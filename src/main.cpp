#include <SPI.h>
#include <mcp_can.h>

// MCP2515 pins
#define CAN0_INT 2
#define CAN_CS_PIN 5

MCP_CAN CAN0(CAN_CS_PIN); // CS pin for MCP2515

// CAN data variables
int vehicleSpeed = 0;
int fuelLevel = 0;
float batteryVoltage = 0.0;
int rpm = 0;
int engineCoolantTemp = 0;
int intakePressure = 0;
int gear = 0;
void MCP2515_ISR() {
    // Empty interrupt service routine for MCP2515
}

void sendOBDRequest(byte pid) {
    byte data[8] = {0x02, 0x01, pid, 0x00, 0x00, 0x00, 0x00, 0x00};
    CAN0.sendMsgBuf(0x7E0, 0, 8, data);
}

void readOBDResponse() {
    long unsigned int canId;
    byte len;
    byte buf[8];

    if (CAN0.checkReceive() == CAN_MSGAVAIL) {
        if (CAN0.readMsgBuf(&canId, &len, buf) == CAN_OK) {
            if (canId == 0x7E8) { // Response from engine ECU
                switch (buf[2]) {
                    case 0x05: // Engine Coolant Temperature
                        engineCoolantTemp = buf[3]-40; // Decode
                        break;
                    case 0x0C: // RPM
                        rpm = ((buf[3] * 256) + buf[4]) / 4; // Decode
                        break;
                    case 0x0D: // Vehicle Speed
                        vehicleSpeed = buf[3]; // Decode
                        break;
                    case 0x2F: // Fuel Level
                        fuelLevel = buf[3] * 100.0 / 255.0; // Decode
                        break;
                    case 0x0B: // Intake Pressure
                        intakePressure = (buf[3] * 1) - 35; // Decode
                        break;
                    case 0x42: // Battery Voltage
                        batteryVoltage = buf[3] * 0.1; // Decode
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
int determineGear(int speed) {
    if (speed <= 10) {
        return 1; // 1ère vitesse
    } else if (speed <= 25) {
        return 2; // 2ème vitesse
    } else if (speed <= 45) {
        return 3; // 3ème vitesse
    } else if (speed <= 65) {
        return 4; // 4ème vitesse
    } else if (speed <= 85) {
        return 5; // 5ème vitesse
    } else if (speed <= 105) {
        return 6; // 6ème vitesse
    } else {
        return 7; // 7ème vitesse
    }
}
void setup() {
    Serial.begin(115200);
    
    // Start CAN and SPI
    SPI.begin();
    
    // Initialize CAN
    while (true) {
        if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
            Serial.println("MCP2515 Initialized Successfully!");
            CAN0.setMode(MCP_NORMAL);
            break; // Exit the loop if connected
        } else {
            Serial.println("Error Initializing MCP2515. Retrying...");
            delay(1000); // Wait before retrying
        }
    }

    attachInterrupt(digitalPinToInterrupt(CAN0_INT), MCP2515_ISR, FALLING);
}

void loop() {
    // Send OBD requests
    sendOBDRequest(0x05); // PID 0x05 for engine coolant temperature
    delay(100);
    readOBDResponse();

    sendOBDRequest(0x0C); // PID 0x0C for RPM
    delay(100);
    readOBDResponse();

    sendOBDRequest(0x0D); // PID 0x0D for vehicle speed
    delay(100);
    readOBDResponse();

    sendOBDRequest(0x2F); // PID 0x2F for fuel level
    delay(100);
    readOBDResponse();

    sendOBDRequest(0x0B); // PID 0x0B for intake pressure
    delay(100);
    readOBDResponse();

    sendOBDRequest(0x42); // PID 0x42 for battery voltage
    delay(100);
    readOBDResponse();
gear = determineGear(vehicleSpeed);
    // Print data to Serial Monitor
    Serial.print("Vitesse du véhicule: ");
    Serial.println(vehicleSpeed);
    Serial.print("Niveau de carburant: ");
    Serial.println(fuelLevel);
    Serial.print("Tension de la batterie: ");
    Serial.println(batteryVoltage);
    Serial.print("RPM: ");
    Serial.println(rpm);
    Serial.print("Température du liquide de refroidissement: ");
    Serial.println(engineCoolantTemp);
    Serial.print("Pression d'admission: ");
    Serial.println(intakePressure);

    delay(1000); // Delay before the next loop iteration
}
