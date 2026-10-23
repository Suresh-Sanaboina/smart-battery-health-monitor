# Smart Battery Health Monitoring System — Simulation

A modular Embedded C portfolio project that simulates battery voltage, current, and temperature readings; assesses readings against configurable demonstration limits; reports multiple simultaneous faults; and appends a diagnostic record to a log file.

> **Scope and safety:** This is a desktop software simulation. It does not connect to hardware, measure a real battery, estimate state of charge/state of health, or provide a safety-rated protection function. The default limits are illustrative and are not universal battery limits. Real products require limits appropriate to chemistry, cell count, pack design, sensors, and manufacturer guidance.

## Features

- C11 implementation split into monitoring logic and command-line application.
- `struct` for readings and limits; `enum` bit flags for fault states.
- Multiple simultaneous fault detection.
- Input parsing that rejects non-numeric/trailing-junk values.
- Rejects negative voltage/current and non-finite measurements.
- Append-only `battery_log.txt` with local timestamp when available.
- Automated C test runner with normal, fault, boundary, invalid and multi-fault cases.
- Strict compiler warnings.

## Default demonstration rules

| Condition | Demonstration rule |
|---|---|
| Undervoltage | voltage < 11.0 V |
| Overvoltage | voltage > 14.6 V |
| Overcurrent | current > 5.0 A |
| High temperature | temperature > 45.0 °C |

At exact boundaries the relevant fault is not triggered. Change `battery_default_limits()` in `src/battery_monitor.c` to experiment with limits.

## Build on Windows with MSYS2 UCRT64

Open the MSYS2 UCRT64 terminal in this folder (or `cd` to the extracted folder):

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -Isrc src/main.c src/battery_monitor.c -o battery.exe
./battery.exe
```

Alternatively, from Windows Command Prompt or PowerShell, double-click `build.bat` or run `.\build.bat`.

## Run automated tests

In MSYS2 UCRT64:

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -Isrc tests/test_battery_monitor.c src/battery_monitor.c -o test_battery.exe
./test_battery.exe
```

Or run `test.bat` from Windows. Exit code 0 means all tests passed; a failing assertion returns a non-zero code.

## Example

Input:
- voltage: `10.5`
- current: `6.2`
- temperature: `50`

Expected: undervoltage, overcurrent and high-temperature alerts. A line is appended to `battery_log.txt`.

## Project layout

```text
Smart_Battery_Monitor_Pro/
├── src/
│   ├── main.c
│   ├── battery_monitor.c
│   └── battery_monitor.h
├── tests/
│   └── test_battery_monitor.c
├── build.bat
├── test.bat
├── Makefile
├── test_cases.csv
├── ARCHITECTURE.md
├── PROJECT_REPORT.md
├── INTERVIEW_PREP.md
└── README.md
```

## Limitations and future work

- No physical sensors or microcontroller peripherals.
- No battery chemistry model, state-of-charge/state-of-health estimation, balancing, or safety certification.
- CLI log timestamps use the host computer's local time; this is not a real-time embedded clock.
- Future extensions: hardware abstraction layer, sensor drivers, watchdog/error handling, configuration file, serial protocol simulation, CI workflow, and target-specific build.

## Resume-safe project description

**Smart Battery Health Monitoring and Fault Alert System (C11 simulation)** — Developed a modular C application to assess simulated voltage/current/temperature readings, detect multiple threshold violations with bitmask fault flags, validate inputs, persist diagnostic logs, and verify behavior using automated unit tests. Implemented and tested on Windows using GCC/MSYS2. No physical hardware was used.
