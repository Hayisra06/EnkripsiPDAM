#include "mbedtls/aes.h"
#include "mbedtls/aes.h"

char * key = "abcdefghijklmnop";
char *plainText = "Tech tutorials x";
unsigned char cipherTextOutput[16];
unsigned char decipheredTextOutput[16];

byte buf[16];

const byte bufferSize = 16;
char inputBuffer[bufferSize + 1];

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
  if (Serial2.available() > 0) {
    byte baca = Serial2.read();
    byte * top = &baca;
    //    Serial.print(baca);
    Serial.print(top);
    encrypt(plainText, key, cipherTextOutput);
    unsigned char * tes = (unsigned char *) &baca;
    decrypt(tes, key, decipheredTextOutput);


     //    String baca = Serial2.readString();
    //    Serial.println(baca);
    //    int len = baca.length();
    //    Serial.println(len);
    //    baca.getBytes(buf, 16);
    //    for (int i = 0; i < 16; i++) {
    //      Serial.write(buf[i]);
    //    }
  }
  //  if (Serial2.available() > 0) {
  //    baca = Serial2.read();
  //    Serial.print(baca);
  //
  //    //    int n = 0;
  //    //    byte dta[16];
  //    //    while (char(baca) != '\n') {
  //    //      Serial.write(baca);
  //    //      dta[n] =  (unsigned char)baca;
  //    //      n++;
  //    //    }
  //    //    strcpy((byte*)cipherTextOutput, dta);
  //          unsigned char * tes = (unsigned char *) baca;
  //          encrypt(plainText, key, cipherTextOutput);
         
  //    //
  //    //    for (int i = 0; i < 16; i++) {
  //    //      Serial.print(char(decipheredTextOutput[i]));
  //    //    }
  //
  //
  //    //    if(conChip){
  //    //
  //    //      }
  //
  //  }
}
