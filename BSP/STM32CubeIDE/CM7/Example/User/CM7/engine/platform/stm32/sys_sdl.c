/*
sys_sdl.c - SDL2 system utils
Copyright (C) 2018 a1batross

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include <engine/platform/stm32/events.h>
#include "platform/platform.h"

#include "stm32h7xx_hal.h"

extern void qembd_vidinit();

void Platform_Init( void )
{
#if XASH_WIN32
	Wcon_CreateConsole(); // system console used by dedicated server or show fatal errors
#elif XASH_POSIX
	//Posix_Daemonize();
#if XASH_PSVITA
	PSVita_Init();
#elif XASH_NSWITCH
	NSwitch_Init();
#endif
#endif // XASH_POSIX

	//qembd_vidinit();
}

void Platform_Shutdown( void )
{
#if XASH_NSWITCH
	NSwitch_Shutdown();
#elif XASH_WIN32
	Wcon_DestroyConsole();
#elif XASH_PSVITA
	PSVita_Shutdown();
#endif
}

double Platform_DoubleTime( void )
{
	return HAL_GetTick() / 1000.0;
}

void Platform_Sleep( int msec )
{
	HAL_Delay(msec);
}

void Platform_ShellExecute( const char *path, const char *parms )
{
	Con_Reportf( S_WARN "Tried to shell execute ;%s; -- not supported\n", path );
}

// Function addresses in flash don't move, simply use their address as their ID

void *COM_FunctionFromName( void *hInstance, const char *pName )
{
	return (void*)Q_atoi((uint32_t)pName);
}

const char *COM_NameForFunction( void *hInstance, void *function )
{
	static string sname;
	Q_snprintf( sname, MAX_STRING, "%d", (uint32_t)function);
	return sname;
}
