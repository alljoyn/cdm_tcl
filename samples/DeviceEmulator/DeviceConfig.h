/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef ALLJOYN_DEVICECONFIG_H
#define ALLJOYN_DEVICECONFIG_H

typedef struct
{
    char *name;
} DEM_Interface;

typedef struct
{
    char *objectPath;
    DEM_Interface *interfaces;
    int numInterfaces;
} DEM_Object;

typedef struct
{
    char *deviceName;
    char *aboutData;
    DEM_Object *objects;
    int numObjects;
} DEM_Config;

DEM_Config *DEM_CreateConfig(const char *deviceXmlPath);

#endif //ALLJOYN_DEVICECONFIG_H
