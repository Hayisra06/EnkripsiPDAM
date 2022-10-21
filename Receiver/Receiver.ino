#include "mbedtls/aes.h"
char * key = "abcdefghijklmnop";
char *plainText = "Tech tutorials x";
unsigned char cipherTextOutput[16];
unsigned char decipheredTextOutput[16];
unsigned char hasilEnkripisi[16];
unsigned char * outputBuffer;

#define RXD2 16
#define TXD2 17
#define BUZZER_SIZE 1000

String dataBuffer;
char txt[15];
int i;
int Status = 0;

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
    int n = 0;
    byte dta[16];
    while (char(baca) != '\n') {
      Serial.write(baca);
      dta[n] =  (unsigned char)baca;
      n++;
    }
    strcpy((byte*)cipherTextOutput, dta);
    decrypt(cipherTextOutput, key, hasilEnkripisi);

    for (int i = 0; i < 16; i++) {
      Serial.print(char(hasilEnkripisi[i]));
    }


    //    if(conChip){
    //
    //      }

  }
}
