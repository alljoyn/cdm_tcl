/**
 * @file
 */
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

#ifndef LAUNDRYCYCLEPHASE_H_
#define LAUNDRYCYCLEPHASE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

/**
 * LaundryCyclePhaseCyclePhaseDescriptor struct
 */
typedef struct {
    uint8_t phase;
    char* name;
    char* description;
} LaundryCyclePhaseCyclePhaseDescriptor;

/**
 * LaundryCyclePhase interface listener
 */
typedef struct {
    /**
     * Handler for getting CyclePhase property
     * @param[in] objPath object path
     * @param[out] cyclePhase Current cycle phase
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetCyclePhase) (const char* objPath, uint8_t* cyclePhase);

    /**
     * Handler for getting SupportedCyclePhases property
     * @param[in] objPath object path
     * @param[out] supportedCyclePhases List of supported cycle phases
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSupportedCyclePhases) (const char* objPath, uint8_t* supportedCyclePhases);

    /**
     * Handler for GetVendorPhasesDescription method
     * @param[in] objPath object path
     * @param[in] languageTag Preferred language to be used in selecting the output strings
     * @param[out] phasesDescription Cycle phases description
     * @param[out] numReturnedRecords the number of returned CyclePhaseDescriptor info records
     * @param[out] errorCode error code
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetVendorPhasesDescription) (const char* objPath, const char* languageTag, LaundryCyclePhaseCyclePhaseDescriptor** phasesDescription,
                                               uint16_t* numReturnedRecords, ErrorCode* errorCode);
} LaundryCyclePhaseListener;

/**
 * Get cyclePhase of LaundryCyclePhase interface
 * @param[in] objPath the object path including the interface
 * @param[out] cyclePhase Current cycle phase
 * @return AJ_OK on success
 */
AJ_Status Cdm_LaundryCyclePhaseInterfaceGetCyclePhase(const char* objPath, uint8_t* cyclePhase);

/**
 * Set cyclePhase of LaundryCyclePhase interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] cyclePhase Current cycle phase
 * @return AJ_OK on success
 */

AJ_Status Cdm_LaundryCyclePhaseInterfaceSetCyclePhase(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t cyclePhase);
/**
 * Get supportedCyclePhases of LaundryCyclePhase interface
 * @param[in] objPath the object path including the interface
 * @param[out] supportedCyclePhases List of supported cycle phases
 * @return AJ_OK on success
 */
AJ_Status Cdm_LaundryCyclePhaseInterfaceGetSupportedCyclePhases(const char* objPath, uint8_t* supportedCyclePhases);

/**
 * Set supportedCyclePhases of LaundryCyclePhase interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] supportedCyclePhases List of supported cycle phases
 * @param[in] supportedCyclePhasesListSize SupportedCyclePhases size
 * @return AJ_OK on success
 */
AJ_Status Cdm_LaundryCyclePhaseInterfaceSetSupportedCyclePhases(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t* supportedCyclePhases, const size_t supportedCyclePhasesListSize);

#endif /* LAUNDRYCYCLEPHASE_H_ */
