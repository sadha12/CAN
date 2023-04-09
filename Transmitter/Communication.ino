#include <SPI.h>
#include <mcp2515.h>

#define CAN_MESSAGE_LENGTH 8
#define MCP2515_CS_PIN 53
#define MCP2515_INT_PIN 2

struct can_frame CANMessage;
MCP2515 mcp2515(MCP2515_CS_PIN);
volatile bool interruptTriggered = false;

void initCAN() {
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  pinMode(MCP2515_INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MCP2515_INT_PIN), interruptHandler, CHANGE);
}

void interruptHandler() {
  interruptTriggered = true;
}

void sendData(uint8_t* data, int messageId1, int messageId2) {
  // Since data is 16 bytes, it needs to be split in 2 parts and sent to the node
  // Send the first frame
  CANMessage.can_id = messageId1;
  CANMessage.can_dlc = CAN_MESSAGE_LENGTH;
  for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
    CANMessage.data[index] = data[index];
  mcp2515.sendMessage(&CANMessage);
  if (interruptTriggered) {
    Serial.println("First half of message sent");
    interruptTriggered = false;
  }

  delay(250);

  // Send the second frame
  CANMessage.can_id = messageId2;
  CANMessage.can_dlc = CAN_MESSAGE_LENGTH;
  for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
    CANMessage.data[index] = data[CAN_MESSAGE_LENGTH + index];
  mcp2515.sendMessage(&CANMessage);
  if (interruptTriggered) {
    Serial.println("Second half of message sent");
    interruptTriggered = false;
  }

  delay(250);
}
