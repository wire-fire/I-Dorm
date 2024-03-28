/**
 * ----------------------------------------------------------------------------
 * Written by Jack McTasney, original code by: https://github.com/miguelbalboa/rfid
 * ----------------------------------------------------------------------------
**/
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9  // Configurable, see typical pin layout above
#define SS_PIN 10  // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
MFRC522::MIFARE_Key key;
void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial)
    ;                  // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  Serial.println("I-Dorm V2 RFID Program: 1");
  Serial.println("Insert a card or keyfob for comparison against master codes");
}
/**
 * Main loop.
 */
void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (!mfrc522.PICC_IsNewCardPresent())
    return;
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
    return;
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  // Check for compatibility
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI
      && piccType != MFRC522::PICC_TYPE_MIFARE_1K
      && piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("This sample only works with MIFARE Classic cards."));
    return;
  }
  //get UID of card
  int i;
  int uid[4];
  for (i = 0; i < 4; i++) {
    uid[i] = getUID(i);
  }
  //Card IDs
  int keyfob1ID[4] = { 138, 184, 213, 128 };  //keyfob1 UID
  int keyfob2ID[4] = { 26, 228, 198, 126 };   //keyfob2 UID
  int keycardID[4] = { 230, 46, 216, 3 };     //keycard ID
  //There is probably a better way to do this
  bool check1, check2, check3;
  check1 = UID_check(uid, keyfob1ID);
  check2 = UID_check(uid, keyfob2ID);
  check3 = UID_check(uid, keycardID);
  if (check1 == true) {
    Serial.println("This is keyfob1");
    auth();
  } else if (check2 == true) {
    Serial.println("This is keyfob2");
  } else if (check3 == true) {
    Serial.println("This is the keycard");
  }
  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}
int getUID(int i) {
  int uidByte;
  uidByte = mfrc522.uid.uidByte[i];
  return (uidByte);
}
bool UID_check(int array1[4], int array2[4]) {
  int i;
  int flag = 0;
  for (i = 0; i < 4; i++) {
    if (array1[i] == array2[i]) {
      flag += 1;
    }
  }
  if (flag == 4) {
    return (true);
  } else {
    return (false);
  }
}
void auth() {
  int i;
  Serial.println("Authentication Successful!\nWelcome to the Program!");
  for (i=0;i<3;i++){
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}