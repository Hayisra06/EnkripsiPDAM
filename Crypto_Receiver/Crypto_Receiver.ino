#include "mbedtls/aes.h"
char * key = "abcdefghijklmnop";
char *plainText = "Tech tutorials x";
char cipherTextOutput[16] = {0};
unsigned char decipheredTextOutput[16];

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

// convert a hex string such as "A489B1" into an array like [0xA4, 0x89, 0xB1].

const byte MaxByteArraySize = 5;

//void setup()
//{
//  Serial.begin(115200);
//
//  byte byteArray[MaxByteArraySize] = {0};
//
//  hexCharacterStringToBytes(byteArray, "A489B1");
//  dumpByteArray(byteArray, MaxByteArraySize);
//
//  hexCharacterStringToBytes(byteArray, "A489B10");
//  dumpByteArray(byteArray, MaxByteArraySize);
//}


void hexCharacterStringToBytes(byte *byteArray, const char *hexString)
{
  bool oddLength = strlen(hexString) & 1;

  byte currentByte = 0;
  byte byteIndex = 0;

  for (byte charIndex = 0; charIndex < strlen(hexString); charIndex++)
  {
    bool oddCharIndex = charIndex & 1;

    if (oddLength)
    {
      // If the length is odd
      if (oddCharIndex)
      {
        // odd characters go in high nibble
        currentByte = nibble(hexString[charIndex]) << 4;
      }
      else
      {
        // Even characters go into low nibble
        currentByte |= nibble(hexString[charIndex]);
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
    else
    {
      // If the length is even
      if (!oddCharIndex)
      {
        // Odd characters go into the high nibble
        currentByte = nibble(hexString[charIndex]) << 4;
      }
      else
      {
        // Odd characters go into low nibble
        currentByte |= nibble(hexString[charIndex]);
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
  }
}

void dumpByteArray(const byte * byteArray, const byte arraySize)
{

  for (int i = 0; i < arraySize; i++)
  {
    Serial.print("0x");
    if (byteArray[i] < 0x10)
      Serial.print("0");
    Serial.print(byteArray[i], HEX);
    Serial.print(", ");
  }
  Serial.println();
}

byte nibble(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';

  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;

  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;

  return 0;  // Not a valid hexadecimal character
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
}

void loop() {
  if (Serial2.available())
  {
    int i = 0;
    while (Serial2.available() && i < 63)
    {
      cipherTextOutput[i] = (char)Serial2.read();
      i++;
    }
    cipherTextOutput[i] = '\0';
    if (cipherTextOutput[0])
    {
      Serial.print("data diterima dari Lora ");
      Serial.println(cipherTextOutput);
    }

    byte byteArray[MaxByteArraySize] = {0};

    hexCharacterStringToBytes(byteArray, "A489B1");
    dumpByteArray(byteArray, MaxByteArraySize);

    unsigned char * cipherText = (unsigned char *)byteArray;
    decrypt(cipherText, key, decipheredTextOutput);

    Serial.println("\n\nDeciphered text:");
    for (int i = 0; i < 16; i++) {
      Serial.print((char)decipheredTextOutput[i]);
    }
  }
}
