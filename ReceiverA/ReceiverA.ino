#include "aes.c"
#include "aes.h"

// Global variables for data
// It is assumed that the data is 1 byte and only 1 AES block is required
uint8_t cipherText[AES_BLOCKLEN];
uint8_t decodedText;

void setup() {
  Serial.begin(9600);
  initCAN();
  initDecrypt();
  initDisplay();
}

void loop() {
  receiveData(cipherText);
  decryptData(cipherText, &decodedText);
  // displayInLED(decodedText);
  delay(100);
}