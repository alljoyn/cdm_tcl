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
#include <ajtcl/cdm/CdmControllee.h>
#include "CdmControlleeImpl.h"
#include <ajtcl/cdm/interfaces/environment/TargetTemperature.h>

#define CDM_OBJECT_LIST_INDEX AJAPP_OBJECTS_LIST_INDEX

static CdmObjectInfo* objInfoFirst;
static CdmObjectInfo* objInfoLast;
static AJ_Object* ajObjects;


AJ_Status Cdm_Init(void)
{
    objInfoFirst = NULL;
    objInfoLast = NULL;
    ajObjects = NULL;

    AJ_Status status = AJ_OK;

    return status;
}


void Cdm_Deinit(void)
{
    CdmObjectInfo* objInfo = objInfoFirst;
    CdmObjectInfo* tempObjInfo = NULL;
    CdmInterfaceInfo* intfInfo = NULL;
    CdmInterfaceInfo* tempIntfInfo = NULL;

    if (ajObjects) {
        free(ajObjects);
    }

    while (objInfo) {
        intfInfo = objInfo->intfFirst;

        while (intfInfo) {
            tempIntfInfo = intfInfo;
            intfInfo = intfInfo->nextNode;
            free(tempIntfInfo);
        }

        if (objInfo->descs) {
            free(objInfo->descs);
        }

        tempObjInfo = objInfo;
        objInfo = objInfo->nextNode;
        free(tempObjInfo);
    }
}



static CdmObjectInfo* GetObjectInfoByPath(const char* objPath)
{
    CdmObjectInfo* objInfo = objInfoFirst;

    if (!objPath) {
        return NULL;
    }

    while (objInfo) {
        if (!strcmp(objPath, objInfo->path)) {
            break;
        } else {
            objInfo = objInfo->nextNode;
        }
    }

    return objInfo;
}


static bool CheckInterfaceAlreadyAdded(CdmObjectInfo* objInfo, const char* intfName)
{
    if (!objInfo) {
        return false;
    }

    CdmInterfaceInfo* intfInfo = objInfo->intfFirst;
    while (intfInfo) {
        if (!strcmp(intfName, intfInfo->name)) {
            break;
        }
        intfInfo = intfInfo->nextNode;
    }

    return (intfInfo != NULL);
}


AJ_Status Cdm_AddInterface(const char* objPath, const char* intfName, const char* const* intfDesc, const InterfaceHandler* intfHandler, void* intfModel)
{
    CdmObjectInfo* objInfo = NULL;

    if (!intfName || !intfDesc || !intfHandler || !objPath || !intfModel) {
        return AJ_ERR_INVALID;
    }

    objInfo = GetObjectInfoByPath(objPath);
    if (objInfo) {
        if (CheckInterfaceAlreadyAdded(objInfo, intfName)) {
            return AJ_ERR_DISALLOWED;
        }
    } else {
        objInfo = malloc(sizeof(CdmObjectInfo));
        if (!objInfo) {
            return AJ_ERR_RESOURCES;
        }
        memset(objInfo, 0, sizeof(CdmObjectInfo));

        {
            CdmObjectInfo tempObj = { objPath, NULL, NULL, NULL, NULL };
            memcpy(objInfo, &tempObj, sizeof(tempObj));
        }

        if (!objInfoFirst) {
            objInfoFirst = objInfo;
        }
        if (objInfoLast) {
            objInfoLast->nextNode = objInfo;
        }
        objInfoLast = objInfo;
    }

    CdmInterfaceInfo* intfInfo = malloc(sizeof(CdmInterfaceInfo));
    if (!intfInfo) {
        return AJ_ERR_RESOURCES;
    }
    memset(intfInfo, 0, sizeof(CdmInterfaceInfo));

    {
        CdmInterfaceInfo tempIntfInfo = {intfName, intfDesc, intfHandler, intfModel, NULL };
        memcpy(intfInfo, &tempIntfInfo, sizeof(tempIntfInfo));
    }

    if (!objInfo->intfFirst) {
        objInfo->intfFirst = intfInfo;
        objInfo->intfLast = intfInfo;
    } else {
        objInfo->intfLast->nextNode = intfInfo;
        objInfo->intfLast = intfInfo;
    }

    return AJ_OK;
}



static void CleanInterfaceDescs()
{
    CdmObjectInfo* objInfo = objInfoFirst;

    while (objInfo) {
        if (objInfo->descs) {
            free(objInfo->descs);
        }

        objInfo = objInfo->nextNode;
    }
}



