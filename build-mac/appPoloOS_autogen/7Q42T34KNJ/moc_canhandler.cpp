/****************************************************************************
** Meta object code from reading C++ file 'canhandler.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/can/canhandler.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10CanHandlerE_t {};
} // unnamed namespace

template <> constexpr inline auto CanHandler::qt_create_metaobjectdata<qt_meta_tag_ZN10CanHandlerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CanHandler",
        "engineMetricChanged",
        "",
        "engineFlagChanged",
        "speedChanged",
        "gearChanged",
        "steeringAngleChanged",
        "wheelSpeedChanged",
        "safetyChanged",
        "brakeChanged",
        "handbrakeChanged",
        "lockStatusChanged",
        "doorChanged",
        "windowChanged",
        "windshieldChanged",
        "beltChanged",
        "tempChanged",
        "elecChanged",
        "fuelLevelChanged",
        "fuelChanged",
        "diagChanged",
        "ecuStatusChanged",
        "mileageChanged",
        "blinkerChanged",
        "wiperChanged",
        "lightChanged",
        "acChanged",
        "lightsChanged",
        "absChanged",
        "epcChanged",
        "checkEngineChanged",
        "glowPlugChanged",
        "batteryWarningChanged",
        "setRpm",
        "v",
        "setSpeed",
        "setGear",
        "setIgnitionOn",
        "setEngineRunning",
        "setEngineLoad",
        "setThrottlePos",
        "setPedalPos",
        "setTorqueActual",
        "setTorqueRequest",
        "setIdleState",
        "setCruiseActive",
        "setLimpMode",
        "setOverheat",
        "setSteeringAngle",
        "setWheelFL",
        "setWheelFR",
        "setWheelRL",
        "setWheelRR",
        "setAbsActive",
        "setEspActive",
        "setTractionActive",
        "setBrakePressed",
        "setHandbrake",
        "setIsLocked",
        "setDoorFL",
        "setDoorFR",
        "setDoorRL",
        "setDoorRR",
        "setTrunk",
        "setWindshieldHeater",
        "setWindowPos",
        "setBeltDriver",
        "setBeltPassenger",
        "setTempCoolant",
        "setTempOil",
        "setTempAmbient",
        "setTempIntake",
        "setTempFuel",
        "setBatteryVoltage",
        "setAltCharging",
        "setRangePossible",
        "setFuelToFill",
        "setFuelInst",
        "setFuelAvg",
        "setBusEngineActive",
        "setBusComfortActive",
        "setEngineFps",
        "setComfortFps",
        "setErrorFrames",
        "setLastFaultCode",
        "setEcuEngineOnline",
        "setEcuAbsOnline",
        "setEcuBodyOnline",
        "setBlinkerStatus",
        "setWiperLevel",
        "setInteriorLight",
        "setAcActive",
        "setPosLights",
        "setLowBeam",
        "setHighBeam",
        "setEpcActive",
        "setCheckEngine",
        "setGlowPlug",
        "setBatteryWarning",
        "rpm",
        "speed",
        "gear",
        "ignitionOn",
        "engineRunning",
        "engineLoad",
        "throttlePos",
        "pedalPos",
        "torqueActual",
        "torqueRequest",
        "idleState",
        "cruiseActive",
        "limpMode",
        "overheat",
        "steeringAngle",
        "wheelFL",
        "wheelFR",
        "wheelRL",
        "wheelRR",
        "absActive",
        "espActive",
        "tractionActive",
        "brakePressed",
        "handbrake",
        "isLocked",
        "anyDoorOpen",
        "doorFL",
        "doorFR",
        "doorRL",
        "doorRR",
        "trunk",
        "windowPos",
        "windshieldHeater",
        "beltDriver",
        "beltPassenger",
        "blinkerStatus",
        "wiperLevel",
        "interiorLight",
        "acActive",
        "tempCoolant",
        "tempOil",
        "tempAmbient",
        "tempIntake",
        "tempFuel",
        "batteryVoltage",
        "altCharging",
        "rangePossible",
        "fuelToFill",
        "fuelInst",
        "fuelAvg",
        "busEngineActive",
        "busComfortActive",
        "engineFps",
        "comfortFps",
        "errorFrames",
        "lastFaultCode",
        "ecuEngineOnline",
        "ecuAbsOnline",
        "ecuBodyOnline",
        "vin",
        "mileage",
        "gitHash",
        "buildDate",
        "posLights",
        "lowBeam",
        "highBeam",
        "epcActive",
        "checkEngine",
        "glowPlug",
        "batteryWarning"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'engineMetricChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'engineFlagChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'speedChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gearChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'steeringAngleChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'wheelSpeedChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'safetyChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'brakeChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'handbrakeChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lockStatusChanged'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'doorChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'windowChanged'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'windshieldChanged'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'beltChanged'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tempChanged'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'elecChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fuelLevelChanged'
        QtMocHelpers::SignalData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fuelChanged'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'diagChanged'
        QtMocHelpers::SignalData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'ecuStatusChanged'
        QtMocHelpers::SignalData<void()>(21, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mileageChanged'
        QtMocHelpers::SignalData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'blinkerChanged'
        QtMocHelpers::SignalData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'wiperChanged'
        QtMocHelpers::SignalData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lightChanged'
        QtMocHelpers::SignalData<void()>(25, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'acChanged'
        QtMocHelpers::SignalData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lightsChanged'
        QtMocHelpers::SignalData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'absChanged'
        QtMocHelpers::SignalData<void()>(28, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'epcChanged'
        QtMocHelpers::SignalData<void()>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'checkEngineChanged'
        QtMocHelpers::SignalData<void()>(30, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'glowPlugChanged'
        QtMocHelpers::SignalData<void()>(31, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'batteryWarningChanged'
        QtMocHelpers::SignalData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setRpm'
        QtMocHelpers::SlotData<void(int)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setSpeed'
        QtMocHelpers::SlotData<void(int)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setGear'
        QtMocHelpers::SlotData<void(int)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setIgnitionOn'
        QtMocHelpers::SlotData<void(bool)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setEngineRunning'
        QtMocHelpers::SlotData<void(bool)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setEngineLoad'
        QtMocHelpers::SlotData<void(int)>(39, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setThrottlePos'
        QtMocHelpers::SlotData<void(int)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setPedalPos'
        QtMocHelpers::SlotData<void(int)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setTorqueActual'
        QtMocHelpers::SlotData<void(double)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setTorqueRequest'
        QtMocHelpers::SlotData<void(double)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setIdleState'
        QtMocHelpers::SlotData<void(bool)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setCruiseActive'
        QtMocHelpers::SlotData<void(bool)>(45, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setLimpMode'
        QtMocHelpers::SlotData<void(bool)>(46, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setOverheat'
        QtMocHelpers::SlotData<void(bool)>(47, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setSteeringAngle'
        QtMocHelpers::SlotData<void(double)>(48, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setWheelFL'
        QtMocHelpers::SlotData<void(double)>(49, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setWheelFR'
        QtMocHelpers::SlotData<void(double)>(50, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setWheelRL'
        QtMocHelpers::SlotData<void(double)>(51, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setWheelRR'
        QtMocHelpers::SlotData<void(double)>(52, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setAbsActive'
        QtMocHelpers::SlotData<void(bool)>(53, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setEspActive'
        QtMocHelpers::SlotData<void(bool)>(54, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setTractionActive'
        QtMocHelpers::SlotData<void(bool)>(55, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setBrakePressed'
        QtMocHelpers::SlotData<void(bool)>(56, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setHandbrake'
        QtMocHelpers::SlotData<void(bool)>(57, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setIsLocked'
        QtMocHelpers::SlotData<void(bool)>(58, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setDoorFL'
        QtMocHelpers::SlotData<void(bool)>(59, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setDoorFR'
        QtMocHelpers::SlotData<void(bool)>(60, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setDoorRL'
        QtMocHelpers::SlotData<void(bool)>(61, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setDoorRR'
        QtMocHelpers::SlotData<void(bool)>(62, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setTrunk'
        QtMocHelpers::SlotData<void(bool)>(63, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setWindshieldHeater'
        QtMocHelpers::SlotData<void(bool)>(64, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setWindowPos'
        QtMocHelpers::SlotData<void(int)>(65, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setBeltDriver'
        QtMocHelpers::SlotData<void(bool)>(66, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setBeltPassenger'
        QtMocHelpers::SlotData<void(bool)>(67, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setTempCoolant'
        QtMocHelpers::SlotData<void(double)>(68, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setTempOil'
        QtMocHelpers::SlotData<void(double)>(69, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setTempAmbient'
        QtMocHelpers::SlotData<void(double)>(70, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setTempIntake'
        QtMocHelpers::SlotData<void(double)>(71, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setTempFuel'
        QtMocHelpers::SlotData<void(double)>(72, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setBatteryVoltage'
        QtMocHelpers::SlotData<void(double)>(73, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setAltCharging'
        QtMocHelpers::SlotData<void(bool)>(74, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setRangePossible'
        QtMocHelpers::SlotData<void(int)>(75, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setFuelToFill'
        QtMocHelpers::SlotData<void(int)>(76, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setFuelInst'
        QtMocHelpers::SlotData<void(double)>(77, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setFuelAvg'
        QtMocHelpers::SlotData<void(double)>(78, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 34 },
        }}),
        // Slot 'setBusEngineActive'
        QtMocHelpers::SlotData<void(bool)>(79, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setBusComfortActive'
        QtMocHelpers::SlotData<void(bool)>(80, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setEngineFps'
        QtMocHelpers::SlotData<void(int)>(81, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setComfortFps'
        QtMocHelpers::SlotData<void(int)>(82, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setErrorFrames'
        QtMocHelpers::SlotData<void(int)>(83, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setLastFaultCode'
        QtMocHelpers::SlotData<void(QString)>(84, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'setEcuEngineOnline'
        QtMocHelpers::SlotData<void(bool)>(85, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setEcuAbsOnline'
        QtMocHelpers::SlotData<void(bool)>(86, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setEcuBodyOnline'
        QtMocHelpers::SlotData<void(bool)>(87, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setBlinkerStatus'
        QtMocHelpers::SlotData<void(int)>(88, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setWiperLevel'
        QtMocHelpers::SlotData<void(int)>(89, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'setInteriorLight'
        QtMocHelpers::SlotData<void(bool)>(90, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setAcActive'
        QtMocHelpers::SlotData<void(bool)>(91, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setPosLights'
        QtMocHelpers::SlotData<void(bool)>(92, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setLowBeam'
        QtMocHelpers::SlotData<void(bool)>(93, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setHighBeam'
        QtMocHelpers::SlotData<void(bool)>(94, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setEpcActive'
        QtMocHelpers::SlotData<void(bool)>(95, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setCheckEngine'
        QtMocHelpers::SlotData<void(bool)>(96, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setGlowPlug'
        QtMocHelpers::SlotData<void(bool)>(97, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
        // Slot 'setBatteryWarning'
        QtMocHelpers::SlotData<void(bool)>(98, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 34 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'rpm'
        QtMocHelpers::PropertyData<int>(99, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'speed'
        QtMocHelpers::PropertyData<int>(100, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'gear'
        QtMocHelpers::PropertyData<int>(101, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'ignitionOn'
        QtMocHelpers::PropertyData<bool>(102, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'engineRunning'
        QtMocHelpers::PropertyData<bool>(103, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'engineLoad'
        QtMocHelpers::PropertyData<int>(104, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'throttlePos'
        QtMocHelpers::PropertyData<int>(105, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'pedalPos'
        QtMocHelpers::PropertyData<int>(106, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'torqueActual'
        QtMocHelpers::PropertyData<double>(107, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'torqueRequest'
        QtMocHelpers::PropertyData<double>(108, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'idleState'
        QtMocHelpers::PropertyData<bool>(109, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'cruiseActive'
        QtMocHelpers::PropertyData<bool>(110, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'limpMode'
        QtMocHelpers::PropertyData<bool>(111, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'overheat'
        QtMocHelpers::PropertyData<bool>(112, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'steeringAngle'
        QtMocHelpers::PropertyData<double>(113, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'wheelFL'
        QtMocHelpers::PropertyData<double>(114, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'wheelFR'
        QtMocHelpers::PropertyData<double>(115, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'wheelRL'
        QtMocHelpers::PropertyData<double>(116, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'wheelRR'
        QtMocHelpers::PropertyData<double>(117, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'absActive'
        QtMocHelpers::PropertyData<bool>(118, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'espActive'
        QtMocHelpers::PropertyData<bool>(119, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'tractionActive'
        QtMocHelpers::PropertyData<bool>(120, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'brakePressed'
        QtMocHelpers::PropertyData<bool>(121, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 7),
        // property 'handbrake'
        QtMocHelpers::PropertyData<bool>(122, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 8),
        // property 'isLocked'
        QtMocHelpers::PropertyData<bool>(123, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 9),
        // property 'anyDoorOpen'
        QtMocHelpers::PropertyData<bool>(124, QMetaType::Bool, QMC::DefaultPropertyFlags, 10),
        // property 'doorFL'
        QtMocHelpers::PropertyData<bool>(125, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'doorFR'
        QtMocHelpers::PropertyData<bool>(126, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'doorRL'
        QtMocHelpers::PropertyData<bool>(127, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'doorRR'
        QtMocHelpers::PropertyData<bool>(128, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'trunk'
        QtMocHelpers::PropertyData<bool>(129, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 10),
        // property 'windowPos'
        QtMocHelpers::PropertyData<int>(130, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 11),
        // property 'windshieldHeater'
        QtMocHelpers::PropertyData<int>(131, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 12),
        // property 'beltDriver'
        QtMocHelpers::PropertyData<bool>(132, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'beltPassenger'
        QtMocHelpers::PropertyData<bool>(133, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 13),
        // property 'blinkerStatus'
        QtMocHelpers::PropertyData<int>(134, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 21),
        // property 'wiperLevel'
        QtMocHelpers::PropertyData<int>(135, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 22),
        // property 'interiorLight'
        QtMocHelpers::PropertyData<bool>(136, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 23),
        // property 'acActive'
        QtMocHelpers::PropertyData<bool>(137, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 24),
        // property 'tempCoolant'
        QtMocHelpers::PropertyData<double>(138, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'tempOil'
        QtMocHelpers::PropertyData<double>(139, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'tempAmbient'
        QtMocHelpers::PropertyData<double>(140, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'tempIntake'
        QtMocHelpers::PropertyData<double>(141, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'tempFuel'
        QtMocHelpers::PropertyData<double>(142, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 14),
        // property 'batteryVoltage'
        QtMocHelpers::PropertyData<double>(143, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'altCharging'
        QtMocHelpers::PropertyData<bool>(144, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 15),
        // property 'rangePossible'
        QtMocHelpers::PropertyData<int>(145, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 16),
        // property 'fuelToFill'
        QtMocHelpers::PropertyData<int>(146, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 16),
        // property 'fuelInst'
        QtMocHelpers::PropertyData<double>(147, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
        // property 'fuelAvg'
        QtMocHelpers::PropertyData<double>(148, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 17),
        // property 'busEngineActive'
        QtMocHelpers::PropertyData<bool>(149, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 18),
        // property 'busComfortActive'
        QtMocHelpers::PropertyData<bool>(150, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 18),
        // property 'engineFps'
        QtMocHelpers::PropertyData<int>(151, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 18),
        // property 'comfortFps'
        QtMocHelpers::PropertyData<int>(152, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 18),
        // property 'errorFrames'
        QtMocHelpers::PropertyData<int>(153, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 18),
        // property 'lastFaultCode'
        QtMocHelpers::PropertyData<QString>(154, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 18),
        // property 'ecuEngineOnline'
        QtMocHelpers::PropertyData<bool>(155, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 19),
        // property 'ecuAbsOnline'
        QtMocHelpers::PropertyData<bool>(156, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 19),
        // property 'ecuBodyOnline'
        QtMocHelpers::PropertyData<bool>(157, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 19),
        // property 'vin'
        QtMocHelpers::PropertyData<QString>(158, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'mileage'
        QtMocHelpers::PropertyData<double>(159, QMetaType::Double, QMC::DefaultPropertyFlags, 20),
        // property 'gitHash'
        QtMocHelpers::PropertyData<QString>(160, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'buildDate'
        QtMocHelpers::PropertyData<QString>(161, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'posLights'
        QtMocHelpers::PropertyData<bool>(162, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 25),
        // property 'lowBeam'
        QtMocHelpers::PropertyData<bool>(163, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 25),
        // property 'highBeam'
        QtMocHelpers::PropertyData<bool>(164, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 25),
        // property 'epcActive'
        QtMocHelpers::PropertyData<bool>(165, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 27),
        // property 'checkEngine'
        QtMocHelpers::PropertyData<bool>(166, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 28),
        // property 'glowPlug'
        QtMocHelpers::PropertyData<bool>(167, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 29),
        // property 'batteryWarning'
        QtMocHelpers::PropertyData<bool>(168, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 30),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CanHandler, qt_meta_tag_ZN10CanHandlerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CanHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10CanHandlerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10CanHandlerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10CanHandlerE_t>.metaTypes,
    nullptr
} };

void CanHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CanHandler *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->engineMetricChanged(); break;
        case 1: _t->engineFlagChanged(); break;
        case 2: _t->speedChanged(); break;
        case 3: _t->gearChanged(); break;
        case 4: _t->steeringAngleChanged(); break;
        case 5: _t->wheelSpeedChanged(); break;
        case 6: _t->safetyChanged(); break;
        case 7: _t->brakeChanged(); break;
        case 8: _t->handbrakeChanged(); break;
        case 9: _t->lockStatusChanged(); break;
        case 10: _t->doorChanged(); break;
        case 11: _t->windowChanged(); break;
        case 12: _t->windshieldChanged(); break;
        case 13: _t->beltChanged(); break;
        case 14: _t->tempChanged(); break;
        case 15: _t->elecChanged(); break;
        case 16: _t->fuelLevelChanged(); break;
        case 17: _t->fuelChanged(); break;
        case 18: _t->diagChanged(); break;
        case 19: _t->ecuStatusChanged(); break;
        case 20: _t->mileageChanged(); break;
        case 21: _t->blinkerChanged(); break;
        case 22: _t->wiperChanged(); break;
        case 23: _t->lightChanged(); break;
        case 24: _t->acChanged(); break;
        case 25: _t->lightsChanged(); break;
        case 26: _t->absChanged(); break;
        case 27: _t->epcChanged(); break;
        case 28: _t->checkEngineChanged(); break;
        case 29: _t->glowPlugChanged(); break;
        case 30: _t->batteryWarningChanged(); break;
        case 31: _t->setRpm((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 32: _t->setSpeed((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 33: _t->setGear((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 34: _t->setIgnitionOn((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 35: _t->setEngineRunning((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 36: _t->setEngineLoad((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 37: _t->setThrottlePos((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 38: _t->setPedalPos((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 39: _t->setTorqueActual((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 40: _t->setTorqueRequest((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 41: _t->setIdleState((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 42: _t->setCruiseActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 43: _t->setLimpMode((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 44: _t->setOverheat((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 45: _t->setSteeringAngle((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 46: _t->setWheelFL((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 47: _t->setWheelFR((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 48: _t->setWheelRL((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 49: _t->setWheelRR((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 50: _t->setAbsActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 51: _t->setEspActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 52: _t->setTractionActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 53: _t->setBrakePressed((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 54: _t->setHandbrake((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 55: _t->setIsLocked((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 56: _t->setDoorFL((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 57: _t->setDoorFR((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 58: _t->setDoorRL((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 59: _t->setDoorRR((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 60: _t->setTrunk((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 61: _t->setWindshieldHeater((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 62: _t->setWindowPos((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 63: _t->setBeltDriver((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 64: _t->setBeltPassenger((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 65: _t->setTempCoolant((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 66: _t->setTempOil((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 67: _t->setTempAmbient((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 68: _t->setTempIntake((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 69: _t->setTempFuel((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 70: _t->setBatteryVoltage((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 71: _t->setAltCharging((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 72: _t->setRangePossible((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 73: _t->setFuelToFill((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 74: _t->setFuelInst((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 75: _t->setFuelAvg((*reinterpret_cast<std::add_pointer_t<double>>(_a[1]))); break;
        case 76: _t->setBusEngineActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 77: _t->setBusComfortActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 78: _t->setEngineFps((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 79: _t->setComfortFps((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 80: _t->setErrorFrames((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 81: _t->setLastFaultCode((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 82: _t->setEcuEngineOnline((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 83: _t->setEcuAbsOnline((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 84: _t->setEcuBodyOnline((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 85: _t->setBlinkerStatus((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 86: _t->setWiperLevel((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 87: _t->setInteriorLight((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 88: _t->setAcActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 89: _t->setPosLights((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 90: _t->setLowBeam((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 91: _t->setHighBeam((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 92: _t->setEpcActive((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 93: _t->setCheckEngine((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 94: _t->setGlowPlug((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 95: _t->setBatteryWarning((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::engineMetricChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::engineFlagChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::speedChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::gearChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::steeringAngleChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::wheelSpeedChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::safetyChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::brakeChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::handbrakeChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::lockStatusChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::doorChanged, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::windowChanged, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::windshieldChanged, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::beltChanged, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::tempChanged, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::elecChanged, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::fuelLevelChanged, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::fuelChanged, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::diagChanged, 18))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::ecuStatusChanged, 19))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::mileageChanged, 20))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::blinkerChanged, 21))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::wiperChanged, 22))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::lightChanged, 23))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::acChanged, 24))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::lightsChanged, 25))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::absChanged, 26))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::epcChanged, 27))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::checkEngineChanged, 28))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::glowPlugChanged, 29))
            return;
        if (QtMocHelpers::indexOfMethod<void (CanHandler::*)()>(_a, &CanHandler::batteryWarningChanged, 30))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->rpm(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->speed(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->gear(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->ignitionOn(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->engineRunning(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->engineLoad(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->throttlePos(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->pedalPos(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->torqueActual(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->torqueRequest(); break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->idleState(); break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->cruiseActive(); break;
        case 12: *reinterpret_cast<bool*>(_v) = _t->limpMode(); break;
        case 13: *reinterpret_cast<bool*>(_v) = _t->overheat(); break;
        case 14: *reinterpret_cast<double*>(_v) = _t->steeringAngle(); break;
        case 15: *reinterpret_cast<double*>(_v) = _t->wheelFL(); break;
        case 16: *reinterpret_cast<double*>(_v) = _t->wheelFR(); break;
        case 17: *reinterpret_cast<double*>(_v) = _t->wheelRL(); break;
        case 18: *reinterpret_cast<double*>(_v) = _t->wheelRR(); break;
        case 19: *reinterpret_cast<bool*>(_v) = _t->absActive(); break;
        case 20: *reinterpret_cast<bool*>(_v) = _t->espActive(); break;
        case 21: *reinterpret_cast<bool*>(_v) = _t->tractionActive(); break;
        case 22: *reinterpret_cast<bool*>(_v) = _t->brakePressed(); break;
        case 23: *reinterpret_cast<bool*>(_v) = _t->handbrake(); break;
        case 24: *reinterpret_cast<bool*>(_v) = _t->isLocked(); break;
        case 25: *reinterpret_cast<bool*>(_v) = _t->anyDoorOpen(); break;
        case 26: *reinterpret_cast<bool*>(_v) = _t->doorFL(); break;
        case 27: *reinterpret_cast<bool*>(_v) = _t->doorFR(); break;
        case 28: *reinterpret_cast<bool*>(_v) = _t->doorRL(); break;
        case 29: *reinterpret_cast<bool*>(_v) = _t->doorRR(); break;
        case 30: *reinterpret_cast<bool*>(_v) = _t->trunk(); break;
        case 31: *reinterpret_cast<int*>(_v) = _t->windowPos(); break;
        case 32: *reinterpret_cast<int*>(_v) = _t->windshieldHeater(); break;
        case 33: *reinterpret_cast<bool*>(_v) = _t->beltDriver(); break;
        case 34: *reinterpret_cast<bool*>(_v) = _t->beltPassenger(); break;
        case 35: *reinterpret_cast<int*>(_v) = _t->blinkerStatus(); break;
        case 36: *reinterpret_cast<int*>(_v) = _t->wiperLevel(); break;
        case 37: *reinterpret_cast<bool*>(_v) = _t->interiorLight(); break;
        case 38: *reinterpret_cast<bool*>(_v) = _t->acActive(); break;
        case 39: *reinterpret_cast<double*>(_v) = _t->tempCoolant(); break;
        case 40: *reinterpret_cast<double*>(_v) = _t->tempOil(); break;
        case 41: *reinterpret_cast<double*>(_v) = _t->tempAmbient(); break;
        case 42: *reinterpret_cast<double*>(_v) = _t->tempIntake(); break;
        case 43: *reinterpret_cast<double*>(_v) = _t->tempFuel(); break;
        case 44: *reinterpret_cast<double*>(_v) = _t->batteryVoltage(); break;
        case 45: *reinterpret_cast<bool*>(_v) = _t->altCharging(); break;
        case 46: *reinterpret_cast<int*>(_v) = _t->rangePossible(); break;
        case 47: *reinterpret_cast<int*>(_v) = _t->fuelToFill(); break;
        case 48: *reinterpret_cast<double*>(_v) = _t->fuelInst(); break;
        case 49: *reinterpret_cast<double*>(_v) = _t->fuelAvg(); break;
        case 50: *reinterpret_cast<bool*>(_v) = _t->busEngineActive(); break;
        case 51: *reinterpret_cast<bool*>(_v) = _t->busComfortActive(); break;
        case 52: *reinterpret_cast<int*>(_v) = _t->engineFps(); break;
        case 53: *reinterpret_cast<int*>(_v) = _t->comfortFps(); break;
        case 54: *reinterpret_cast<int*>(_v) = _t->errorFrames(); break;
        case 55: *reinterpret_cast<QString*>(_v) = _t->lastFaultCode(); break;
        case 56: *reinterpret_cast<bool*>(_v) = _t->ecuEngineOnline(); break;
        case 57: *reinterpret_cast<bool*>(_v) = _t->ecuAbsOnline(); break;
        case 58: *reinterpret_cast<bool*>(_v) = _t->ecuBodyOnline(); break;
        case 59: *reinterpret_cast<QString*>(_v) = _t->vin(); break;
        case 60: *reinterpret_cast<double*>(_v) = _t->mileage(); break;
        case 61: *reinterpret_cast<QString*>(_v) = _t->gitHash(); break;
        case 62: *reinterpret_cast<QString*>(_v) = _t->buildDate(); break;
        case 63: *reinterpret_cast<bool*>(_v) = _t->posLights(); break;
        case 64: *reinterpret_cast<bool*>(_v) = _t->lowBeam(); break;
        case 65: *reinterpret_cast<bool*>(_v) = _t->highBeam(); break;
        case 66: *reinterpret_cast<bool*>(_v) = _t->epcActive(); break;
        case 67: *reinterpret_cast<bool*>(_v) = _t->checkEngine(); break;
        case 68: *reinterpret_cast<bool*>(_v) = _t->glowPlug(); break;
        case 69: *reinterpret_cast<bool*>(_v) = _t->batteryWarning(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRpm(*reinterpret_cast<int*>(_v)); break;
        case 1: _t->setSpeed(*reinterpret_cast<int*>(_v)); break;
        case 2: _t->setGear(*reinterpret_cast<int*>(_v)); break;
        case 3: _t->setIgnitionOn(*reinterpret_cast<bool*>(_v)); break;
        case 4: _t->setEngineRunning(*reinterpret_cast<bool*>(_v)); break;
        case 5: _t->setEngineLoad(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setThrottlePos(*reinterpret_cast<int*>(_v)); break;
        case 7: _t->setPedalPos(*reinterpret_cast<int*>(_v)); break;
        case 8: _t->setTorqueActual(*reinterpret_cast<double*>(_v)); break;
        case 9: _t->setTorqueRequest(*reinterpret_cast<double*>(_v)); break;
        case 10: _t->setIdleState(*reinterpret_cast<bool*>(_v)); break;
        case 11: _t->setCruiseActive(*reinterpret_cast<bool*>(_v)); break;
        case 12: _t->setLimpMode(*reinterpret_cast<bool*>(_v)); break;
        case 13: _t->setOverheat(*reinterpret_cast<bool*>(_v)); break;
        case 14: _t->setSteeringAngle(*reinterpret_cast<double*>(_v)); break;
        case 15: _t->setWheelFL(*reinterpret_cast<double*>(_v)); break;
        case 16: _t->setWheelFR(*reinterpret_cast<double*>(_v)); break;
        case 17: _t->setWheelRL(*reinterpret_cast<double*>(_v)); break;
        case 18: _t->setWheelRR(*reinterpret_cast<double*>(_v)); break;
        case 19: _t->setAbsActive(*reinterpret_cast<bool*>(_v)); break;
        case 20: _t->setEspActive(*reinterpret_cast<bool*>(_v)); break;
        case 21: _t->setTractionActive(*reinterpret_cast<bool*>(_v)); break;
        case 22: _t->setBrakePressed(*reinterpret_cast<bool*>(_v)); break;
        case 23: _t->setHandbrake(*reinterpret_cast<bool*>(_v)); break;
        case 24: _t->setIsLocked(*reinterpret_cast<bool*>(_v)); break;
        case 26: _t->setDoorFL(*reinterpret_cast<bool*>(_v)); break;
        case 27: _t->setDoorFR(*reinterpret_cast<bool*>(_v)); break;
        case 28: _t->setDoorRL(*reinterpret_cast<bool*>(_v)); break;
        case 29: _t->setDoorRR(*reinterpret_cast<bool*>(_v)); break;
        case 30: _t->setTrunk(*reinterpret_cast<bool*>(_v)); break;
        case 31: _t->setWindowPos(*reinterpret_cast<int*>(_v)); break;
        case 32: _t->setWindshieldHeater(*reinterpret_cast<int*>(_v)); break;
        case 33: _t->setBeltDriver(*reinterpret_cast<bool*>(_v)); break;
        case 34: _t->setBeltPassenger(*reinterpret_cast<bool*>(_v)); break;
        case 35: _t->setBlinkerStatus(*reinterpret_cast<int*>(_v)); break;
        case 36: _t->setWiperLevel(*reinterpret_cast<int*>(_v)); break;
        case 37: _t->setInteriorLight(*reinterpret_cast<bool*>(_v)); break;
        case 38: _t->setAcActive(*reinterpret_cast<bool*>(_v)); break;
        case 39: _t->setTempCoolant(*reinterpret_cast<double*>(_v)); break;
        case 40: _t->setTempOil(*reinterpret_cast<double*>(_v)); break;
        case 41: _t->setTempAmbient(*reinterpret_cast<double*>(_v)); break;
        case 42: _t->setTempIntake(*reinterpret_cast<double*>(_v)); break;
        case 43: _t->setTempFuel(*reinterpret_cast<double*>(_v)); break;
        case 44: _t->setBatteryVoltage(*reinterpret_cast<double*>(_v)); break;
        case 45: _t->setAltCharging(*reinterpret_cast<bool*>(_v)); break;
        case 46: _t->setRangePossible(*reinterpret_cast<int*>(_v)); break;
        case 47: _t->setFuelToFill(*reinterpret_cast<int*>(_v)); break;
        case 48: _t->setFuelInst(*reinterpret_cast<double*>(_v)); break;
        case 49: _t->setFuelAvg(*reinterpret_cast<double*>(_v)); break;
        case 50: _t->setBusEngineActive(*reinterpret_cast<bool*>(_v)); break;
        case 51: _t->setBusComfortActive(*reinterpret_cast<bool*>(_v)); break;
        case 52: _t->setEngineFps(*reinterpret_cast<int*>(_v)); break;
        case 53: _t->setComfortFps(*reinterpret_cast<int*>(_v)); break;
        case 54: _t->setErrorFrames(*reinterpret_cast<int*>(_v)); break;
        case 55: _t->setLastFaultCode(*reinterpret_cast<QString*>(_v)); break;
        case 56: _t->setEcuEngineOnline(*reinterpret_cast<bool*>(_v)); break;
        case 57: _t->setEcuAbsOnline(*reinterpret_cast<bool*>(_v)); break;
        case 58: _t->setEcuBodyOnline(*reinterpret_cast<bool*>(_v)); break;
        case 63: _t->setPosLights(*reinterpret_cast<bool*>(_v)); break;
        case 64: _t->setLowBeam(*reinterpret_cast<bool*>(_v)); break;
        case 65: _t->setHighBeam(*reinterpret_cast<bool*>(_v)); break;
        case 66: _t->setEpcActive(*reinterpret_cast<bool*>(_v)); break;
        case 67: _t->setCheckEngine(*reinterpret_cast<bool*>(_v)); break;
        case 68: _t->setGlowPlug(*reinterpret_cast<bool*>(_v)); break;
        case 69: _t->setBatteryWarning(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *CanHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10CanHandlerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CanHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 96)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 96;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 96)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 96;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 70;
    }
    return _id;
}

// SIGNAL 0
void CanHandler::engineMetricChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CanHandler::engineFlagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CanHandler::speedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CanHandler::gearChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CanHandler::steeringAngleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CanHandler::wheelSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CanHandler::safetyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void CanHandler::brakeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void CanHandler::handbrakeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void CanHandler::lockStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void CanHandler::doorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void CanHandler::windowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void CanHandler::windshieldChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void CanHandler::beltChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void CanHandler::tempChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void CanHandler::elecChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void CanHandler::fuelLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void CanHandler::fuelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void CanHandler::diagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void CanHandler::ecuStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void CanHandler::mileageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void CanHandler::blinkerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void CanHandler::wiperChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void CanHandler::lightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void CanHandler::acChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void CanHandler::lightsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 25, nullptr);
}

// SIGNAL 26
void CanHandler::absChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 26, nullptr);
}

// SIGNAL 27
void CanHandler::epcChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 27, nullptr);
}

// SIGNAL 28
void CanHandler::checkEngineChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 28, nullptr);
}

// SIGNAL 29
void CanHandler::glowPlugChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 29, nullptr);
}

// SIGNAL 30
void CanHandler::batteryWarningChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 30, nullptr);
}
QT_WARNING_POP
