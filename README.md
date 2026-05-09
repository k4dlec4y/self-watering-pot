# Automatic Watering System with ATmega4809 Curiosity Nano

## Short Description

This project implements intelligent water pump control based on soil moisture levels and water tank availability. The system monitors an analog moisture sensor and a float switch (pump protection), allowing for manual override via an external button. It includes safety features such as run-time limits and cooling-off periods (lockout) managed by the RTC/PIT peripheral.

## Components Needed

- 1x ATmega4809 Curiosity Nano Microcontroller
- 1x Soil Moisture Sensor (Analog output).
- 1x Float Switch (Swimmer) (Magnetic reed switch type)
- 1x Momentary Push Button
- 1x Small Water Pump (3V – 6V)
- 1x 5V Relay Module or N-Channel MOSFET (e.g., IRF540) to drive the pump
- 1x USB Cable for power (VBUS) and programming

## Installation

Using MPLAB X IDE:
1. Clone the repository: `git clone https://github.com/k4dlec4y/self-watering-pot.git`
2. Open the project in MPLAB X IDE.
3. Build the project to compile the code.
4. Connect the ATmega4809 Curiosity Nano to your computer via USB.
5. Program the microcontroller using the MPLAB X IDE programming tools.

## Status console output
The system provides real-time status updates via the serial console, including:
- Time since last watering
- Current soil moisture level (0 - 100 %)
- Water tank status (OK/EMPTY)
- Pump status (ON/OFF)
To access the console output, you can launch a serial terminal (e.g., PuTTY) and connect to the appropriate port at a baud rate of 9600 bps.
If you are using linux and tio is installed, you can also use script launch_console.sh to view the output:
```
./launch_console.sh [<device=/dev/ttyACM0>]
```

## Component Connections

| Component          | MCU Pin | Code Configuration                        | Note                                                        |
|--------------------|---------|-------------------------------------------|-------------------------------------------------------------|
| External Button    | PC0     | Input, Internal PULLUP enabled            | Activates the pump manually (if conditions are met)         |
| Swimmer (Float)    | PD1     | Input, Internal PULLUP enabled            | Detects empty water tank                                    |
| Moisture Sensor    | PD0     | Analog Input (AIN0), Digital Input Off    | Measures soil moisture (0 - 1023)                           |
| Water Pump         | PE0     | Digital Output                            | MUST use a relay or transistor                              |

## License
This project is licensed under the MIT License – see the LICENSE file for details.

## Author
Created by Matúš Kadlecay – https://github.com/k4dlec4y
