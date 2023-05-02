//
// Copyright(C) 2005-2014 Simon Howard
// Copyright(C) 2021-2022 Graham Sanderson
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//    Reading of MIDI files.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "memio.h"

#include "doomtype.h"
#include "i_swap.h"
#include "i_system.h"
#include "z_zone.h"
#include "midifile.h"

#if USE_MUSX
#include "musx_decoder.h"
#endif

#define HEADER_CHUNK_ID "MThd"
#define TRACK_CHUNK_ID  "MTrk"
#define MAX_BUFFER_SIZE 0x10000

// haleyjd 09/09/10: packing required
#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

//! Byte swap unsigned short
uint16_t SDL_SwapBE16(uint16_t val)
{
    return (val << 8) | (val >> 8);
}

uint32_t SDL_SwapBE32(uint32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}


typedef PACKED_STRUCT (
{
    byte chunk_id[4];
    unsigned int chunk_size;
}) chunk_header_t;

typedef PACKED_STRUCT (
{
    chunk_header_t chunk_header;
    unsigned short format_type;
    unsigned short num_tracks;
    unsigned short time_division;
}) midi_header_t;

// haleyjd 09/09/10: packing off.
#ifdef _MSC_VER
#pragma pack(pop)
#endif

#if USE_DIRECT_MIDI_LUMP || USE_MIDI_DUMP_MEMFILE
typedef struct {
                           midi_header_t header;
                           uint16_t pad;
} raw_midi_t;
static_assert(sizeof(raw_midi_t) == 16, "");

typedef struct {
                           // Time between the previous event and this event.
                           uint32_t delta_time;
                           uint8_t event;
                           uint8_t param[3];
} raw_midi_event_t;
static_assert(sizeof(raw_midi_event_t) == 8, "");
#endif

typedef struct
{
#if !USE_DIRECT_MIDI_LUMP
    // Length in bytes:

    unsigned int data_len;

    // Events in this track:

    midi_event_t *events;
#else
#if !USE_MUSX
    raw_midi_event_t *raw_events;
#else
    const byte *buffer;
    uint32_t buffer_size;
#endif
#endif
    int num_events;
    int event_capacity;
} midi_track_t;

struct midi_file_s
{
#if !USE_MUSX
    midi_header_t header;

    // All tracks in this file:
    midi_track_t *tracks;
    unsigned int num_tracks;
#endif
#if !USE_DIRECT_MIDI_LUMP
    // Data buffer used to store data read for SysEx or meta events:
    byte *buffer;
    unsigned int buffer_size;
#endif
#if USE_MUSX
    midi_track_t tracks[1];
#endif
};

struct midi_track_iter_s
{
    midi_track_t *track;
    unsigned int position;
#if USE_MUSX
    midi_event_t events[2];
    int peek_index;
    th_bit_input bit_input; // note we mark end of stream reached by NULLing this out
    musx_decoder decoder;
    uint16_t decoder_space[MUSX_MAX_DECODER_SPACE];
#endif
};


#if !USE_DIRECT_MIDI_LUMP


// Check the header of a chunk:

static boolean CheckChunkHeader(chunk_header_t *chunk,
                                const char *expected_id)
{
    boolean result;
    
    result = (memcmp((char *) chunk->chunk_id, expected_id, 4) == 0);

    if (!result)
    {
        stderr_print( "CheckChunkHeader: Expected '%s' chunk header, "
                        "got '%c%c%c%c'\n",
                        expected_id,
                        chunk->chunk_id[0], chunk->chunk_id[1],
                        chunk->chunk_id[2], chunk->chunk_id[3]);
    }

    return result;
}

// Read a single byte.  Returns false on error.

static boolean ReadByte(byte *result, MEMFILE *stream)
{
    int c;

    mem_fread(&c, 1, 1, stream);
    //c = fgetc(stream);

    if (c == EOF)
    {
        stderr_print( "ReadByte: Unexpected end of file\n");
        return false;
    }
    else
    {
        *result = (byte) c;

        return true;
    }
}