AJ_Status Cdm_Start(void)
{
    if (!objInfoFirst || !objInfoLast) {
        return AJ_ERR_UNEXPECTED;
    }

    int numOfObjs = 1;
    CdmObjectInfo* objInfo = objInfoFirst;
    while (objInfo != objInfoLast) {
        objInfo = objInfo->nextNode;
        numOfObjs++;
    }

    ajObjects = malloc(sizeof(AJ_Object) * (numOfObjs + 1)); /* +1 is for last NULL */
    if (!ajObjects) {
        return AJ_ERR_RESOURCES;
    }
    memset(ajObjects, 0, sizeof(AJ_Object) * (numOfObjs + 1));

    int i = 0;
    objInfo = objInfoFirst;
    while (objInfo) {
        CdmInterfaceInfo* intfInfo = objInfo->intfFirst;
        int numOfIntfs = 1;
        while (intfInfo != objInfo->intfLast) {
            intfInfo = intfInfo->nextNode;
            numOfIntfs++;
        }

        objInfo->descs = malloc(sizeof(AJ_InterfaceDescription) * (numOfIntfs + 2)); /* +2 are for AJ_PropertiesIface and last NULL */
        if (!objInfo->descs) {
            CleanInterfaceDescs();
            free(ajObjects);
            return AJ_ERR_RESOURCES;
        }
        memset(objInfo->descs, 0, sizeof(AJ_InterfaceDescription) * (numOfIntfs + 2));
        
        objInfo->descs[0] = AJ_PropertiesIface;

        int j = 1;
        intfInfo = objInfo->intfFirst;
        while (intfInfo) {
            objInfo->descs[j] = intfInfo->desc;
            intfInfo = intfInfo->nextNode;
            j++;
        }
        objInfo->descs[j] = NULL;

        {
            AJ_Object temp_obj = { objInfo->path, objInfo->descs, AJ_OBJ_FLAG_ANNOUNCED };
            memcpy(&ajObjects[i], &temp_obj, sizeof(temp_obj));
        }
        objInfo = objInfo->nextNode;
        i++;
    }

    return AJ_RegisterObjectList(ajObjects, CDM_OBJECT_LIST_INDEX);
}

static bool IsCdmMsg(uint32_t msgId)
{
    return ((msgId >> 24) == CDM_OBJECT_LIST_INDEX);
}

static uint8_t GetObjectIndex(uint32_t msgId)
{
    return (uint8_t)((msgId & 0x00FF0000) >> 16);
}

static uint8_t GetInterfaceIndex(uint32_t msgId)
{
    return (uint8_t)((msgId & 0x0000FF00) >> 8);
}

static uint8_t GetMemberIndex(uint32_t msgId)
{
    return (uint8_t)(msgId & 0x0000FF);
}


static CdmObjectInfo* GetObjectInfoByIndex(uint8_t objIndex)
{
    CdmObjectInfo* objInfo = objInfoFirst;

    for (uint32_t i = 0; i < objIndex; i++) {
        if (!objInfo) {
            break;
        }

        objInfo = objInfo->nextNode;
    }

    return objInfo;
}


static CdmInterfaceInfo* GetInterfaceInfo(CdmObjectInfo* objInfo, uint8_t intfIndex)
{
    if (!objInfo) {
        return NULL;
    }
    if (intfIndex < 1) { /* 0 is org.freedesktop.DBus.Properties */
        return NULL;
    }

    CdmInterfaceInfo* intfInfo = objInfo->intfFirst;

    for (uint32_t i = 1; i < intfIndex; i++) {
        intfInfo = intfInfo->nextNode;
        if (!intfInfo) {
            break;
        }
    }

    return intfInfo;
}



static AJ_Status PropGetHandler(AJ_Message* msg, AJ_BusAttachment* busAttachment)
{
    uint32_t propId;
    const char* sig;
    AJ_Message reply;

    AJ_Status status = AJ_UnmarshalPropertyArgs(msg, &propId, &sig);
    if (status == AJ_OK) {
        AJ_MarshalReplyMsg(msg, &reply);
        AJ_MarshalVariant(&reply, sig);

        uint8_t objIndex = GetObjectIndex(propId);
        uint8_t intfIndex = GetInterfaceIndex(propId);
        CdmObjectInfo* objInfo = GetObjectInfoByIndex(objIndex);
        CdmInterfaceInfo* intfInfo = GetInterfaceInfo(objInfo, intfIndex);
            
        /**
         * OnGetProperty must attempt to deliver the message for memory management reasons.
         * If it returns an error it may have attempted to deliver the message
         * but failed. Be careful that nothing else attempts to marshal a message until this
         * reply has been delivered.
         */
        if (objInfo && intfInfo && intfInfo->handler && intfInfo->handler->OnGetProperty) {
            uint8_t memberIndex = GetMemberIndex(propId);
            status = intfInfo->handler->OnGetProperty(busAttachment, &reply, objInfo->path, memberIndex);
        } else {
            status = AJ_ERR_NULL;
        }
    }

    if (status != AJ_OK) {
        AJ_MarshalStatusMsg(msg, &reply, status);
        status = AJ_DeliverMsg(&reply);
    }

    return status;
}



