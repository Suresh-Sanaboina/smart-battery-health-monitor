#include "battery_monitor.h"
#include <math.h>

BatteryLimits battery_default_limits(void)
{
    BatteryLimits limits = {11.0f, 14.6f, 5.0f, 45.0f};
    return limits;
}

bool battery_reading_is_valid(const BatteryReading *reading)
{
    if (reading == 0) {
        return false;
    }

    /* Reject NaN and infinity; voltage/current cannot be negative in this model.
       Temperature may be negative for cold-environment simulations. */
    return isfinite(reading->voltage_v) &&
           isfinite(reading->current_a) &&
           isfinite(reading->temperature_c) &&
           reading->voltage_v >= 0.0f &&
           reading->current_a >= 0.0f;
}

BatteryAssessment battery_assess(const BatteryReading *reading,
                                 const BatteryLimits *limits)
{
    BatteryAssessment result = {FAULT_NONE, false};

    if (!battery_reading_is_valid(reading) || limits == 0 ||
        !isfinite(limits->min_voltage_v) ||
        !isfinite(limits->max_voltage_v) ||
        !isfinite(limits->max_current_a) ||
        !isfinite(limits->max_temperature_c) ||
        limits->min_voltage_v < 0.0f ||
        limits->max_voltage_v <= limits->min_voltage_v ||
        limits->max_current_a < 0.0f) {
        return result;
    }

    result.valid = true;

    if (reading->voltage_v < limits->min_voltage_v) {
        result.fault_mask |= FAULT_UNDERVOLTAGE;
    }
    if (reading->voltage_v > limits->max_voltage_v) {
        result.fault_mask |= FAULT_OVERVOLTAGE;
    }
    if (reading->current_a > limits->max_current_a) {
        result.fault_mask |= FAULT_OVERCURRENT;
    }
    if (reading->temperature_c > limits->max_temperature_c) {
        result.fault_mask |= FAULT_OVERTEMPERATURE;
    }

    return result;
}
