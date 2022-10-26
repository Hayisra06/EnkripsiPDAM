#include "mbedtls/aes.h"

#define RXD2 16
#define TXD2 17

char * key = "abcdefghijklmnop";
char *plainText = "Tech tutorials x";
unsigned char cippherTextOutput[16];
unsigned char decipheredTextOutput[16];
byte a[16];

void encrypt(char * plainText, char * key, unsigned char * outputBuffer) {
  mbedtls_aes_context aes;
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void decrypt(unsigned char * chipherText, char * key, unsigned char * outputBuffer) {
  mbedtls_aes_context aes;
  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
}

void loop() {
//  encrypt(plainText, key, cippherTextOutput);
  
  for (int i = 0; i < 16; i++) {
    char buff[3];
    sprintf(buff, "%02x", (byte)cippherTextOutput[i]);
    Serial.write((byte)cippherTextOutput[i]);
    Serial2.write((byte)cippherTextOutput[i]);
  }

  decrypt(cippherTextOutput, key, decipheredTextOutput);
  Serial2.println("");
  unsigned char tes
  Serial.println("\n\nDeciphered text:");
  for (int i = 0; i < 16; i++) {
    Serial.print((char)decipheredTextOutput[i]);
  }
  delay(5000);
}