static AJ_Status PropSetHandler(AJ_Message* msg, AJ_BusAttachment* busAttachment)
{
    uint32_t propId;
    const char* sig;
    AJ_Message reply;

    AJ_Status status = AJ_UnmarshalPropertyArgs(msg, &propId, &sig);
    if (status == AJ_OK) {
        const char* variant;
        AJ_UnmarshalVariant(msg, &variant);
        if (strcmp(sig, variant) != 0) {
            status = AJ_ERR_SIGNATURE;
        } else {
            uint8_t objIndex = GetObjectIndex(propId);
            uint8_t intfIndex = GetInterfaceIndex(propId);
            CdmObjectInfo* objInfo = GetObjectInfoByIndex(objIndex);
            CdmInterfaceInfo* intfInfo = GetInterfaceInfo(objInfo, intfIndex);
            
            if (objInfo && intfInfo && intfInfo->handler && intfInfo->handler->OnSetProperty) {
                uint8_t memberIndex = GetMemberIndex(propId);
                status = intfInfo->handler->OnSetProperty(busAttachment, msg, objInfo->path, memberIndex);
            } else {
                status = AJ_ERR_NULL;
            }
        }

        AJ_MarshalReplyMsg(msg, &reply);
    }

    if (status != AJ_OK) {
        AJ_MarshalStatusMsg(msg, &reply, status);
    }

    return AJ_DeliverMsg(&reply);
}



AJSVC_ServiceStatus Cdm_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status)
{
    if (!IsCdmMsg(msg->msgId)) {
        return AJSVC_SERVICE_STATUS_NOT_HANDLED;
    }

    uint8_t objIndex = GetObjectIndex(msg->msgId);
    uint8_t intfIndex = GetInterfaceIndex(msg->msgId);
    uint8_t memberIndex = GetMemberIndex(msg->msgId);

    if (intfIndex == (uint8_t)0) { /* org.freedesktop.DBus.Properties handling */
        if (memberIndex == AJ_PROP_GET) {
            *status = PropGetHandler(msg, busAttachment);
        } else if (memberIndex == AJ_PROP_SET) {
            *status = PropSetHandler(msg, busAttachment);
        } else {
            *status = AJ_ERR_INVALID;
        }
    } else { /* method */
        CdmObjectInfo* objInfo = GetObjectInfoByIndex(objIndex);
        CdmInterfaceInfo* intfInfo = GetInterfaceInfo(objInfo, intfIndex);

        if (*status == AJ_OK) {
            if (objInfo && intfInfo && intfInfo->handler && intfInfo->handler->OnMethodHandler) {
                if (*status == AJ_OK) {
                    *status = intfInfo->handler->OnMethodHandler(busAttachment, msg, objInfo->path, memberIndex);
                }
            } else {
                *status = AJ_ERR_NULL;
            }
        }
    }

    return AJSVC_SERVICE_STATUS_HANDLED;
}


void* GetInterfaceModel(const char* objPath, const char* intfName)
{
    CdmObjectInfo* objInfo = NULL;

    if (!objPath) {
        return NULL;
    }

    objInfo = GetObjectInfoByPath(objPath);
    if (objInfo) {
        CdmInterfaceInfo* intfInfo = objInfo->intfFirst;

        while (intfInfo) {
            if (!strcmp(intfInfo->name, intfName)) {
                break;
            }
            intfInfo = intfInfo->nextNode;
        }

        if (intfInfo) {
            return intfInfo->model;
        }
    }

    return NULL;
}


AJ_Status MakeMessageId(const char* objPath, const char* intfName, uint8_t memberIndex, uint32_t* msgId)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }
    if (!msgId) {
        return AJ_ERR_INVALID;
    }

    *msgId = CDM_OBJECT_LIST_INDEX << 24;

    uint8_t objIndex = -1;
    CdmObjectInfo* objInfo = objInfoFirst;
    while (objInfo) {
        objIndex++;

        if (!strcmp(objInfo->path, objPath)) {
            break;
        } else {
            objInfo = objInfo->nextNode;
        }
    }

    if (!objInfo) {
        return AJ_ERR_NO_MATCH;
    }

    *msgId |= (objIndex << 16);

    uint8_t intfIndex = 0;
    CdmInterfaceInfo* intfInfo = objInfo->intfFirst;
    while (intfInfo) {
        intfIndex++;
        if (!strcmp(intfInfo->name, intfName)) {
            break;
        } else {
            intfInfo = intfInfo->nextNode;
        }
    }

    if (!intfInfo) {
        return AJ_ERR_NO_MATCH;
    }

    *msgId |= (intfIndex << 8);
    *msgId |= memberIndex;

    return AJ_OK;
}



AJ_Status MakePropChangedId(const char* objPath, uint32_t* msgId)
{
    CdmObjectInfo* objInfo = objInfoFirst;
    uint8_t objIndex = -1;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }
    if (!msgId) {
        return AJ_ERR_INVALID;
    }

    *msgId = CDM_OBJECT_LIST_INDEX << 24;

    while (objInfo) {
        objIndex++;
        if (!strcmp(objInfo->path, objPath)) {
            break;
        }
        objInfo = objInfo->nextNode;
    }

    if (!objInfo) {
        return AJ_ERR_NO_MATCH;
    }

    *msgId |= (objIndex << 16);
    *msgId |= AJ_PROP_CHANGED;

    return AJ_OK;
}
