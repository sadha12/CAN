struct AES_ctx context;
uint8_t key[16] = {
  0x2D, 0xC6, 0x0D, 0xE1, 0x9E, 0x32, 0x8B, 0x39,
  0x62, 0x7B, 0x5A, 0xF6, 0x2E, 0x03, 0x75, 0x80
};
uint8_t paddedDecodedText[AES_BLOCKLEN];

void initDecrypt() {
  AES_init_ctx(&context, key);
}

uint8_t removePadding(uint8_t* paddedDecodedText) {
  return paddedDecodedText[0];
}

void decryptData(uint8_t* cipherText, uint8_t* decodedText) {
  for (size_t index = 0; index < AES_BLOCKLEN; index++)
    paddedDecodedText[index] = cipherText[index];
  AES_ECB_decrypt(&context, paddedDecodedText);
  *decodedText = removePadding(paddedDecodedText);
  Serial.println(" Decoded data : " + String(*decodedText));
}