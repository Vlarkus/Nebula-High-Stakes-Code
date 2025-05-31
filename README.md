# NEBULA | 7518D - High Stakes Codebase

This repository contains a well-structured and modular codebase for a VEX V5 competition robot. It includes custom implementations to enhance match readiness, user interaction, and autonomous flexibility on the VEX field.

## Disclaimer

This codebase is provided for educational purposes to inspire and support learning within the VEX V5 ecosystem. Users are advised to use this code responsibly and at their own risk. Per the REC Foundation's Student-Centered Policy, students must design, build, and program their robots independently. Direct reuse of this code without understanding or modification may violate these guidelines.


## Overview

The code provides a complete control system featuring:
- Alliance color selection screen when connected to a competition field (used for color sorting).
- A flexible autonomous selector supporting unlimited routines. Each routine has a title and a description to be displayes and the code to run
- A startup logo screen displayed during autonomous and driver control phases.
- Connectivity monitoring functionality (see config.cpp) of all motors and sensors with controller vibration and LED indicators feedback. Disconnected ports are also displayed on the screen.

## Features

- **Screen Management System**: Modular management of screen elements including logos, selectors, and live feedback
- **Autonomous Routine Manager**: Dynamic system for selecting from any number of autonomous strategies
- **Alliance Color Selector**: Alliance color selection screen that sets the current alliance color.
- **Device Connectivity Checker**: Monitors motor/sensor connections; provides:
  - Vibration feedback on controller
  - Visual LED alerts on brain
  - Port number and device name on disconnected ports
- **clock.cpp and led.cpp**: Integrated from [StormLib](https://github.com/ItzSt0rmz/StormLib) (attribution)

## Credits

- **[StormLib](https://github.com/ItzSt0rmz/StormLib)** – Clock and LED module used under attribution
- **[LemLib](https://github.com/LemLib/LemLib)** - DriveTrain setup

## Notes

This code is designed for use in VEX V5 competition environments and assumes the use of [PROS](https://pros.cs.purdue.edu/) through Visual Studio Code and [LemLib](https://github.com/LemLib/LemLib) as the base for the drivetrain setup.
