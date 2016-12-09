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

#ifndef _BASE_CONTROLLEE_SAMPLE_H_
#define _BASE_CONTROLLEE_SAMPLE_H_

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h.
 * The corresponding flag dbgCDMAPP is defined in the containing sample app.
 */
#define AJ_MODULE CDMAPP

#include <ajtcl/aj_debug.h>

AJ_EXPORT extern uint8_t dbgCDMAPP;

/**
 * Interrupt / volatile flags.
 */
extern volatile sig_atomic_t irqOccurred;	// Set this to trigger h/w interrupt callback in main loop.
extern volatile bool cdmModelsInitialised;

/**
 * Startup state utility structs.
 */
typedef struct {
	const char* mimeType;
	const uint8_t* content;
	size_t contentSize;
	const char* url;
} AboutIconParams;

typedef struct {
	const char* name;
	uint32_t busLinkTimeout;
	uint32_t connectTimeout;
	uint32_t connectPause;
	uint32_t preDisconnectPause;
	uint32_t postDisconnectPause;
} RoutingNodeParams;

typedef struct {
	const char* pskPrivateKey;
	const char* pskPublicKey;
	const char* spekePassword;
	const char* ecdsaPEMPrivateKey;
	const char* ecdsaPEMCertificate;
	uint32_t keyExpiration;
} DefaultAuthListenerCallbackParams;

typedef struct {
	AJ_Status (*AuthListenerCallback) (uint32_t authmechanism, uint32_t command, AJ_Credential* cred);
	const uint32_t* authSuites;
	size_t numAuthSuites;

	// If the callback, auth suites or numAuthSuites are zero, the defaults will be used along with
	// the values in this structure. Note that all parameters MUST be provided in this case, or
	// AJ_ERR_INVALID will be returned. Vendors should ideally roll their own implementation based
	// on all or a subset of the default callback.
	DefaultAuthListenerCallbackParams defaultCallbackParams;
} SecurityParams;

typedef struct {
	// Memset all unused members of this structure to zero in order to initialise them to defaults.

/**
 * Customisable callbacks.
 */
	// Callback called once upon successful connection to the Routing Node, and recalled on reboot.
 	// The bus attachment is initialised internally.
	AJ_Status (*AppConnectedHandler) (AJ_BusAttachment* busAttachment);

	// Callback called before application has disconnected from the Routing Node. Do not free the
	// bus attachment.
	AJ_Status (*AppDisconnectedHandler) (AJ_BusAttachment* busAttachment, uint8_t restart);

	// Callback called once per cycle of the main loop only while the application is connected to AllJoyn.
	// - Note that this is still called on the same frame as AppConnectedHandler.
	AJ_Status (*AppUpdateHandler) (AJ_BusAttachment* busAttachment);

	// Callback called per cycle of the message handling loop with messages not handled by CDM.
	AJSVC_ServiceStatus (*AppMessageProcessor) (AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status);
	
	// Callback called when a session has been accepted with another device.
	// - Note that there is no default handling of sessions being removed either by the Controllee or
	//   another device. The AppMessageProcessor must be overridden in this case.
	AJ_Status (*AppSessionAcceptedHandler) (uint16_t port, uint32_t sessionId, const char* joiner);

	// Callback called when the vendor application sets the global IRQ flag (irqOccurred) to true. This
	// allows for hardware interrupt handling to be performed within the same process (restricts only
	// the flag to being defined as volatile). This is called prior to the AppUpdateHandler.
	AJ_Status (*InterruptHandler) (AJ_BusAttachment* busAttachment);

	// Callback called once prior to main loop to instantiate the CDM interfaces for this Controllee device.
	AJ_Status (*InitCdmInterfaces) ();

	// Callback called in main loop to allow initialisation of interface state. This is called after
	// InitCdmInterfaces, and also recalled if the application reboots.
	AJ_Status (*InitCdmModels) (AJ_BusAttachment* busAttachment);
	
/**
 * Initial setup state.
 */
	AboutIconParams aboutIconParams;
	RoutingNodeParams routingNodeParams;
	SecurityParams securityParams;
	uint32_t sessionPort;
	uint32_t unmarshalTimeout;
	uint8_t maxInitAttempts;
	uint32_t failedInitReattemptTime;
} CDM_MainParams;

/**
 * Default application callback handlers.
 */
AJ_Status Cdm_DefaultAppConnectedHandler(AJ_BusAttachment* busAttachment);
AJ_Status Cdm_DefaultAppUpdateHandler(AJ_BusAttachment* busAttachment);
AJSVC_ServiceStatus Cdm_DefaultAppMessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status);
AJ_Status Cdm_DefaultAppSessionAcceptedHandler(uint16_t port, uint32_t sessionId, const char* joiner);
AJ_Status Cdm_DefaultAppDisconnectedHandler(AJ_BusAttachment* busAttachment, uint8_t restart);

/**
 * Utility main function with automatic AllJoyn / CDM setup and message handling loop.
 */
int CDM_Main(const CDM_MainParams* mainParams);

#endif /* _BASE_CONTROLLEE_SAMPLE_H_ */
