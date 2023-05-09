/*
filesystem.h - engine FS
Copyright (C) 2007 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifndef FILESYSTEM_INTERNAL_H
#define FILESYSTEM_INTERNAL_H

#include "xash3d_types.h"
#include "filesystem.h"

#ifdef __cplusplus
extern "C"
{
#endif



#if 0
#define Mem_Malloc( pool, size ) g_engfuncs._Mem_Alloc( pool, size, false, __FILE__, __LINE__ )
#define Mem_Calloc( pool, size ) g_engfuncs._Mem_Alloc( pool, size, true, __FILE__, __LINE__ )
#define Mem_Realloc( pool, ptr, size ) g_engfuncs._Mem_Realloc( pool, ptr, size, true, __FILE__, __LINE__ )
#define Mem_Free( mem ) g_engfuncs._Mem_Free( mem, __FILE__, __LINE__ )
#define Mem_AllocPool( name ) g_engfuncs._Mem_AllocPool( name, __FILE__, __LINE__ )
#define Mem_FreePool( pool ) g_engfuncs._Mem_FreePool( pool, __FILE__, __LINE__ )

#define Con_Printf  (*g_engfuncs._Con_Printf)
#define Con_DPrintf (*g_engfuncs._Con_DPrintf)
#define Con_Reportf (*g_engfuncs._Con_Reportf)
#define Sys_Error   (*g_engfuncs._Sys_Error)
#endif

#ifdef __cplusplus
}
#endif

#endif // FILESYSTEM_INTERNAL_H
