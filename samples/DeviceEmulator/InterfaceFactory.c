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

#include "InterfaceFactory.h"

#include <ajtcl/cdm/interfaces/operation/AirRecirculationModeModel.h>
#include "Models/operation/AirRecirculationModeModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/AlertsModel.h>
#include "Models/operation/AlertsModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/AudioVideoInputModel.h>
#include "Models/operation/AudioVideoInputModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/AudioVolumeModel.h>
#include "Models/operation/AudioVolumeModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/BatteryStatusModel.h>
#include "Models/operation/BatteryStatusModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/BrightnessModel.h>
#include "Models/operation/BrightnessModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/ChannelModel.h>
#include "Models/operation/ChannelModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/ClimateControlModeModel.h>
#include "Models/operation/ClimateControlModeModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/ClosedStatusModel.h>
#include "Models/operation/ClosedStatusModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/ColorModel.h>
#include "Models/operation/ColorModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/ColorTemperatureModel.h>
#include "Models/operation/ColorTemperatureModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/CurrentPowerModel.h>
#include "Models/operation/CurrentPowerModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/CycleControlModel.h>
#include "Models/operation/CycleControlModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/DishWashingCyclePhaseModel.h>
#include "Models/operation/DishWashingCyclePhaseModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/EnergyUsageModel.h>
#include "Models/operation/EnergyUsageModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/FanSpeedLevelModel.h>
#include "Models/operation/FanSpeedLevelModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/FilterStatusModel.h>
#include "Models/operation/FilterStatusModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/HeatingZoneModel.h>
#include "Models/operation/HeatingZoneModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/HvacFanModeModel.h>
#include "Models/operation/HvacFanModeModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/LaundryCyclePhaseModel.h>
#include "Models/operation/LaundryCyclePhaseModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/LockControlModel.h>
#include "Models/operation/LockControlModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/LockedStatusModel.h>
#include "Models/operation/LockedStatusModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/MoistureOutputLevelModel.h>
#include "Models/operation/MoistureOutputLevelModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/OffControlModel.h>
#include "Models/operation/OffControlModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/OnControlModel.h>
#include "Models/operation/OnControlModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/OnOffStatusModel.h>
#include "Models/operation/OnOffStatusModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/OvenCyclePhaseModel.h>
#include "Models/operation/OvenCyclePhaseModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/PlugInUnitsModel.h>
#include "Models/operation/PlugInUnitsModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/RapidModeModel.h>
#include "Models/operation/RapidModeModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/RapidModeTimedModel.h>
#include "Models/operation/RapidModeTimedModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/RemoteControllabilityModel.h>
#include "Models/operation/RemoteControllabilityModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/RepeatModeModel.h>
#include "Models/operation/RepeatModeModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/ResourceSavingModel.h>
#include "Models/operation/ResourceSavingModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/RobotCleaningCyclePhaseModel.h>
#include "Models/operation/RobotCleaningCyclePhaseModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/SoilLevelModel.h>
#include "Models/operation/SoilLevelModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/SpinSpeedLevelModel.h>
#include "Models/operation/SpinSpeedLevelModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/TimerModel.h>
#include "Models/operation/TimerModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/TriggerSensorModel.h>
#include "Models/operation/TriggerSensorModelImpl.h"
#include <ajtcl/cdm/interfaces/operation/UnlockControlModel.h>
#include "Models/operation/UnlockControlModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/CurrentAirQualityModel.h>
#include "Models/environment/CurrentAirQualityModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/CurrentAirQualityLevelModel.h>
#include "Models/environment/CurrentAirQualityLevelModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/CurrentHumidityModel.h>
#include "Models/environment/CurrentHumidityModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/CurrentTemperatureModel.h>
#include "Models/environment/CurrentTemperatureModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/TargetHumidityModel.h>
#include "Models/environment/TargetHumidityModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/TargetTemperatureModel.h>
#include "Models/environment/TargetTemperatureModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/TargetTemperatureLevelModel.h>
#include "Models/environment/TargetTemperatureLevelModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/WaterLevelModel.h>
#include "Models/environment/WaterLevelModelImpl.h"
#include <ajtcl/cdm/interfaces/environment/WindDirectionModel.h>
#include "Models/environment/WindDirectionModelImpl.h"