// Read a variable-length value.

static boolean ReadVariableLength(unsigned int *result, MEMFILE *stream)
{
    int i;
    byte b = 0;

    *result = 0;

    for (i=0; i<4; ++i)
    {
        if (!ReadByte(&b, stream))
        {
            stderr_print( "ReadVariableLength: Error while reading "
                            "variable-length value\n");
            return false;
        }

        // Insert the bottom seven bits from this byte.

        *result <<= 7;
        *result |= b & 0x7f;

        // If the top bit is not set, this is the end.

        if ((b & 0x80) == 0)
        {
            return true;
        }
    }

    stderr_print( "ReadVariableLength: Variable-length value too "
                    "long: maximum of four bytes\n");
    return false;
}

// Read a byte sequence into the data buffer.

static void *ReadByteSequence(unsigned int num_bytes, MEMFILE *stream)
{
    unsigned int i;
    byte *result;

    // Allocate a buffer. Allocate one extra byte, as malloc(0) is
    // non-portable.

    result = Z_Malloc(num_bytes + 1, PU_STATIC, 0);

    if (result == NULL)
    {
    	assert(0);
        stderr_print( "ReadByteSequence: Failed to allocate buffer\n");
        return NULL;
    }

    // Read the data:

    for (i=0; i<num_bytes; ++i)
    {
        if (!ReadByte(&result[i], stream))
        {
        	assert(0);
            stderr_print( "ReadByteSequence: Error while reading byte %u\n",
                            i);
            Z_Free(result);
            return NULL;
        }
    }

    return result;
}

// Read a MIDI channel event.
// two_param indicates that the event type takes two parameters
// (three byte) otherwise it is single parameter (two byte)

static boolean ReadChannelEvent(midi_event_t *event,
                                byte event_type, boolean two_param,
                                MEMFILE *stream)
{
    byte b = 0;

    // Set basics:

    event->event_type = event_type & 0xf0;
    event->data.channel.channel = event_type & 0x0f;

    // Read parameters:

    if (!ReadByte(&b, stream))
    {
        stderr_print( "ReadChannelEvent: Error while reading channel "
                        "event parameters\n");
        return false;
    }

    event->data.channel.param1 = b;

    // Second parameter:

    if (two_param)
    {
        if (!ReadByte(&b, stream))
        {
            stderr_print( "ReadChannelEvent: Error while reading channel "
                            "event parameters\n");
            return false;
        }

        event->data.channel.param2 = b;
    } else {
        event->data.channel.param2 = 0;
    }

    return true;
}

// Read sysex event:

static boolean ReadSysExEvent(midi_event_t *event, int event_type,
                              MEMFILE *stream)
{
    event->event_type = event_type;

    if (!ReadVariableLength(&event->data.sysex.length, stream))
    {
        stderr_print( "ReadSysExEvent: Failed to read length of "
                                        "SysEx block\n");
        return false;
    }

    // Read the byte sequence:

    event->data.sysex.data = ReadByteSequence(event->data.sysex.length, stream);

    if (event->data.sysex.data == NULL)
    {
        stderr_print( "ReadSysExEvent: Failed while reading SysEx event\n");
        return false;
    }

    return true;
}

// Read meta event:

static boolean ReadMetaEvent(midi_event_t *event, MEMFILE *stream)
{
    byte b = 0;

    event->event_type = MIDI_EVENT_META;

    // Read meta event type:

    if (!ReadByte(&b, stream))
    {
        stderr_print( "ReadMetaEvent: Failed to read meta event type\n");
        return false;
    }

    event->data.meta.type = b;

    // Read length of meta event data:

    if (!ReadVariableLength(&event->data.meta.length, stream))
    {
        stderr_print( "ReadSysExEvent: Failed to read length of "
                                        "SysEx block\n");
        return false;
    }

    // Read the byte sequence:

    event->data.meta.data = ReadByteSequence(event->data.meta.length, stream);

    if (event->data.meta.data == NULL)
    {
        stderr_print( "ReadSysExEvent: Failed while reading SysEx event\n");
        return false;
    }

    return true;
}

