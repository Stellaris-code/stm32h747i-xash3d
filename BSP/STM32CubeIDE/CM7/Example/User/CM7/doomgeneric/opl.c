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
//     OPL interface.
//

#include <stdio.h>
#include <stdlib.h>

#include "opl.h"
#include "opl_internal.h"

extern opl_driver_t *driver;

typedef struct
{
    int finished;

} delay_data_t;

static void DelayCallback(void *_delay_data)
{
    delay_data_t *delay_data = _delay_data;

    delay_data->finished = 1;

}

void OPL_Delay(uint64_t us)
{
    volatile delay_data_t delay_data;

    if (driver == NULL)
    {
        return;
    }

    // Create a callback that will signal this thread after the
    // specified time.


    delay_data.finished = 0;
    OPL_SetCallback(us, DelayCallback, &delay_data);

    // Wait until the callback is invoked.
    while (!delay_data.finished)
    {
        ;
    }
}
