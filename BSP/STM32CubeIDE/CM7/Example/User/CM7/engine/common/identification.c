/*
identification.c - unique id generation
Copyright (C) 2017 mittorn

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "common.h"

static char id_md5[33];
static char id_customid[MAX_STRING];

const char *ID_GetMD5( void )
{
	if( id_customid[0] )
		return id_customid;
	return id_md5;
}

/*
===============
ID_SetCustomClientID

===============
*/
void GAME_EXPORT ID_SetCustomClientID( const char *id )
{
	if( !id )
		return;

	Q_strncpy( id_customid, id, sizeof( id_customid  ) );
}

void ID_Init( void )
{
	memcpy(id_md5, "abcdefg", 8);
}
