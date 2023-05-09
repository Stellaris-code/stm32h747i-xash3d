/*
events.c - SDL event system handlers
Copyright (C) 2015-2017 a1batross

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#if !XASH_DEDICATED
#include <ctype.h>

#include "common.h"
#include "keydefs.h"
#include "input.h"
#include "client.h"
#include "vgui_draw.h"
#include <engine/platform/stm32/events.h>
#include "sound.h"
#include "vid_common.h"

//#include "../MiniFB.h"

//extern struct mfb_window* window;

void Platform_RunEvents( void )
{
	//mfb_update_events(window);
}

void* Platform_GetNativeObject( const char *name )
{
	return NULL; // SDL don't have it
}

/*
========================
Platform_PreCreateMove

this should disable mouse look on client when m_ignore enabled
TODO: kill mouse in win32 clients too
========================
*/
void Platform_PreCreateMove( void )
{
}

#endif //  defined( XASH_SDL ) && !XASH_DEDICATED
