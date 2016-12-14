/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "DeviceConfig.h"
#include "../Utils/BSXML.h"
#include "../Utils/StrBuf.h"
#include "../Utils/FileIO.h"


DEM_Config *DEM_CreateConfig(const char *deviceXmlPath)
{
    StrBuf buf;
    StrBuf_Init(&buf);

    Element* root = NULL;
    DEM_Config* config = calloc(1, sizeof(DEM_Config));

    if (!ReadFile(deviceXmlPath, &buf)) {
        goto error;
    }

    root = BSXML_GetRoot(buf.chars);

    if (!root) {
        goto error;
    }

    // Extract the About data
    Element** about = BSXML_GetPath(root, "AboutData");

    if (!about[0]) {
        goto error;
    }

    config->aboutData = BSXML_Generate(about[0]);
    free((void*)about);

    // Extract the interfaces
    Element** objects = BSXML_GetPath(root, "InterfaceList/Object");

    for (Element** objPtr = objects; *objPtr; ++objPtr) {
        Element* obj = *objPtr;

        /** Each is 
         *      <Object path='/CDM/Lamp'>
         *          <Interface name='org.alljoyn.SmartSpaces.Operation.OnControl'/>
         *      </Object>
         */
        const char* objPath = BSXML_GetAttribute(obj, "path");

        if (!objPath) {
            goto error;
        }

         // Push another object
        config->objects = realloc(config->objects, sizeof(DEM_Object) * (config->numObjects + 1));
        DEM_Object* newObj = &config->objects[config->numObjects++];
        memset(newObj, 0, sizeof(DEM_Object));

        newObj->objectPath = strdup(objPath);

        Element** ifaces = BSXML_GetPath(obj, "Interface");

        for (Element** ifPtr = ifaces; *ifPtr; ++ifPtr) {
            Element* iface = *ifPtr;
            const char* ifaceName = BSXML_GetAttribute(iface, "name");

            if (!ifaceName) {
                goto error;
            }

            // Push another interface
            newObj->interfaces = realloc(newObj->interfaces, sizeof(DEM_Interface) * (newObj->numInterfaces + 1));
            DEM_Interface* newIface = &newObj->interfaces[newObj->numInterfaces++];
            memset(newIface, 0, sizeof(DEM_Interface));

            newIface->name = strdup(ifaceName);

            Element** props = BSXML_GetPath(iface, "Property");

            for (Element** propPtr = props; *propPtr; ++propPtr) {
                Element* prop = *propPtr;

                const char* propName = BSXML_GetAttribute(prop, "name");
                const char* propMode = BSXML_GetAttribute(prop, "mode");

                if (!propName) {
                    goto error;
                }

                // Push another propery
                newIface->properties = realloc(newIface->properties, sizeof(DEM_Property) * (newIface->numProperties + 1));
                DEM_Property* newProp = &newIface->properties[newIface->numProperties++];
                memset(newProp, 0, sizeof(DEM_Property));

                newProp->name = strdup(propName);
                newProp->defaultOnly = (propMode && strcmp(propMode, "default") == 0);

                // There should be one child which is the initial state
                if (prop->numChildren > 0) {
                    newProp->initialState = BSXML_Generate(prop->children[0]);
                }
            }
        }

    }

done:
    if (root) {
        BSXML_FreeElement(root);
    }

    StrBuf_Free(&buf);
    return config;

error:
    DEM_FreeConfig(config);
    config = NULL;
    goto done;
}



static void FreeProperty(DEM_Property* prop)
{
    free((void*)prop->name);

    if (prop->initialState) {
        free((void*)prop->initialState);
    }
}



static void FreeInterface(DEM_Interface* iface)
{
    if (iface->name) {
        free((void*)iface->name);
    }

    for (size_t i = 0; i < iface->numProperties; ++i) {
        FreeProperty(&iface->properties[i]);
    }

    if (iface->properties) {
        free((void*)iface->properties);
    }
}



static void FreeObject(DEM_Object* obj)
{
    if (obj->objectPath) {
        free((void*)obj->objectPath);
    }

    for (size_t i = 0; i < obj->numInterfaces; ++i) {
        FreeInterface(&obj->interfaces[i]);
    }

    if (obj->interfaces) {
        free((void*)obj->interfaces);
    }
}


void DEM_FreeConfig(DEM_Config *config)
{
    if (config != NULL) {
        if (config->deviceName) {
            free((void*)config->deviceName);
        }

        if (config->aboutData) {
            free((void*)config->aboutData);
        }

        for (size_t i = 0; i < config->numObjects; ++i) {
            FreeObject(&config->objects[i]);
        }

        if (config->objects) {
            free((void*)config->objects);
        }

        free((void*)config);
    }
}