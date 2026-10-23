# Smart Battery Health Monitoring and Fault Alert System

## Overview

The **Smart Battery Health Monitoring and Fault Alert System** is a modular C-based software simulation designed to monitor battery parameters and identify potential fault conditions using predefined thresholds.

The application evaluates simulated voltage, current, and temperature readings, detects abnormal conditions, and generates corresponding fault alerts. It demonstrates fundamental concepts in C programming, condition-based monitoring, bitwise operations, input validation, and software testing.

## Features

- **Battery Parameter Monitoring:** Evaluates simulated voltage, current, and temperature readings.
- **Fault Detection:** Identifies undervoltage, overcurrent, and high-temperature conditions using predefined thresholds.
- **Bitwise Fault Flags:** Uses bit flags to represent and track multiple fault conditions.
- **Input Validation:** Handles invalid inputs to improve reliability.
- **Fault Reporting:** Generates alert messages and records assessment information.
- **Automated Testing:** Verified the monitoring logic with 11 automated test cases, with all 11 tests passing.

## Technologies Used

- **Programming Language:** C
- **Compiler:** GCC
- **Development Environment:** Visual Studio Code
- **Version Control:** Git and GitHub

## How It Works

1. The application receives simulated battery voltage, current, and temperature values.
2. It validates the input values.
3. The readings are evaluated against predefined thresholds.
4. The application identifies abnormal conditions and sets the corresponding fault flags.
5. Appropriate fault alerts and assessment information are generated.

## Fault Conditions

| Fault Condition | Description |
|---|---|
| Undervoltage | Battery voltage falls below the configured threshold. |
| Overcurrent | Battery current exceeds the configured threshold. |
| High Temperature | Battery temperature exceeds the configured threshold. |

## Testing

The monitoring logic was compiled using GCC and validated with an automated test suite.

- **Total test cases:** 11
- **Passed:** 11
- **Failed:** 0

The test results validate the implemented software logic under the tested scenarios. They do not represent physical battery testing or hardware validation.

## How to Run

1. Install GCC and ensure it is available in your terminal.
2. Clone or download this repository.
3. Open the project folder in Visual Studio Code.
4. Compile the relevant C source files using GCC.
5. Run the generated executable and follow the application's input prompts.
6. Execute the project's test suite using the test instructions included in the source files.

**Note:** Use the actual source filenames and test commands from this repository when compiling and running the application.

## Project Scope

This project is a **software simulation**. Battery readings are simulated, and no physical battery, sensor, or microcontroller hardware is claimed as part of the implementation.

## Skills Demonstrated

- C programming and modular code organization
- Conditional statements and threshold-based logic
- Bitwise operators and fault flags
- Input validation and fault reporting
- GCC compilation and automated testing
- Git-based version control

## Future Enhancements

- Interface with physical voltage, current, and temperature sensors.
- Integrate a microcontroller for real-time monitoring.
- Add UART, SPI, or I2C communication where appropriate.
- Develop a real-time fault logging and monitoring interface.

## Author

**Durga Suresh Sanaboina**

GitHub: [Suresh-Sanaboina](https://github.com/Suresh-Sanaboina)

---

*Developed as a C programming project to explore battery parameter monitoring, fault detection, and automated software testing.*