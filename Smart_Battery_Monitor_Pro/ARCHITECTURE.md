# Architecture

```text
User / simulated input
        |
        v
  src/main.c  ---------> battery_log.txt
  (CLI, input parsing, output, file logging)
        |
        v
  battery_assess()
  src/battery_monitor.c
        |
        +--> reading validation
        +--> threshold checks
        +--> fault bitmask
        |
        v
  BatteryAssessment
        |
        v
  Console alerts + log record

tests/test_battery_monitor.c ---> battery_assess()
```

## Design choices

- Monitoring logic is independent from console input and file I/O, so it can be tested in isolation.
- `BatteryReading` groups the measurements into one value.
- `BatteryLimits` keeps thresholds configurable.
- Fault bit flags allow more than one fault to be represented at the same time.
- The assessment includes a separate validity flag so invalid readings are not mistaken for a normal battery state.
