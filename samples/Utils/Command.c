/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <pthread.h>

#include "Command.h"


void InitCommand(Command* cmd)
{
    memset(cmd, 0, sizeof(Command));
}



void FreeCommand(Command* cmd)
{
    if (cmd->name)
    {
        free((void*)cmd->name);
    }

    if (cmd->objPath)
    {
        free((void*)cmd->objPath);
    }

    if (cmd->interface)
    {
        free((void*)cmd->interface);
    }

    if (cmd->property)
    {
        free((void*)cmd->property);
    }

    memset(cmd, 0, sizeof(Command));
}


/*======================================================================*/

static pthread_t irq;


static void ParseCommand(char* buf, CommandHandler handler)
{
    /* The buffer may be altered by having NULs replace some characters.
    */
    Command cmd;
    const char* token;
    int step = 0;

    InitCommand(&cmd);

    /* Split the line into words at white space.
    */
    while ((token = strsep(&buf, " \t")) != NULL)
    {
        const char* s = strdup(token);

        switch (step)
        {
        case 0:
            cmd.name = s;
            break;

        case 1:
            cmd.objPath = s;
            break;

        case 2:
            cmd.interface = s;
            break;

        case 3:
            cmd.property = s;
            break;

        default:
            free((void*)s);
            break;
        }

        ++step;
    }

    (*handler)(&cmd);
    FreeCommand(&cmd);
}



static void* IrqHandler(void* arg)
{
    CommandHandler handler = (CommandHandler)(arg);
    char buf[BUFSIZ + 1];
    size_t cap = BUFSIZ;
    size_t len = 0;

    while(1)
    {
        int c = fgetc(stdin);

        if (c == EOF)
        {
            fprintf(stderr, "Warning: stdin closed\n");
            break;
        }
        else
        if (c == '\n')
        {
            ParseCommand(buf, handler);
            len = 0;
        }
        else
        if (len < cap)
        {
            buf[len++] = c;
            buf[len] = 0;
        }
        else
        {
            fprintf(stderr, "Error: exceeded the command length\n");
            len = 0;
        }
    }

    return 0;
}



void StartCommands(CommandHandler handler)
{
    if (pthread_create(&irq, NULL, &IrqHandler, handler) != 0)
    {
        fprintf(stderr, "Error setting up IRQ\n");
    }
}
