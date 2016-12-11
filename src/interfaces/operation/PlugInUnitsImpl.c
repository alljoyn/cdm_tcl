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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/PlugInUnitsInterface.h>
#include <ajtcl/cdm/interfaces/operation/PlugInUnitsModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME PLUG_IN_UNITS

const char* const intfDescOperationPlugInUnits[] = {
    "$org.alljoyn.SmartSpaces.Operation.PlugInUnits",
    "@Version>q",
    "@PlugInUnits>a(oub)",
    NULL
};



void FreeFields_PlugInUnits_PlugInInfo(PlugInUnits_PlugInInfo* value)
{
    free((void*)value->objectPath);

    
    
}


void InitArray_PlugInUnits_PlugInInfo(Array_PlugInUnits_PlugInInfo* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(PlugInUnits_PlugInInfo), numElems);
}


// Note: this only allows fields that are char*, not any other kind of pointer
void CopyArray_PlugInUnits_PlugInInfo(Array_PlugInUnits_PlugInInfo* value, Array_PlugInUnits_PlugInInfo* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(PlugInUnits_PlugInInfo));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].objectPath = strdup(value->elems[i].objectPath);
            copy->elems[i].deviceId = value->elems[i].deviceId;
            copy->elems[i].pluggedIn = value->elems[i].pluggedIn;
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_PlugInUnits_PlugInInfo(Array_PlugInUnits_PlugInInfo* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_PlugInUnits_PlugInInfo(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_PlugInUnits_PlugInInfo(Array_PlugInUnits_PlugInInfo* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(PlugInUnits_PlugInInfo), numElems);
}




static AJ_Status PlugInUnits_GetPlugInUnits(AJ_BusAttachment* busAttachment, const char* objPath, Array_PlugInUnits_PlugInInfo* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    PlugInUnitsModel* model = (PlugInUnitsModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetPlugInUnits) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetPlugInUnits(model, objPath, out);
}
 



static AJ_Status MarshalPlugInUnits(AJ_Message* msg, void* structure, const char* structSignature)
{
    PlugInUnits_PlugInInfo* value = (PlugInUnits_PlugInInfo*)structure;
    AJ_MarshalArgs(msg, "o", value->objectPath);
    AJ_MarshalArgs(msg, "u", value->deviceId);
    AJ_MarshalArgs(msg, "b", value->pluggedIn);
    return AJ_OK;
}



AJ_Status Cdm_PlugInUnits_EmitPlugInUnitsChanged(AJ_BusAttachment *bus, const char *objPath, Array_PlugInUnits_PlugInInfo newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "PlugInUnits", "a(oub)", newValue.elems, newValue.numElems, sizeof(*newValue.elems), MarshalPlugInUnits);
}




//
// Handler functions
//
static AJ_Status PlugInUnits_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case PLUGINUNITS_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case PLUGINUNITS_PROP_PLUG_IN_UNITS:
        {
            Array_PlugInUnits_PlugInInfo plug_in_units;
            status = PlugInUnits_GetPlugInUnits(busAttachment, objPath, &plug_in_units);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "a(oub)", plug_in_units.elems, plug_in_units.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_PlugInUnits_PlugInInfo(&plug_in_units);
            }
            break;
        }
    }

    return status;
}



static AJ_Status PlugInUnits_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case PLUGINUNITS_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status PlugInUnits_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationPlugInUnits = {
    PlugInUnits_OnGetProperty,
    PlugInUnits_OnSetProperty,
    PlugInUnits_OnMethodHandler
};
