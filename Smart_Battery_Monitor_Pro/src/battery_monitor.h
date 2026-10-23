#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <stdbool.h>

typedef struct {
    float voltage_v;
    float current_a;
    float temperature_c;
} BatteryReading;

typedef enum {
    FAULT_NONE             = 0u,
    FAULT_UNDERVOLTAGE     = 1u << 0,
    FAULT_OVERVOLTAGE      = 1u << 1,
    FAULT_OVERCURRENT      = 1u << 2,
    FAULT_OVERTEMPERATURE  = 1u << 3
} BatteryFault;

typedef struct {
    float min_voltage_v;
    float max_voltage_v;
    float max_current_a;
    float max_temperature_c;
} BatteryLimits;

typedef struct {
    unsigned int fault_mask;
    bool valid;
} BatteryAssessment;

/* Demonstration limits only. Real limits depend on cell chemistry and pack design. */
BatteryLimits battery_default_limits(void);
BatteryAssessment battery_assess(const BatteryReading *reading,
                                 const BatteryLimits *limits);
bool battery_reading_is_valid(const BatteryReading *reading);

#endif
