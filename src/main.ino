#include <Arduino.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_Thermal.h>

#include <SoftwareSerial.h>

#define bonlogo_width 80
#define bonlogo_height 80

#define TX_PIN 14
#define RX_PIN 15

static const uint8_t PROGMEM bonlogo [] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1C, 0x0E, 0x00, 0xFC, 0x00, 0x1F, 0x00, 0x00,
  0xF8, 0x00, 0x1C, 0x0E, 0x07, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1E, 0x0E, 0x0F, 0xF8,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1F, 0x0E, 0x1F, 0x80, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00,
  0x1F, 0x0E, 0x3C, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1F, 0x8E, 0x3C, 0x00, 0x00, 0x1F,
  0x00, 0x00, 0xF8, 0x00, 0x1F, 0xCE, 0x3F, 0xF8, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1D, 0xCE,
  0x1F, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1D, 0xEE, 0x07, 0xFC, 0x00, 0x1F, 0x00, 0x00,
  0xF8, 0x00, 0x1C, 0xFE, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1C, 0x7E, 0x00, 0x1C,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1C, 0x7E, 0x00, 0x7C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00,
  0x1C, 0x3E, 0x1F, 0xF8, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1C, 0x1E, 0x3F, 0xF0, 0x00, 0x1F,
  0x00, 0x00, 0xF8, 0x00, 0x1C, 0x0E, 0x1F, 0xC0, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x1F, 0x00, 0x00,
  0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFC,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00,
  0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F,
  0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00,
  0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00,
  0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00,
  0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x1F,
  0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00,
  0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00,
  0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00,
  0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x1F,
  0x00, 0x00, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x3F, 0xFF,
  0xFF, 0xFC, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x1F, 0x00, 0x00,
  0xF8, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x0F, 0x80, 0x01, 0xF0,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x07, 0xC0, 0x03, 0xE0, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00,
  0x03, 0xE0, 0x07, 0xC0, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x01, 0xF0, 0x0F, 0x80, 0x00, 0x1F,
  0x00, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x1F, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x7C,
  0x3E, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x3E, 0x7C, 0x00, 0x00, 0x1F, 0x00, 0x00,
  0xF8, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00,
  0x00, 0x23, 0xC0, 0x77, 0x0E, 0x1F, 0x00, 0x00, 0xF8, 0x3F, 0xC0, 0x70, 0xF0, 0x77, 0x1E, 0x1F,
  0x00, 0x00, 0xF8, 0x3F, 0xE0, 0xF0, 0xF0, 0x77, 0x3E, 0x1F, 0x00, 0x00, 0xF8, 0x3F, 0xF0, 0xF0,
  0xF8, 0x77, 0x7C, 0x1F, 0x00, 0x00, 0xF8, 0x38, 0x70, 0xF8, 0xFC, 0x77, 0xF8, 0x1F, 0x00, 0x00,
  0xF8, 0x3F, 0xF1, 0xF8, 0xFE, 0x77, 0xF0, 0x1F, 0x00, 0x00, 0xF8, 0x3F, 0xE1, 0xFC, 0xEF, 0x77,
  0xE0, 0x1F, 0x00, 0x00, 0xF8, 0x3F, 0xC3, 0xDC, 0xE7, 0x77, 0xC0, 0x1F, 0x00, 0x00, 0xF8, 0x3F,
  0xF3, 0xFE, 0xE7, 0xF7, 0xE0, 0x1F, 0x00, 0x00, 0xF8, 0x38, 0xF3, 0xFE, 0xE3, 0xF7, 0xF0, 0x1F,
  0x00, 0x00, 0xF8, 0x38, 0xF7, 0xFE, 0xE1, 0xF7, 0x78, 0x1F, 0x00, 0x00, 0xF8, 0x3F, 0xF7, 0x0E,
  0xE0, 0xF7, 0x3E, 0x1F, 0x00, 0x00, 0xF8, 0x3F, 0xCF, 0x07, 0xE0, 0x77, 0x1E, 0x1F, 0x00, 0x00,
  0xF8, 0x3E, 0x0E, 0x07, 0xE0, 0x77, 0x0E, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x0E, 0x03, 0xE0, 0x00,
  0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00
};
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor


String location = "Wijnhaven Rotterdam";
String date = "07/06/2024";
String time = "12:05";
int transID = 12902;
String bonIBAN = "***********093";
int bedrag = 0;

#define SS_PIN 53  // MEGA: 53
#define RST_PIN 48  // MEGA: 5


#define slave 1

#define button1 6
#define button2 5
#define button3 4
#define button4 3
#define button5 2
#define button6 22

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

void printBon(){
  printer.printBitmap(bonlogo_width, bonlogo_height, bonlogo);
  printer.justify('L');
  printer.setFont('A');
  printer.setSize('M');
  printer.println("Nederlandse Staat Bank");

  printer.println();
  printer.setSize('S');
  printer.println(location); 
  printer.print("Datum: "); printer.print(date);
  printer.print("\tTijd: "); printer.println(time);
  printer.println(); printer.justify('L');
  printer.print("IBAN: "); printer.println(IBAN);
  printer.print("Transactie ID: "); printer.println(transID);

  printer.justify('C'); printer.println("-----------------------------");
  printer.println();
  printer.justify('R'); printer.print("Bedrag:\t"); printer.print(bedrag); printer.println(",00 EUR");
  printer.println();
  printer.justify('C'); printer.println("-----------------------------");
  printer.println("Bedankt voor het pinnen bij de");
  printer.println("Nederlandse Staat Bank."); printer.println();
  printer.println("Graag tot ziens!");
  printer.println(); printer.println(); printer.println();
  printer.sleep();      // Tell printer to sleep
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
}

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  SPI.begin();         // SPI bus
  mfrc522.PCD_Init();  // Initialise MFRC522
  for (int b: buttons) {
    pinMode(b, INPUT_PULLUP);
  }
  Wire.begin();
  mySerial.begin(19200);
  printer.begin();
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

  //geld printer=========
  int request = Serial.read();
  
  int vijftig, twintig, tien;
  if(request == 1){
    vijftig = Serial.read();
    twintig = Serial.read();
    tien = Serial.read();
    Wire.beginTransmission(slave);
    Wire.write(tien);
    Wire.write(twintig);
    Wire.write(vijftig);
    Wire.endTransmission();
    Serial.write(3);

  //bon printer============
  }else if(request == 2){
    int hundreds = Serial.read();
    int tens = Serial.read();
    bedrag = hundreds*100+tens*10;
    int hours = Serial.read();
    int minutes = Serial.read();
    time = String(hours) + ":" + String(minutes);
    printBon();
  }

  delay(100);
}