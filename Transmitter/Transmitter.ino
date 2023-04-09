#include "aes.c"
#include "aes.h"

// Global variables for data
// It is assumed that the data is 1 byte and only 1 AES block is required
uint8_t plainText;
uint8_t cipherText[AES_BLOCKLEN];

// Global variables for CAN transmission
#define MESSAGE_ID_1 0x056
#define MESSAGE_ID_2 0x057

void setup() {
  Serial.begin(9600);
  initSensor();
  initEncrypt();
  initCAN();
}

void loop() {
  sense(&plainText);
  encryptData(&plainText, cipherText);
  sendData(cipherText, MESSAGE_ID_1, MESSAGE_ID_2);
}
