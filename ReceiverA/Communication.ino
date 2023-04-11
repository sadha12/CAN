#include <SPI.h>
#include <mcp2515.h>

// Global variables for CAN transmission
#define MESSAGE_ID_1 0x056
#define MESSAGE_ID_2 0x057
#define MCP2515_CS_PIN 53

#define CAN_MESSAGE_LENGTH 8
struct can_frame CANMessage;
MCP2515 mcp2515(MCP2515_CS_PIN);

void initCAN() {
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void receiveData(uint8_t* data) {
  if (mcp2515.readMessage(&CANMessage) == MCP2515::ERROR_OK) {
    // Receive the first frame
    if (CANMessage.can_id == MESSAGE_ID_1) {
      for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
        data[index] = CANMessage.data[index];
    }

    // Receive the second frame
    if (CANMessage.can_id == MESSAGE_ID_2) {
      for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
        data[CAN_MESSAGE_LENGTH + index] = CANMessage.data[index];
    }
  }

  Serial.print("Encrypted data : ");
  for (size_t index = 0; index < AES_BLOCKLEN; index++)
    Serial.print(data[index], HEX);
}