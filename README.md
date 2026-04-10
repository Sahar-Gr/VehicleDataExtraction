# Vehicle Data Extraction over CAN (ESP32 + MCP2515)

## Overview

This project implements an embedded system for extracting real-time vehicle data through the OBD-II interface using CAN communication.

The system uses an ESP32 connected to an MCP2515 CAN module to retrieve data from the vehicle’s ECU, decode relevant parameters (such as speed, RPM, and temperature), and transmit them for real-time monitoring in a mobile application.

The project focuses on building a complete data pipeline from low-level CAN communication to application-level usage, while ensuring that the extracted data remains coherent and usable.

---

## My Role

- Implemented CAN communication between ESP32 and MCP2515 using SPI
- Retrieved raw CAN messages from the vehicle ECU via OBD-II
- Decoded CAN frames into meaningful physical values (RPM, speed, etc.)
- Integrated real-time data transmission to Firebase

---

## Engineering & Validation Approach

Even though this was primarily an embedded systems project, it required validating the data flow at different levels:

- checking that decoded values matched expected vehicle behavior
- verifying consistency of CAN messages over time
- debugging communication issues between modules
- ensuring reliable data transmission to the mobile application

---

## System Architecture

Vehicle ECU → OBD-II / CAN → MCP2515 → ESP32 → Firebase → Mobile App

---

## Main Challenges

- Understanding and decoding CAN messages and PIDs
- Ensuring stable communication between ESP32 and MCP2515
- Handling inconsistencies in real-time vehicle data
- Maintaining reliable data transmission to Firebase

---

## Technologies

- ESP32
- MCP2515
- CAN Bus
- OBD-II
- PlatformIO (C++)
- Firebase

---

## Repository Structure

- `src/` → embedded source code
- `include/` → header files
- `lib/` → external libraries
- `test/` → test folder
- `platformio.ini` → configuration

---

## How to Run

- Open the project in PlatformIO
- Configure ESP32 board
- Connect MCP2515 to ESP32 and OBD-II interface
- Upload firmware
- Monitor serial output to verify CAN communication
