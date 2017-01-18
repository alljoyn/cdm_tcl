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

#include <string.h>
#include <ajtcl/cdm/CdmControllee.h>
#include "DeviceCommand.h"

#include "Models/input/HidModelImpl.h"
#include "Models/environment/CurrentAirQualityModelImpl.h"
#include "Models/environment/CurrentAirQualityLevelModelImpl.h"
#include "Models/environment/CurrentHumidityModelImpl.h"
#include "Models/environment/CurrentTemperatureModelImpl.h"
#include "Models/environment/TargetHumidityModelImpl.h"
#include "Models/environment/TargetTemperatureModelImpl.h"
#include "Models/environment/TargetTemperatureLevelModelImpl.h"
#include "Models/environment/WaterLevelModelImpl.h"
#include "Models/environment/WindDirectionModelImpl.h"
#include "Models/operation/AirRecirculationModeModelImpl.h"
#include "Models/operation/AlertsModelImpl.h"
#include "Models/operation/AudioVideoInputModelImpl.h"
#include "Models/operation/AudioVolumeModelImpl.h"
#include "Models/operation/BatteryStatusModelImpl.h"
#include "Models/operation/BrightnessModelImpl.h"
#include "Models/operation/ChannelModelImpl.h"
#include "Models/operation/ClimateControlModeModelImpl.h"
#include "Models/operation/ClosedStatusModelImpl.h"
#include "Models/operation/ColorModelImpl.h"
#include "Models/operation/ColorTemperatureModelImpl.h"
#include "Models/operation/CurrentPowerModelImpl.h"
#include "Models/operation/CycleControlModelImpl.h"
#include "Models/operation/DishWashingCyclePhaseModelImpl.h"
#include "Models/operation/EnergyUsageModelImpl.h"
#include "Models/operation/FanSpeedLevelModelImpl.h"
#include "Models/operation/FilterStatusModelImpl.h"
#include "Models/operation/HeatingZoneModelImpl.h"
#include "Models/operation/HvacFanModeModelImpl.h"
#include "Models/operation/LaundryCyclePhaseModelImpl.h"
#include "Models/operation/LockControlModelImpl.h"
#include "Models/operation/LockedStatusModelImpl.h"
#include "Models/operation/MoistureOutputLevelModelImpl.h"
#include "Models/operation/OffControlModelImpl.h"
#include "Models/operation/OnControlModelImpl.h"
#include "Models/operation/OnOffStatusModelImpl.h"
#include "Models/operation/OvenCyclePhaseModelImpl.h"
#include "Models/operation/PlugInUnitsModelImpl.h"
#include "Models/operation/RapidModeModelImpl.h"
#include "Models/operation/RapidModeTimedModelImpl.h"
#include "Models/operation/RemoteControllabilityModelImpl.h"
#include "Models/operation/RepeatModeModelImpl.h"
#include "Models/operation/ResourceSavingModelImpl.h"
#include "Models/operation/RobotCleaningCyclePhaseModelImpl.h"
#include "Models/operation/SoilLevelModelImpl.h"
#include "Models/operation/SpinSpeedLevelModelImpl.h"
#include "Models/operation/TimerModelImpl.h"
#include "Models/operation/TriggerSensorModelImpl.h"
#include "Models/operation/UnlockControlModelImpl.h"
#include "Models/userinterfacesettings/LanguageDisplayModelImpl.h"
#include "Models/userinterfacesettings/TemperatureDisplayModelImpl.h"
#include "Models/userinterfacesettings/TimeDisplayModelImpl.h"


/*======================================================================*/

