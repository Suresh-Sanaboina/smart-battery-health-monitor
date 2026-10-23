# Project Report: Smart Battery Health Monitoring System

## 1. Objective
Create a desktop C simulation that accepts battery voltage, current and temperature values, checks them against demonstration thresholds, reports every matching fault, and records a diagnostic line.

## 2. Scope
The project simulates readings entered by a user. It does not interface with physical sensors or a microcontroller and is not a safety controller.

## 3. Requirements
- Read three numeric values from the user.
- Reject malformed, non-finite, negative-voltage and negative-current input.
- Detect undervoltage, overvoltage, overcurrent and high temperature independently.
- Report simultaneous faults.
- Append a diagnostic record to a text log.
- Provide automated unit tests with non-zero exit status when a test fails.

## 4. Implementation
The monitoring engine is separated into `battery_monitor.c/.h`. The CLI and logging are in `main.c`. Tests call the monitoring engine directly, avoiding dependence on terminal prompts.

## 5. Test strategy
Automated tests cover normal input, each individual fault, multiple faults, exact threshold values, negative measurements, NaN and a null pointer. Manual CLI tests should additionally cover non-numeric text and log-file creation.

## 6. Known limitations
The thresholds are illustrative and require engineering validation before use in any real application. No sensor acquisition, calibration, state estimation, battery chemistry model, hardware interface, real-time guarantee or safety certification is included.

## 7. Future enhancements
- Add a portable hardware abstraction layer and target-specific sensor drivers.
- Add explicit sensor disconnected/out-of-range status.
- Add configuration loading with range validation.
- Add CI build/test pipeline and code coverage.
- Add serial data replay for repeatable simulation.