static boolean ReadEvent(midi_event_t *event, unsigned int *last_event_type,
                         MEMFILE *stream)
{
    byte event_type = 0;

    if (!ReadVariableLength(&event->delta_time, stream))
    {
        stderr_print( "ReadEvent: Failed to read event timestamp\n");
        return false;
    }

    if (!ReadByte(&event_type, stream))
    {
        stderr_print( "ReadEvent: Failed to read event type\n");
        return false;
    }

    // All event types have their top bit set.  Therefore, if 
    // the top bit is not set, it is because we are using the "same
    // as previous event type" shortcut to save a byte.  Skip back
    // a byte so that we read this byte again.

    if ((event_type & 0x80) == 0)
    {
        event_type = *last_event_type;

        if (mem_fseek(stream, -1, SEEK_CUR) < 0)
        {
            stderr_print( "ReadEvent: Unable to seek in stream\n");
            return false;
        }
    }
    else
    {
        *last_event_type = event_type;
    }

    // Check event type:

    switch (event_type & 0xf0)
    {
        // Two parameter channel events:

        case MIDI_EVENT_NOTE_OFF:
        case MIDI_EVENT_NOTE_ON:
        case MIDI_EVENT_AFTERTOUCH:
        case MIDI_EVENT_CONTROLLER:
        case MIDI_EVENT_PITCH_BEND:
            return ReadChannelEvent(event, event_type, true, stream);

        // Single parameter channel events:

        case MIDI_EVENT_PROGRAM_CHANGE:
        case MIDI_EVENT_CHAN_AFTERTOUCH:
            return ReadChannelEvent(event, event_type, false, stream);

        default:
            break;
    }

    // Specific value?

    switch (event_type)
    {
        case MIDI_EVENT_SYSEX:
        case MIDI_EVENT_SYSEX_SPLIT:
            return ReadSysExEvent(event, event_type, stream);

        case MIDI_EVENT_META:
            return ReadMetaEvent(event, stream);

        default:
            break;
    }

    stderr_print( "ReadEvent: Unknown MIDI event type: 0x%x\n", event_type);
    return false;
}

// Free an event:

static void FreeEvent(midi_event_t *event)
{
    // Some event types have dynamically allocated buffers assigned
    // to them that must be freed.

    switch (event->event_type)
    {
        case MIDI_EVENT_SYSEX:
        case MIDI_EVENT_SYSEX_SPLIT:
            Z_Free(event->data.sysex.data);
            break;

        case MIDI_EVENT_META:
            Z_Free(event->data.meta.data);
            break;

        default:
            // Nothing to do.
            break;
    }
}

// Read and check the track chunk header

static boolean ReadTrackHeader(midi_track_t *track, MEMFILE *stream)
{
    size_t records_read;
    chunk_header_t chunk_header;

    records_read = mem_fread(&chunk_header, sizeof(chunk_header_t), 1, stream);

    if (records_read < 1)
    {
        return false;
    }

    if (!CheckChunkHeader(&chunk_header, TRACK_CHUNK_ID))
    {
        return false;
    }

    track->data_len = SDL_SwapBE32(chunk_header.chunk_size);

    return true;
}

static boolean ReadTrack(midi_track_t *track, MEMFILE *stream)
{
    midi_event_t *new_events;
    midi_event_t *event;
    unsigned int last_event_type;

    track->num_events = 0;
    track->event_capacity = 4096;
    track->events = NULL;

    // Read the header:

    if (!ReadTrackHeader(track, stream))
    {
        return false;
    }

    track->events = Z_Malloc(sizeof(midi_event_t) * track->event_capacity, PU_STATIC, 0);

    // Then the events:

    last_event_type = 0;

    for (;;)
    {
    	if (track->event_capacity < track->num_events + 1)
    	{
    		track->event_capacity += 4096;
            new_events = I_Realloc(track->events,
                                 sizeof(midi_event_t) * track->event_capacity);
            track->events = new_events;
    	}

        // Resize the track slightly larger to hold another event:

        // Read the next event:

        event = &track->events[track->num_events];
        if (!ReadEvent(event, &last_event_type, stream))
        {
            return false;
        }

        ++track->num_events;

        // End of track?

        if (event->event_type == MIDI_EVENT_META
         && event->data.meta.type == MIDI_META_END_OF_TRACK)
        {
            break;
        }
    }

    return true;
}

