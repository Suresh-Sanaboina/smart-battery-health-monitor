# Interview Preparation

## 60-second project introduction
"I developed a Smart Battery Health Monitoring and Fault Alert System as a C11 software simulation. It accepts simulated voltage, current and temperature readings, validates the input, evaluates configurable demonstration limits, and reports multiple simultaneous faults using bitmask flags. I separated the monitoring engine from the command-line interface so the logic can be unit-tested independently. The application appends diagnostic records to a log file, and I added automated tests for normal readings, each fault, boundary conditions and invalid values. It is a simulation only; it does not use physical sensors."

## Likely questions

**Why use separate functions/files?**  
Separation of concerns makes the fault logic reusable and independently testable, while keeping input and logging out of the core assessment function.

**Why use bit flags?**  
Each fault has its own bit, so multiple faults can be represented in one integer. A mask is checked with bitwise AND.

**Why separate validity from fault status?**  
Invalid input must not be interpreted as a healthy reading. `valid` reports whether assessment was possible; `fault_mask` reports threshold violations.

**Why independent `if` statements?**  
All fault conditions must be checked. An `else if` chain would report only the first matching condition.

**Why check `isfinite`?**  
It rejects NaN and positive/negative infinity, which can otherwise make comparisons behave unexpectedly.

**What does `fopen("battery_log.txt", "a")` do?**  
It opens the file for appending, preserving previous records. The program checks for failure and closes the file after writing.

**What are the limits?**  
They are demonstration values for this simulation only. Real thresholds depend on battery chemistry, cell count, pack design and manufacturer specifications.

**What would you add for real embedded hardware?**  
Sensor drivers, ADC scaling/calibration, sensor-fault detection, watchdog handling, timing constraints, a hardware abstraction layer, nonvolatile log strategy, and validation against the target hardware. Safety-critical functions require appropriate engineering and verification.

**What is not implemented?**  
No physical sensor interface, microcontroller target, state-of-charge/state-of-health estimation, balancing, or safety certification.
