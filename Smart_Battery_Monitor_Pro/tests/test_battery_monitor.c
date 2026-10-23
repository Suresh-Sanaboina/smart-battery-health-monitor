#include "../src/battery_monitor.h"
#include <math.h>
#include <stdio.h>

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(name, condition) do { \
    ++tests_run; \
    if (condition) { printf("[PASS] %s\n", name); } \
    else { printf("[FAIL] %s\n", name); ++tests_failed; } \
} while (0)

int main(void)
{
    BatteryLimits limits = battery_default_limits();
    BatteryReading r;
    BatteryAssessment a;

    r = (BatteryReading){12.4f, 2.1f, 32.0f};
    a = battery_assess(&r, &limits);
    CHECK("normal reading", a.valid && a.fault_mask == FAULT_NONE);

    r = (BatteryReading){10.5f, 2.1f, 32.0f};
    a = battery_assess(&r, &limits);
    CHECK("undervoltage", a.valid && a.fault_mask == FAULT_UNDERVOLTAGE);

    r = (BatteryReading){15.0f, 2.1f, 32.0f};
    a = battery_assess(&r, &limits);
    CHECK("overvoltage", a.valid && a.fault_mask == FAULT_OVERVOLTAGE);

    r = (BatteryReading){12.4f, 6.2f, 32.0f};
    a = battery_assess(&r, &limits);
    CHECK("overcurrent", a.valid && a.fault_mask == FAULT_OVERCURRENT);

    r = (BatteryReading){12.4f, 2.1f, 50.0f};
    a = battery_assess(&r, &limits);
    CHECK("overtemperature", a.valid && a.fault_mask == FAULT_OVERTEMPERATURE);

    r = (BatteryReading){10.5f, 6.2f, 50.0f};
    a = battery_assess(&r, &limits);
    CHECK("simultaneous faults",
          a.valid && a.fault_mask ==
          (FAULT_UNDERVOLTAGE | FAULT_OVERCURRENT | FAULT_OVERTEMPERATURE));

    r = (BatteryReading){11.0f, 5.0f, 45.0f};
    a = battery_assess(&r, &limits);
    CHECK("exact lower and upper thresholds are not exceeded",
          a.valid && a.fault_mask == FAULT_NONE);

    r = (BatteryReading){-0.1f, 1.0f, 20.0f};
    a = battery_assess(&r, &limits);
    CHECK("negative voltage rejected", !a.valid);

    r = (BatteryReading){12.0f, -0.1f, 20.0f};
    a = battery_assess(&r, &limits);
    CHECK("negative current rejected", !a.valid);

    r = (BatteryReading){NAN, 1.0f, 20.0f};
    a = battery_assess(&r, &limits);
    CHECK("NaN reading rejected", !a.valid);

    a = battery_assess(NULL, &limits);
    CHECK("null reading rejected", !a.valid);

    printf("\nTests: %d, Passed: %d, Failed: %d\n",
           tests_run, tests_run - tests_failed, tests_failed);
    return tests_failed == 0 ? 0 : 1;
}
