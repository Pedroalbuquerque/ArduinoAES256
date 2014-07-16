#include "aes256.h" //Include library files
#define DUMP(str, i, buf, sz) { Serial.print(str); \
                               for(i=0; i<(sz); ++i) { if(buf[i]<0x10) Serial.write('0'); Serial.print(buf[i], HEX); Serial.write(' ');} \
                               Serial.println(); } //Help function for printing the Output

AES256 aes;

void setup() {
  int i;
  Serial.begin(38400);
  
  Serial.println("Initializing AES256... ");
  uint8_t key[32];
  uint8_t data[16];
  /* put a test vector */
  for (i = 0; i < sizeof(data);i++) data[i] = i * 16 + i;
  for (i = 0; i < sizeof(key);i++) key[i] = i;
  DUMP("Key: ", i, key, sizeof(key));
  aes.init(key);
  
  DUMP("Unencrypted    data: ", i, data, sizeof(data));
  Serial.println("Expected  encrypted: 8E A2 B7 CA 51 67 45 BF EA FC 49 90 4B 49 60 89");  
  aes.encrypt_ecb(data);
  DUMP("Real encrypted data: ", i, data, sizeof(data));
  
  aes.decrypt_ecb(data);
  DUMP("Back decrypted data: ", i, data, sizeof(data));
  
  aes.done();
}

void loop() {
}