// Free a track:

static void FreeTrack(midi_track_t *track)
{
    unsigned int i;

    for (i=0; i<track->num_events; ++i)
    {
        FreeEvent(&track->events[i]);
    }

    Z_Free(track->events);
}

static boolean ReadAllTracks(midi_file_t *file, MEMFILE *stream)
{
    unsigned int i;

    // Allocate list of tracks and read each track:

    file->tracks = Z_Malloc(sizeof(midi_track_t) * file->num_tracks, PU_STATIC, 0);

    if (file->tracks == NULL)
    {
        return false;
    }

    memset(file->tracks, 0, sizeof(midi_track_t) * file->num_tracks);

    // Read each track:

    for (i=0; i<file->num_tracks; ++i)
    {
        if (!ReadTrack(&file->tracks[i], stream))
        {
            return false;
        }
    }

    return true;
}

// Read and check the header chunk.

static boolean ReadFileHeader(midi_file_t *file, MEMFILE *stream)
{
    size_t records_read;
    unsigned int format_type;

    records_read = mem_fread(&file->header, sizeof(midi_header_t), 1, stream);

    if (records_read < 1)
    {
        return false;
    }

    if (!CheckChunkHeader(&file->header.chunk_header, HEADER_CHUNK_ID)
     || SDL_SwapBE32(file->header.chunk_header.chunk_size) != 6)
    {
        stderr_print( "ReadFileHeader: Invalid MIDI chunk header! "
                        "chunk_size=%i\n",
                        SDL_SwapBE32(file->header.chunk_header.chunk_size));
        return false;
    }

    format_type = SDL_SwapBE16(file->header.format_type);
    file->num_tracks = SDL_SwapBE16(file->header.num_tracks);

    if ((format_type != 0 && format_type != 1)
     || file->num_tracks < 1)
    {
        stderr_print( "ReadFileHeader: Only type 0/1 "
                                         "MIDI files supported!\n");
        return false;
    }

    return true;
}
#endif

void MIDI_FreeFile(midi_file_t *file)
{

#if !USE_DIRECT_MIDI_LUMP
    if (file->tracks != NULL)
    {
        int i;
        for (i=0; i<file->num_tracks; ++i)
        {
            FreeTrack(&file->tracks[i]);
        }
        Z_Free(file->tracks);
    }
#endif

    Z_Free(file);
}

#if !USE_DIRECT_MIDI_LUMP
midi_file_t *MIDI_LoadFile(MEMFILE* stream)
{
    midi_file_t *file;

    file = Z_Malloc(sizeof(midi_file_t), PU_STATIC, 0);

    if (file == NULL)
    {
        return NULL;
    }

    file->tracks = NULL;
    file->num_tracks = 0;
    file->buffer = NULL;
    file->buffer_size = 0;

    // Open file

    if (stream == NULL)
    {
        //stderr_print( "MIDI_LoadFile: Failed to open '%s'\n", filename);
        assert(0);
        MIDI_FreeFile(file);
        return NULL;
    }

    // Read MIDI file header

    if (!ReadFileHeader(file, stream))
    {
        assert(0);
        MIDI_FreeFile(file);
        return NULL;
    }

    // Read all tracks:

    if (!ReadAllTracks(file, stream))
    {
        assert(0);
        MIDI_FreeFile(file);
        return NULL;
    }

    return file;
}
#endif

// Get the number of tracks in a MIDI file.

