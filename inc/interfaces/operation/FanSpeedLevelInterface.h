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

#ifndef FANSPEEDLEVELINTERFACE_H_
#define FANSPEEDLEVELINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define FAN_SPEED_LEVEL "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel"

/**
 * FanSpeedLevel interface members
 */
typedef enum {
    FANSPEEDLEVEL_PROP_VERSION = 0,
    FANSPEEDLEVEL_PROP_FAN_SPEED_LEVEL,
    FANSPEEDLEVEL_PROP_MAX_FAN_SPEED_LEVEL,
    FANSPEEDLEVEL_PROP_AUTO_MODE,
    FANSPEEDLEVEL_MEMBER_COUNT
} FanSpeedLevelMembers;


typedef enum {
    FANSPEEDLEVEL_AUTO_MODE_OFF = 0x00,
    FANSPEEDLEVEL_AUTO_MODE_ON = 0x01,
    FANSPEEDLEVEL_AUTO_MODE_NOT_SUPPORTED = 0xFF
} FanSpeedLevel_AutoMode;


typedef struct {
    FanSpeedLevel_AutoMode* elems;
    size_t numElems;
} Array_FanSpeedLevel_AutoMode;


/**
 *  Initialise an array of AutoMode.
 */
extern void InitArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value, size_t numElems);

/**
 *  Copy an array of AutoMode.
 */
extern void CopyArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value, Array_FanSpeedLevel_AutoMode* copy);

/**
 *  Free an array of AutoMode.
 */
extern void FreeArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value);

/**
 *  Extend an array of AutoMode.
 */
extern size_t ExtendArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value, size_t numElems);



extern const char* const intfDescOperationFanSpeedLevel[FANSPEEDLEVEL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationFanSpeedLevel;


/**
 * Emits a changed signal for the FanSpeedLevel property
 * @param[in] newValue new value of fan speed level
 * @return ER_OK on success
 */
AJ_Status Cdm_FanSpeedLevel_EmitFanSpeedLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the AutoMode property
 * @param[in] newValue new value of auto mode
 * @return ER_OK on success
 */
AJ_Status Cdm_FanSpeedLevel_EmitAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, FanSpeedLevel_AutoMode newValue);

#endif /* FANSPEEDLEVELINTERFACE_H_ */