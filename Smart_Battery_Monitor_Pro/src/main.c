#include "battery_monitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void print_faults(unsigned int mask, FILE *out)
{
    if (mask == FAULT_NONE) {
        fprintf(out, "Status: NORMAL\n");
        return;
    }
    if ((mask & FAULT_UNDERVOLTAGE) != 0u) {
        fprintf(out, "ALERT: UNDERVOLTAGE\n");
    }
    if ((mask & FAULT_OVERVOLTAGE) != 0u) {
        fprintf(out, "ALERT: OVERVOLTAGE\n");
    }
    if ((mask & FAULT_OVERCURRENT) != 0u) {
        fprintf(out, "ALERT: OVERCURRENT\n");
    }
    if ((mask & FAULT_OVERTEMPERATURE) != 0u) {
        fprintf(out, "ALERT: HIGH TEMPERATURE\n");
    }
}

static int read_float(const char *prompt, float *value)
{
    char line[128];
    char extra;
    char *end = NULL;

    printf("%s", prompt);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    /* strtof enables explicit rejection of trailing junk such as "12abc". */
    *value = strtof(line, &end);
    if (end == line) {
        return 0;
    }
    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }
    if (*end != '\0') {
        return 0;
    }
    (void)extra;
    return 1;
}

static void append_log(const BatteryReading *r, const BatteryAssessment *a)
{
    FILE *log = fopen("battery_log.txt", "a");
    time_t now;
    struct tm *local;
    char stamp[32] = "time-unavailable";

    if (log == NULL) {
        fprintf(stderr, "Warning: could not open battery_log.txt for append.\n");
        return;
    }

    now = time(NULL);
    local = localtime(&now);
    if (local != NULL &&
        strftime(stamp, sizeof stamp, "%Y-%m-%d %H:%M:%S", local) == 0u) {
        (void)snprintf(stamp, sizeof stamp, "time-unavailable");
    }

    fprintf(log, "%s, V=%.2f V, I=%.2f A, T=%.2f C, ",
            stamp, r->voltage_v, r->current_a, r->temperature_c);
    if (a->fault_mask == FAULT_NONE) {
        fprintf(log, "NORMAL\n");
    } else {
        fprintf(log, "fault_mask=0x%02X\n", a->fault_mask);
    }
    if (fclose(log) != 0) {
        fprintf(stderr, "Warning: failed to close battery log cleanly.\n");
    }
}

int main(void)
{
    BatteryReading reading;
    BatteryLimits limits = battery_default_limits();
    BatteryAssessment assessment;

    puts("==========================================");
    puts(" SMART BATTERY HEALTH MONITOR - SIMULATOR");
    puts("==========================================");
    puts("Illustrative limits only; not a safety controller.\n");

    if (!read_float("Battery voltage (V): ", &reading.voltage_v) ||
        !read_float("Battery current (A): ", &reading.current_a) ||
        !read_float("Battery temperature (C): ", &reading.temperature_c)) {
        fprintf(stderr, "Input error: enter one numeric value for each field.\n");
        return EXIT_FAILURE;
    }

    assessment = battery_assess(&reading, &limits);
    if (!assessment.valid) {
        fprintf(stderr, "Invalid reading: voltage/current must be finite and non-negative.\n");
        return EXIT_FAILURE;
    }

    puts("\n--------------- ASSESSMENT ---------------");
    printf("Voltage     : %.2f V\n", reading.voltage_v);
    printf("Current     : %.2f A\n", reading.current_a);
    printf("Temperature : %.2f C\n", reading.temperature_c);
    print_faults(assessment.fault_mask, stdout);
    append_log(&reading, &assessment);
    puts("Log: battery_log.txt (append mode)");
    puts("------------------------------------------");
    return EXIT_SUCCESS;
}
