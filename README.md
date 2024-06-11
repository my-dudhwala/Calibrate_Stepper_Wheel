# Stepper Motor Calibration with Hall Effect Sensor

This project demonstrates the calibration of a stepper motor's position using a Hall effect sensor. The motor is connected to a wheel with a magnet, and the sensor is placed on a fixed platform to detect the magnet's position. The code is written for Arduino and avoids using external libraries to ensure transparency in the processes.

## Table of Contents

- [Introduction](#introduction)
- [Components](#components)
- [Wiring](#wiring)
- [Code Overview](#code-overview)
- [Setup and Execution](#setup-and-execution)
- [License](#license)

## Introduction

This project aims to precisely calibrate the position of a stepper motor using a Hall effect sensor. The calibration involves rotating the motor to find a reference point (magnet detection) and then moving the motor to a specific position from that reference point.

## Components

- ESP32(I am using ESP32(Assume Arduino word as my ESP32 here), you can use any other board from Arduino IDE, just remeber to set the GPIO)
- Stepper motor
- Hall effect sensor
- Magnet
- LEDs and resistors (optional for debugging)
- Connecting wires

## Wiring

- **Stepper Motor Connections:**
  - Coil A: Pin 16
  - Coil B: Pin 17
  - Coil C: Pin 18
  - Coil D: Pin 19
- **Hall Effect Sensor Connection:**
  - Sensor Pin: Pin 4
- **LED (optional):**
  - Pin 2

Refer to the pin definitions in the code for exact connections.

## Code Overview

The code is divided into several functions to manage the stepper motor's operations and sensor readings:

- `setup()`: Initializes motor and sensor pins, and sets up serial communication.
- `loop()`: Main execution loop that performs the calibration and moves the motor to specific positions.
- `findReferencePoint()`: Rotates the motor until the sensor detects the magnet, indicating the reference point.
- `moveToPosition(int steps)`: Moves the motor a specified number of steps from the reference point.
- `runMotor(bool forward)`: Runs the motor forward or backward for a target number of steps.
- `stopMotor()`: Stops the motor by setting all motor pins to LOW.
- `coolDown()`: Delays execution to allow the motor to cool down.
- `stepMotor(int aState, int bState, int cState, int dState)`: Steps the motor and reads the sensor value.

## Setup and Execution

1. **Wiring:** Connect the stepper motor, Hall effect sensor, and optional LED to the Arduino as specified in the wiring section.
2. **Upload the Code:** Upload the provided code to the Arduino board using the Arduino IDE.
3. **Monitor Serial Output:** Open the Serial Monitor (set to 115200 baud) to observe the calibration process and motor movements.

The code will:
- Initialize the system and wait for 5 seconds before starting.
- Continuously find the reference point (magnet detection).
- Move the motor to a specified position after detecting the reference point.
- Cool down between cycles to prevent overheating.

## License

This project is free to use, modify, and reuse for personal or commercial purposes. No attribution is required.
