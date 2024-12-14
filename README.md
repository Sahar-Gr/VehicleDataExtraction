# Embedded System Configuration

This section details the embedded system configuration for communicating with the vehicle's OBD-II interface. The system consists of an **ESP32** microcontroller connected to a **MCP2515** CAN bus controller. The vehicle data is retrieved through the CAN protocol, processed by the ESP32, and sent to a mobile application via Firebase.

## Components

- **ESP32-WROOM-32D**: A low-power microcontroller used to handle communication between the vehicle's CAN bus and the mobile application.
- **MCP2515**: A CAN bus controller that interfaces with the vehicle's OBD-II port, enabling communication over the CAN network.
- **OBD-II Interface**: The On-Board Diagnostics (OBD-II) port of the vehicle is used to extract real-time data like RPM, speed, fuel level, and gearbox data.

## Configuration Overview

### 1. ESP32 and MCP2515 Communication

- The **ESP32** communicates with the **MCP2515** via the **SPI interface**.
- The **MCP2515** is connected to the vehicle's **OBD-II port** to retrieve data from the CAN bus.
- The data retrieved from the vehicle is then processed by the ESP32 and sent to the **Firebase Realtime Database**.

### 2. Physical Setup

1. **ESP32 Connections**:
   - **MISO (Master In Slave Out)**: Used to receive data from the MCP2515.
   - **MOSI (Master Out Slave In)**: Used to send data to the MCP2515.
   - **SCK (Clock)**: Provides the clock signal for communication.
   - **CS (Chip Select)**: Used to select the MCP2515 module.
   
2. **MCP2515 Connections**:
   - **CANH (CAN High)**: Connects to the CAN High pin of the vehicle's OBD-II port.
   - **CANL (CAN Low)**: Connects to the CAN Low pin of the vehicle's OBD-II port.

### 3. Software Configuration

- The ESP32 firmware is developed using **PlatformIO** and programmed in **C++**. It uses libraries like **MCP_CAN_lib** to interface with the MCP2515 module.
- The data is sent to Firebase in real-time, where it can be accessed by the mobile application.
  
### 4. Setting Up the CAN Bus Communication

- The communication is initialized using the **MCP2515** library to set up the CAN bus speed and configure the filters for the specific messages needed (RPM, speed, fuel, etc.).
- The ESP32 reads the CAN messages and decodes them to obtain the vehicle data.
- The decoded data is then stored in Firebase for real-time access by the Flutter mobile application.

### 5. Testing the Communication

Once the ESP32 firmware is uploaded, you can test the communication by checking the serial monitor for logs indicating successful CAN bus communication. Ensure the CAN bus is active and the correct PIDs (Parameter IDs) are being requested and received from the vehicle.

## Folder Structure for Embedded Code