unsigned int MIDI_NumTracks(midi_file_t *file)
{
    return midifile_numtracks(file);
}

// Start iterating over the events in a track.

#ifdef TEST
static void PrintTrack(midi_track_t *track);
#endif
midi_track_iter_t *MIDI_IterateTrack(midi_file_t *file, unsigned int track)
{
    midi_track_iter_t *iter;

    assert(track < midifile_numtracks(file));

//    printf("Begin iterating track %d\n", track);
//    PrintTrack(&file->tracks[track]);
    iter = Z_Malloc(sizeof(*iter), PU_STATIC, 0);
    iter->track = &file->tracks[track];
    MIDI_RestartIterator(iter);
    return iter;
}

void MIDI_FreeIterator(midi_track_iter_t *iter)
{
	Z_Free(iter);
}

// Get the time until the next MIDI event in a track.

unsigned int MIDI_GetDeltaTime(midi_track_iter_t *iter)
{
#if USE_MUSX
    return iter->events[iter->peek_index^1].delta_time;
#else
    if (iter->position < iter->track->num_events)
    {
#if USE_DIRECT_MIDI_LUMP
        raw_midi_event_t *next_event;
        next_event = &iter->track->raw_events[iter->position];
#else
        midi_event_t *next_event;
        next_event = &iter->track->events[iter->position];
        return next_event->delta_time;
#endif
        return next_event->delta_time;
    }
    else
    {
        return 0;
    }
#endif
}

// Get a pointer to the next MIDI event.
#if USE_MUSX
void peek_event(midi_track_iter_t *iter);
#endif

#if USE_DIRECT_MIDI_LUMP && !USE_MUSX
static void MIDI_DecodeEvent(raw_midi_event_t *raw_event, midi_event_t *event) {
    event->delta_time = raw_event->delta_time;
    if (raw_event->event == MIDI_EVENT_META) {
        event->event_type = raw_event->event;
        event->data.meta.type = MIDI_META_SET_TEMPO;
        event->data.meta.data = raw_event->param;
        event->data.meta.length = 3;
    } else {
        event->event_type = raw_event->event & 0xf0;
        event->data.channel.channel = raw_event->event & 0x0f;
        event->data.channel.param1 = raw_event->param[0];
        event->data.channel.param2 = raw_event->param[1];
    }
}
#endif

int MIDI_GetNextEvent(midi_track_iter_t *iter, midi_event_t **event)
{
#if USE_MUSX
    *event = &iter->events[iter->peek_index];
    peek_event(iter);
    return 1;
#else
    if (iter->position < iter->track->num_events)
    {
#if USE_DIRECT_MIDI_LUMP
        *event = &iter->track->raw_events[iter->position];
        MIDI_DecodeEvent(&iter->track->raw_events[iter->position], *event);
        ++iter->position;
#else
        *event = &iter->track->events[iter->position];
#endif
        ++iter->position;
        return 1;
    }
    else
    {
        return 0;
    }
#endif
}

unsigned int MIDI_GetFileTimeDivision(midi_file_t *file)
{
    short result = midifile_timedivision(file);

    // Negative time division indicates SMPTE time and must be handled
    // differently.
    if (result < 0)
    {
        return (signed int)(-(result/256))
             * (signed int)(result & 0xFF);
    }
    else
    {
        return result;
    }
}

void MIDI_RestartIterator(midi_track_iter_t *iter)
{
    iter->position = 0;
#if USE_MUSX
    iter->peek_index = 0;
    iter->events[iter->peek_index].delta_time = 0; // time before first event
    uint8_t tmp_buf[512]; // todo get tem[ workspace if stack not big enough
    th_sized_bit_input_init(&iter->bit_input, iter->track->buffer, iter->track->buffer_size);
    musx_decoder_init(&iter->decoder, &iter->bit_input, iter->decoder_space, count_of(iter->decoder_space), tmp_buf, sizeof(tmp_buf));
    peek_event(iter);
#endif
}