static AJ_Status HandleChanged(const Command* cmd)
{
    AJ_Status status = AJ_OK;
    void* context = GetInterfaceModel(cmd->objPath, cmd->interface);
    if (strcmp(cmd->interface, "org.alljoyn.Input.Hid") == 0)
    {
        status = HandleHidCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality") == 0)
    {
        status = HandleCurrentAirQualityCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel") == 0)
    {
        status = HandleCurrentAirQualityLevelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentHumidity") == 0)
    {
        status = HandleCurrentHumidityCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentTemperature") == 0)
    {
        status = HandleCurrentTemperatureCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.TargetHumidity") == 0)
    {
        status = HandleTargetHumidityCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.TargetTemperature") == 0)
    {
        status = HandleTargetTemperatureCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel") == 0)
    {
        status = HandleTargetTemperatureLevelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.WaterLevel") == 0)
    {
        status = HandleWaterLevelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.WindDirection") == 0)
    {
        status = HandleWindDirectionCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.AirRecirculationMode") == 0)
    {
        status = HandleAirRecirculationModeCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Alerts") == 0)
    {
        status = HandleAlertsCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput") == 0)
    {
        status = HandleAudioVideoInputCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.AudioVolume") == 0)
    {
        status = HandleAudioVolumeCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.BatteryStatus") == 0)
    {
        status = HandleBatteryStatusCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Brightness") == 0)
    {
        status = HandleBrightnessCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Channel") == 0)
    {
        status = HandleChannelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode") == 0)
    {
        status = HandleClimateControlModeCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.ClosedStatus") == 0)
    {
        status = HandleClosedStatusCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Color") == 0)
    {
        status = HandleColorCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.ColorTemperature") == 0)
    {
        status = HandleColorTemperatureCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.CurrentPower") == 0)
    {
        status = HandleCurrentPowerCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.CycleControl") == 0)
    {
        status = HandleCycleControlCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase") == 0)
    {
        status = HandleDishWashingCyclePhaseCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.EnergyUsage") == 0)
    {
        status = HandleEnergyUsageCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel") == 0)
    {
        status = HandleFanSpeedLevelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.FilterStatus") == 0)
    {
        status = HandleFilterStatusCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.HeatingZone") == 0)
    {
        status = HandleHeatingZoneCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.HvacFanMode") == 0)
    {
        status = HandleHvacFanModeCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase") == 0)
    {
        status = HandleLaundryCyclePhaseCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.LockControl") == 0)
    {
        status = HandleLockControlCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.LockedStatus") == 0)
    {
        status = HandleLockedStatusCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel") == 0)
    {
        status = HandleMoistureOutputLevelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.OffControl") == 0)
    {
        status = HandleOffControlCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.OnControl") == 0)
    {
        status = HandleOnControlCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.OnOffStatus") == 0)
    {
        status = HandleOnOffStatusCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.OvenCyclePhase") == 0)
    {
        status = HandleOvenCyclePhaseCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.PlugInUnits") == 0)
    {
        status = HandlePlugInUnitsCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.RapidMode") == 0)
    {
        status = HandleRapidModeCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.RapidModeTimed") == 0)
    {
        status = HandleRapidModeTimedCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.RemoteControllability") == 0)
    {
        status = HandleRemoteControllabilityCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.RepeatMode") == 0)
    {
        status = HandleRepeatModeCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.ResourceSaving") == 0)
    {
        status = HandleResourceSavingCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase") == 0)
    {
        status = HandleRobotCleaningCyclePhaseCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.SoilLevel") == 0)
    {
        status = HandleSoilLevelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel") == 0)
    {
        status = HandleSpinSpeedLevelCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Timer") == 0)
    {
        status = HandleTimerCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.TriggerSensor") == 0)
    {
        status = HandleTriggerSensorCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.UnlockControl") == 0)
    {
        status = HandleUnlockControlCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay") == 0)
    {
        status = HandleLanguageDisplayCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay") == 0)
    {
        status = HandleTemperatureDisplayCommand(cmd, context);
    }
    else
    if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay") == 0)
    {
        status = HandleTimeDisplayCommand(cmd, context);
    }
    else
    {
        status = AJ_ERR_FAILURE;
    }

    return status;
}



AJ_Status DeviceCommandHandler(const Command* cmd)
{
    AJ_Status status = AJ_OK;

    if (strcmp(cmd->name, "changed") == 0)
    {
        status = HandleChanged(cmd);
    }
    else
    {
        fprintf(stderr, "Error: unrecognised command %s\n", cmd->name);
        status = AJ_ERR_FAILURE;
    }

    return status;
}