AJ_Status createInterface(const char* objPath, const char* ifaceName)
{

    if (strcmp(ifaceName, AIR_RECIRCULATION_MODE) == 0) {
        return Cdm_AddInterface(objPath, AIR_RECIRCULATION_MODE, intfDescOperationAirRecirculationMode, &intfHandlerOperationAirRecirculationMode, GetAirRecirculationModeModel());
    }

    if (strcmp(ifaceName, ALERTS) == 0) {
        return Cdm_AddInterface(objPath, ALERTS, intfDescOperationAlerts, &intfHandlerOperationAlerts, GetAlertsModel());
    }

    if (strcmp(ifaceName, AUDIO_VIDEO_INPUT) == 0) {
        return Cdm_AddInterface(objPath, AUDIO_VIDEO_INPUT, intfDescOperationAudioVideoInput, &intfHandlerOperationAudioVideoInput, GetAudioVideoInputModel());
    }

    if (strcmp(ifaceName, AUDIO_VOLUME) == 0) {
        return Cdm_AddInterface(objPath, AUDIO_VOLUME, intfDescOperationAudioVolume, &intfHandlerOperationAudioVolume, GetAudioVolumeModel());
    }

    if (strcmp(ifaceName, BATTERY_STATUS) == 0) {
        return Cdm_AddInterface(objPath, BATTERY_STATUS, intfDescOperationBatteryStatus, &intfHandlerOperationBatteryStatus, GetBatteryStatusModel());
    }

    if (strcmp(ifaceName, BRIGHTNESS) == 0) {
        return Cdm_AddInterface(objPath, BRIGHTNESS, intfDescOperationBrightness, &intfHandlerOperationBrightness, GetBrightnessModel());
    }

    if (strcmp(ifaceName, CHANNEL) == 0) {
        return Cdm_AddInterface(objPath, CHANNEL, intfDescOperationChannel, &intfHandlerOperationChannel, GetChannelModel());
    }

    if (strcmp(ifaceName, CLIMATE_CONTROL_MODE) == 0) {
        return Cdm_AddInterface(objPath, CLIMATE_CONTROL_MODE, intfDescOperationClimateControlMode, &intfHandlerOperationClimateControlMode, GetClimateControlModeModel());
    }

    if (strcmp(ifaceName, CLOSED_STATUS) == 0) {
        return Cdm_AddInterface(objPath, CLOSED_STATUS, intfDescOperationClosedStatus, &intfHandlerOperationClosedStatus, GetClosedStatusModel());
    }

    if (strcmp(ifaceName, COLOR) == 0) {
        return Cdm_AddInterface(objPath, COLOR, intfDescOperationColor, &intfHandlerOperationColor, GetColorModel());
    }

    if (strcmp(ifaceName, COLOR_TEMPERATURE) == 0) {
        return Cdm_AddInterface(objPath, COLOR_TEMPERATURE, intfDescOperationColorTemperature, &intfHandlerOperationColorTemperature, GetColorTemperatureModel());
    }

    if (strcmp(ifaceName, CURRENT_POWER) == 0) {
        return Cdm_AddInterface(objPath, CURRENT_POWER, intfDescOperationCurrentPower, &intfHandlerOperationCurrentPower, GetCurrentPowerModel());
    }

    if (strcmp(ifaceName, CYCLE_CONTROL) == 0) {
        return Cdm_AddInterface(objPath, CYCLE_CONTROL, intfDescOperationCycleControl, &intfHandlerOperationCycleControl, GetCycleControlModel());
    }

    if (strcmp(ifaceName, DISH_WASHING_CYCLE_PHASE) == 0) {
        return Cdm_AddInterface(objPath, DISH_WASHING_CYCLE_PHASE, intfDescOperationDishWashingCyclePhase, &intfHandlerOperationDishWashingCyclePhase, GetDishWashingCyclePhaseModel());
    }

    if (strcmp(ifaceName, ENERGY_USAGE) == 0) {
        return Cdm_AddInterface(objPath, ENERGY_USAGE, intfDescOperationEnergyUsage, &intfHandlerOperationEnergyUsage, GetEnergyUsageModel());
    }

    if (strcmp(ifaceName, FAN_SPEED_LEVEL) == 0) {
        return Cdm_AddInterface(objPath, FAN_SPEED_LEVEL, intfDescOperationFanSpeedLevel, &intfHandlerOperationFanSpeedLevel, GetFanSpeedLevelModel());
    }

    if (strcmp(ifaceName, FILTER_STATUS) == 0) {
        return Cdm_AddInterface(objPath, FILTER_STATUS, intfDescOperationFilterStatus, &intfHandlerOperationFilterStatus, GetFilterStatusModel());
    }

    if (strcmp(ifaceName, HEATING_ZONE) == 0) {
        return Cdm_AddInterface(objPath, HEATING_ZONE, intfDescOperationHeatingZone, &intfHandlerOperationHeatingZone, GetHeatingZoneModel());
    }

    if (strcmp(ifaceName, HVAC_FAN_MODE) == 0) {
        return Cdm_AddInterface(objPath, HVAC_FAN_MODE, intfDescOperationHvacFanMode, &intfHandlerOperationHvacFanMode, GetHvacFanModeModel());
    }

    if (strcmp(ifaceName, LAUNDRY_CYCLE_PHASE) == 0) {
        return Cdm_AddInterface(objPath, LAUNDRY_CYCLE_PHASE, intfDescOperationLaundryCyclePhase, &intfHandlerOperationLaundryCyclePhase, GetLaundryCyclePhaseModel());
    }

    if (strcmp(ifaceName, LOCK_CONTROL) == 0) {
        return Cdm_AddInterface(objPath, LOCK_CONTROL, intfDescOperationLockControl, &intfHandlerOperationLockControl, GetLockControlModel());
    }

    if (strcmp(ifaceName, LOCKED_STATUS) == 0) {
        return Cdm_AddInterface(objPath, LOCKED_STATUS, intfDescOperationLockedStatus, &intfHandlerOperationLockedStatus, GetLockedStatusModel());
    }

    if (strcmp(ifaceName, MOISTURE_OUTPUT_LEVEL) == 0) {
        return Cdm_AddInterface(objPath, MOISTURE_OUTPUT_LEVEL, intfDescOperationMoistureOutputLevel, &intfHandlerOperationMoistureOutputLevel, GetMoistureOutputLevelModel());
    }

    if (strcmp(ifaceName, OFF_CONTROL) == 0) {
        return Cdm_AddInterface(objPath, OFF_CONTROL, intfDescOperationOffControl, &intfHandlerOperationOffControl, GetOffControlModel());
    }

    if (strcmp(ifaceName, ON_CONTROL) == 0) {
        return Cdm_AddInterface(objPath, ON_CONTROL, intfDescOperationOnControl, &intfHandlerOperationOnControl, GetOnControlModel());
    }

    if (strcmp(ifaceName, ON_OFF_STATUS) == 0) {
        return Cdm_AddInterface(objPath, ON_OFF_STATUS, intfDescOperationOnOffStatus, &intfHandlerOperationOnOffStatus, GetOnOffStatusModel());
    }

    if (strcmp(ifaceName, OVEN_CYCLE_PHASE) == 0) {
        return Cdm_AddInterface(objPath, OVEN_CYCLE_PHASE, intfDescOperationOvenCyclePhase, &intfHandlerOperationOvenCyclePhase, GetOvenCyclePhaseModel());
    }

    if (strcmp(ifaceName, PLUG_IN_UNITS) == 0) {
        return Cdm_AddInterface(objPath, PLUG_IN_UNITS, intfDescOperationPlugInUnits, &intfHandlerOperationPlugInUnits, GetPlugInUnitsModel());
    }

    if (strcmp(ifaceName, RAPID_MODE) == 0) {
        return Cdm_AddInterface(objPath, RAPID_MODE, intfDescOperationRapidMode, &intfHandlerOperationRapidMode, GetRapidModeModel());
    }

    if (strcmp(ifaceName, RAPID_MODE_TIMED) == 0) {
        return Cdm_AddInterface(objPath, RAPID_MODE_TIMED, intfDescOperationRapidModeTimed, &intfHandlerOperationRapidModeTimed, GetRapidModeTimedModel());
    }

    if (strcmp(ifaceName, REMOTE_CONTROLLABILITY) == 0) {
        return Cdm_AddInterface(objPath, REMOTE_CONTROLLABILITY, intfDescOperationRemoteControllability, &intfHandlerOperationRemoteControllability, GetRemoteControllabilityModel());
    }

    if (strcmp(ifaceName, REPEAT_MODE) == 0) {
        return Cdm_AddInterface(objPath, REPEAT_MODE, intfDescOperationRepeatMode, &intfHandlerOperationRepeatMode, GetRepeatModeModel());
    }

    if (strcmp(ifaceName, RESOURCE_SAVING) == 0) {
        return Cdm_AddInterface(objPath, RESOURCE_SAVING, intfDescOperationResourceSaving, &intfHandlerOperationResourceSaving, GetResourceSavingModel());
    }

    if (strcmp(ifaceName, ROBOT_CLEANING_CYCLE_PHASE) == 0) {
        return Cdm_AddInterface(objPath, ROBOT_CLEANING_CYCLE_PHASE, intfDescOperationRobotCleaningCyclePhase, &intfHandlerOperationRobotCleaningCyclePhase, GetRobotCleaningCyclePhaseModel());
    }

    if (strcmp(ifaceName, SOIL_LEVEL) == 0) {
        return Cdm_AddInterface(objPath, SOIL_LEVEL, intfDescOperationSoilLevel, &intfHandlerOperationSoilLevel, GetSoilLevelModel());
    }

    if (strcmp(ifaceName, SPIN_SPEED_LEVEL) == 0) {
        return Cdm_AddInterface(objPath, SPIN_SPEED_LEVEL, intfDescOperationSpinSpeedLevel, &intfHandlerOperationSpinSpeedLevel, GetSpinSpeedLevelModel());
    }

    if (strcmp(ifaceName, TIMER) == 0) {
        return Cdm_AddInterface(objPath, TIMER, intfDescOperationTimer, &intfHandlerOperationTimer, GetTimerModel());
    }

    if (strcmp(ifaceName, TRIGGER_SENSOR) == 0) {
        return Cdm_AddInterface(objPath, TRIGGER_SENSOR, intfDescOperationTriggerSensor, &intfHandlerOperationTriggerSensor, GetTriggerSensorModel());
    }

    if (strcmp(ifaceName, UNLOCK_CONTROL) == 0) {
        return Cdm_AddInterface(objPath, UNLOCK_CONTROL, intfDescOperationUnlockControl, &intfHandlerOperationUnlockControl, GetUnlockControlModel());
    }

    if (strcmp(ifaceName, CURRENT_AIR_QUALITY) == 0) {
        return Cdm_AddInterface(objPath, CURRENT_AIR_QUALITY, intfDescEnvironmentCurrentAirQuality, &intfHandlerEnvironmentCurrentAirQuality, GetCurrentAirQualityModel());
    }

    if (strcmp(ifaceName, CURRENT_AIR_QUALITY_LEVEL) == 0) {
        return Cdm_AddInterface(objPath, CURRENT_AIR_QUALITY_LEVEL, intfDescEnvironmentCurrentAirQualityLevel, &intfHandlerEnvironmentCurrentAirQualityLevel, GetCurrentAirQualityLevelModel());
    }

    if (strcmp(ifaceName, CURRENT_HUMIDITY) == 0) {
        return Cdm_AddInterface(objPath, CURRENT_HUMIDITY, intfDescEnvironmentCurrentHumidity, &intfHandlerEnvironmentCurrentHumidity, GetCurrentHumidityModel());
    }

    if (strcmp(ifaceName, CURRENT_TEMPERATURE) == 0) {
        return Cdm_AddInterface(objPath, CURRENT_TEMPERATURE, intfDescEnvironmentCurrentTemperature, &intfHandlerEnvironmentCurrentTemperature, GetCurrentTemperatureModel());
    }

    if (strcmp(ifaceName, TARGET_HUMIDITY) == 0) {
        return Cdm_AddInterface(objPath, TARGET_HUMIDITY, intfDescEnvironmentTargetHumidity, &intfHandlerEnvironmentTargetHumidity, GetTargetHumidityModel());
    }

    if (strcmp(ifaceName, TARGET_TEMPERATURE) == 0) {
        return Cdm_AddInterface(objPath, TARGET_TEMPERATURE, intfDescEnvironmentTargetTemperature, &intfHandlerEnvironmentTargetTemperature, GetTargetTemperatureModel());
    }

    if (strcmp(ifaceName, TARGET_TEMPERATURE_LEVEL) == 0) {
        return Cdm_AddInterface(objPath, TARGET_TEMPERATURE_LEVEL, intfDescEnvironmentTargetTemperatureLevel, &intfHandlerEnvironmentTargetTemperatureLevel, GetTargetTemperatureLevelModel());
    }

    if (strcmp(ifaceName, WATER_LEVEL) == 0) {
        return Cdm_AddInterface(objPath, WATER_LEVEL, intfDescEnvironmentWaterLevel, &intfHandlerEnvironmentWaterLevel, GetWaterLevelModel());
    }

    if (strcmp(ifaceName, WIND_DIRECTION) == 0) {
        return Cdm_AddInterface(objPath, WIND_DIRECTION, intfDescEnvironmentWindDirection, &intfHandlerEnvironmentWindDirection, GetWindDirectionModel());
    }
    return AJ_ERR_INVALID;
}

