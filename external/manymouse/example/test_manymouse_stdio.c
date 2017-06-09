/*
 * A test file for ManyMouse that dumps input data to stdout.
 *
 * Please see the file LICENSE.txt in the source's root directory.
 *
 *  This file written by Ryan C. Gordon.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manymouse.h"

int main(int argc, char **argv)
{
    ManyMouseEvent event;
    const int available_mice = ManyMouse_Init();
    int i;

    if (ManyMouse_Init() < 0)
    {
        printf("Error initializing ManyMouse!\n");
        ManyMouse_Quit();
    }

    while (1)
    {
        while (ManyMouse_PollEvent(&event))
        {
            if (event.type == MANYMOUSE_EVENT_RELMOTION)
            {
                printf("Mouse #%u relative motion %s %d\n", event.device,
                        event.item == 0 ? "X" : "Y", event.value);
            }

            else if (event.type == MANYMOUSE_EVENT_ABSMOTION)
            {
                printf("Mouse #%u absolute motion %s %d\n", event.device,
                        event.item == 0 ? "X" : "Y", event.value);
            }

            else if (event.type == MANYMOUSE_EVENT_BUTTON)
            {
                printf("Mouse #%u button %u %s\n", event.device,
                        event.item, event.value ? "down" : "up");
            }

            else if (event.type == MANYMOUSE_EVENT_SCROLL)
            {
                const char *wheel;
                const char *direction;
                if (event.item == 0)
                {
                    wheel = "vertical";
                    direction = ((event.value > 0) ? "up" : "down");
                }
                else
                {
                    wheel = "horizontal";
                    direction = ((event.value > 0) ? "right" : "left");
                }
                printf("Mouse #%u wheel %s %s\n", event.device,
                        wheel, direction);
            }

            else if (event.type == MANYMOUSE_EVENT_DISCONNECT)
                printf("Mouse #%u disconnect\n", event.device);

            else
            {
                printf("Mouse #%u unhandled event type %d\n", event.device,
                        event.type);
            }
        }
    }

    ManyMouse_Quit();
    return 0;
}

/* end of test_manymouse_stdio.c ... */

