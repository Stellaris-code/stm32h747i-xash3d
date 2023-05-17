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

#include "stm32h7xx_hal.h"
#include "stm32h747i_discovery.h"

//#include "../MiniFB.h"

//extern struct mfb_window* window;


#define JOYSTATES 6

static unsigned char joystate[JOYSTATES];
static const char* cmds[JOYSTATES] =
{
		"jump",
		"back",
		"left",
		"right",
		"forward",
		"attack\n+use\n-use"
};


char input_rcv_buf[256];

void Platform_RunEvents( void )
{
	  unsigned char newjoystate[JOYSTATES];
	  newjoystate[0] = !HAL_GPIO_ReadPin(JOY1_SEL_GPIO_PORT, JOY1_SEL_PIN);
	  newjoystate[1] = !HAL_GPIO_ReadPin(JOY1_DOWN_GPIO_PORT, JOY1_DOWN_PIN);
	  newjoystate[2] = !HAL_GPIO_ReadPin(JOY1_LEFT_GPIO_PORT, JOY1_LEFT_PIN);
	  newjoystate[3] = !HAL_GPIO_ReadPin(JOY1_RIGHT_GPIO_PORT, JOY1_RIGHT_PIN);
	  newjoystate[4] = !HAL_GPIO_ReadPin(JOY1_UP_GPIO_PORT, JOY1_UP_PIN);
	  newjoystate[5] = BSP_PB_GetState(BUTTON_WAKEUP);

	  for (int i = 0; i < JOYSTATES; ++i)
	  {
		  if (joystate[i] == newjoystate[i])
			  continue;

		  char buf[32];
		  sprintf(buf, "%c%s\n", newjoystate[i] ? '+' : '-', cmds[i]);

		  Cbuf_InsertText(buf);

		  joystate[i] = newjoystate[i];
	  }
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
