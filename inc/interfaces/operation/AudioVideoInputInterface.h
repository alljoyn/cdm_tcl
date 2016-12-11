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

#ifndef AUDIOVIDEOINPUTINTERFACE_H_
#define AUDIOVIDEOINPUTINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define AUDIO_VIDEO_INPUT "org.alljoyn.SmartSpaces.Operation.AudioVideoInput"

/**
 * AudioVideoInput interface members
 */
typedef enum {
    AUDIOVIDEOINPUT_PROP_VERSION = 0,
    AUDIOVIDEOINPUT_PROP_INPUT_SOURCE_ID,
    AUDIOVIDEOINPUT_PROP_SUPPORTED_INPUT_SOURCES,
    AUDIOVIDEOINPUT_MEMBER_COUNT
} AudioVideoInputMembers;


typedef enum {
    AUDIOVIDEOINPUT_SOURCE_TYPE_UNKNOWN = 0,
    AUDIOVIDEOINPUT_SOURCE_TYPE_TUNER = 1,
    AUDIOVIDEOINPUT_SOURCE_TYPE_COMPONENT = 2,
    AUDIOVIDEOINPUT_SOURCE_TYPE_COMPOSITE = 3,
    AUDIOVIDEOINPUT_SOURCE_TYPE_S_VIDEO = 4,
    AUDIOVIDEOINPUT_SOURCE_TYPE_RGB = 5,
    AUDIOVIDEOINPUT_SOURCE_TYPE_SDI = 6,
    AUDIOVIDEOINPUT_SOURCE_TYPE_DVI = 7,
    AUDIOVIDEOINPUT_SOURCE_TYPE_HDMI = 8,
    AUDIOVIDEOINPUT_SOURCE_TYPE_DISPLAY_PORT = 9,
    AUDIOVIDEOINPUT_SOURCE_TYPE_SCART = 10,
    AUDIOVIDEOINPUT_SOURCE_TYPE_EXTERNAL_STORAGE = 11,
    AUDIOVIDEOINPUT_SOURCE_TYPE_NETWORK = 12,
    AUDIOVIDEOINPUT_SOURCE_TYPE_ANALOG = 13,
    AUDIOVIDEOINPUT_SOURCE_TYPE_PHONO = 14,
    AUDIOVIDEOINPUT_SOURCE_TYPE_SPDIF_COAXIAL = 15,
    AUDIOVIDEOINPUT_SOURCE_TYPE_SPDIF_OPTICAL = 16
} AudioVideoInput_SourceType;


typedef struct {
    AudioVideoInput_SourceType* elems;
    size_t numElems;
} Array_AudioVideoInput_SourceType;


/**
 *  Initialise an array of SourceType.
 */
extern void InitArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value, size_t numElems);

/**
 *  Copy an array of SourceType.
 */
extern void CopyArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value, Array_AudioVideoInput_SourceType* copy);

/**
 *  Free an array of SourceType.
 */
extern void FreeArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value);

/**
 *  Extend an array of SourceType.
 */
extern size_t ExtendArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value, size_t numElems);


typedef enum {
    AUDIOVIDEOINPUT_SIGNAL_PRESENCE_UNKNOWN = 0,
    AUDIOVIDEOINPUT_SIGNAL_PRESENCE_SIGNAL_PRESENT = 1,
    AUDIOVIDEOINPUT_SIGNAL_PRESENCE_SIGNAL_ABSENT = 2
} AudioVideoInput_SignalPresence;


typedef struct {
    AudioVideoInput_SignalPresence* elems;
    size_t numElems;
} Array_AudioVideoInput_SignalPresence;


/**
 *  Initialise an array of SignalPresence.
 */
extern void InitArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value, size_t numElems);

/**
 *  Copy an array of SignalPresence.
 */
extern void CopyArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value, Array_AudioVideoInput_SignalPresence* copy);

/**
 *  Free an array of SignalPresence.
 */
extern void FreeArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value);

/**
 *  Extend an array of SignalPresence.
 */
extern size_t ExtendArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value, size_t numElems);



typedef struct {
    uint16_t id;
    AudioVideoInput_SourceType sourceType;
    AudioVideoInput_SignalPresence signalPresence;
    uint16_t portNumber;
    char const* friendlyName;
} AudioVideoInput_InputSource;


typedef struct {
    AudioVideoInput_InputSource* elems;
    size_t numElems;
} Array_AudioVideoInput_InputSource;

/**
 *  Free the fields in the InputSource but not the struct itself.
 */
extern void FreeFields_AudioVideoInput_InputSource(AudioVideoInput_InputSource* value);

/**
 *  Free an array of InputSource.
 */
extern void FreeArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value);

/**
 *  Initialise an array of InputSource.
 */
extern void InitArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value, size_t numElems);

/**
 *  Copy an array of InputSource.
 */
extern void CopyArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value, Array_AudioVideoInput_InputSource* copy);

/**
 *  Extend an array of InputSource.
 */
extern size_t ExtendArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value, size_t numElems);


extern const char* const intfDescOperationAudioVideoInput[AUDIOVIDEOINPUT_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationAudioVideoInput;


/**
 * Emits a changed signal for the InputSourceId property
 * @param[in] newValue new value of input source id
 * @return ER_OK on success
 */
AJ_Status Cdm_AudioVideoInput_EmitInputSourceIdChanged(AJ_BusAttachment *bus, const char *objPath, AudioVideoInput_SourceType newValue);

/**
 * Emits a changed signal for the SupportedInputSources property
 * @param[in] newValue new value of supported input sources
 * @return ER_OK on success
 */
AJ_Status Cdm_AudioVideoInput_EmitSupportedInputSourcesChanged(AJ_BusAttachment *bus, const char *objPath, Array_AudioVideoInput_InputSource newValue);

#endif /* AUDIOVIDEOINPUTINTERFACE_H_ */