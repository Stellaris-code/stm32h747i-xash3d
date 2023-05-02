//
// Copyright(C) 2005-2014 Simon Howard
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
//     OPL Win32 native interface.
//

#ifdef _WIN32

#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "opl.h"
#include "opl_internal.h"
#include "opl_timer.h"

static unsigned int opl_port_base;

// Not x86, or don't know how to do port R/W on this compiler.

#define NO_PORT_RW

static unsigned int OPL_Win32_PortRead(opl_port_t port)
{
    return 0;
}

static void OPL_Win32_PortWrite(opl_port_t port, unsigned int value)
{
}

static int OPL_Win32_Init(unsigned int port_base)
{
    return OPL_INIT_OPL3;
}

static void OPL_Win32_Shutdown(void)
{
    // Stop callback thread

    //OPL_Timer_StopThread();
}

void OPL_Timer_SetCallback(uint64_t us, opl_callback_t callback, void* data)
{

}

void OPL_Timer_ClearCallbacks(void)
{

}

void OPL_Timer_AdjustCallbacks(unsigned int old_tempo, unsigned int new_tempo)
{
}

void OPL_Timer_Lock(void)
{

}

void OPL_Timer_Unlock(void)
{

}

void OPL_Timer_SetPaused(int paused)
{

}

opl_driver_t opl_win32_driver =
{
    "Win32",
    OPL_Win32_Init,
    OPL_Win32_Shutdown,
    OPL_Win32_PortRead,
    OPL_Win32_PortWrite,
    OPL_Timer_SetCallback,
    OPL_Timer_ClearCallbacks,
    OPL_Timer_Lock,
    OPL_Timer_Unlock,
    OPL_Timer_SetPaused,
    OPL_Timer_AdjustCallbacks,
};

#endif /* #ifdef _WIN32 */

