#include <Arduino.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#define SS_PIN 53  // MEGA: 53
#define RST_PIN 48  // MEGA: 5

#define slave 1

#define button1 6
#define button2 5
#define button3 4
#define button4 3
#define button5 2
#define button6 14

int buttons[6] = {
        button1,
        button2,
        button3,
        button4,
        button5,
        button6
};

String IBAN = "";
bool IBANwegGehaald = false;
bool IBANgestuurd = false;
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {':', '0', ';'}
};
byte rowPins[rows] = {13, 12, 11, 10};
byte colPins[cols] = {9, 8, 7};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void checkCard(){
  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);
  MFRC522::StatusCode result = mfrc522.PICC_WakeupA(bufferATQA, &bufferSize);
  
  if (result == MFRC522::STATUS_OK || result == MFRC522::STATUS_COLLISION) {
    // Select one of the cards
    if (mfrc522.PICC_ReadCardSerial()) {
      MFRC522::MIFARE_Key key;
      for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
      IBAN = "";
      readBlock(4, key, IBAN);
      readBlock(5, key, IBAN);

      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }else{
    if (IBAN != ""){
      IBANwegGehaald = true;
    }
    IBAN = "";
  }
}

bool readBlock(byte block, MFRC522::MIFARE_Key &key, String &data) {
  byte buffer[18];
  byte len = 18;
  MFRC522::StatusCode status;

  // Authenticate with the block
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    // Serial.print(F("Authentication failed for block "));
    // Serial.print(block);
    // Serial.print(F(": "));
    // Serial.println(mfrc522.GetStatusCodeName(status));
    // return false;
  }

  // Read data from the block
  status = mfrc522.MIFARE_Read(block, buffer, &len);
  if (status != MFRC522::STATUS_OK) {
    // Serial.print(F("Reading failed for block "));
    // Serial.print(block);
    // Serial.print(F(": "));
    // Serial.println(mfrc522.GetStatusCodeName(status));
    // return false;
  }

  // Process and append data to IBAN string
  for (uint8_t i = 0; i < 16; i++) {
    if (buffer[i] != 0) {
      IBAN += (char)buffer[i];
    } else {
      break;
    }
  }

  return true;
}

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  SPI.begin();         // SPI bus
  mfrc522.PCD_Init();  // Initialise MFRC522
  for (int b: buttons) {
    pinMode(b, INPUT_PULLUP);
  }
  Wire.begin();
}

void loop() {
  checkCard();
  bool knopIngedruktOfKeypad = false;
  // Serial.print(F("IBAN: "));

  
  // else{
  //   Serial.write(24);
  // }

  // keypad =========
  char key = keypad.getKey();
  if (key){
    Serial.write(key-'0'+200);
    knopIngedruktOfKeypad = true;
  }

  //knoppen ==============
  int button = 0;
  for (int i = 0; i < 6; i++) {
    if (!digitalRead(buttons[i])){
      Serial.write(i+100+1);
      knopIngedruktOfKeypad = true;
      break;
    }
  }

  //kaartlezer ============
  if (IBAN != "" && !knopIngedruktOfKeypad && !IBANgestuurd){
    for(char c: IBAN){
      Serial.write(c);
    }
    Serial.write('\n');
    IBANgestuurd = true;
  }
  if(IBANwegGehaald){
    IBANgestuurd = false;
    IBANwegGehaald = false;
    Serial.write(24);
  }

  


  int vijftig, twintig, tien;
  if(Serial.read() == 1){
    vijftig = Serial.read();
    twintig = Serial.read();
    tien = Serial.read();
    Wire.beginTransmission(slave);
    Wire.write(tien);
    Wire.write(twintig);
    Wire.write(vijftig);
    Wire.endTransmission();
    Serial.write(3);
    
  }

  delay(100);
}