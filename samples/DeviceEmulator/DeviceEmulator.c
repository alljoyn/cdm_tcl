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

#include <stdio.h>
#include <stdlib.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/cdm/utils/CDM_System.h>
#include <ajtcl/cdm/utils/CDM_AboutData.h>

#include "DeviceConfig.h"

int main(int argc, char *argv[])
{
    int retVal = 0;
    AJ_Status status;

    CDM_AboutIconParams iconParams;
    CDM_RoutingNodeParams routingNodeParams;
    CDM_BusAttachment bus;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: DeviceEmulator xml-file\n");
        return 1;
    }

    DEM_Config *config = DEM_CreateConfig(argv[1]);
    const CDM_AboutDataBuf aboutData = CDM_CreateAboutDataFromXml(config->aboutData);

    CDM_SetDefaultAboutIconParams(&iconParams);
    status = CDM_SystemInit(&iconParams);
    if (status != AJ_OK)
    {
        fprintf(stderr, "SystemInit failed: %d\n", status);
        retVal = 1;
        goto CLEANUP;
    }

    CDM_SetDefaultRoutingNodeParams(&routingNodeParams);
    status = CDM_SystemConnect(&routingNodeParams, &bus);


    CDM_SystemStop();

CLEANUP:
    CDM_DestroyAboutData(aboutData);
    DEM_FreeConfig(config);

    return retVal;
}

