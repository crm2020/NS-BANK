#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53  // MEGA: 53
#define RST_PIN 5  // MEGA: 5

byte readCard[4];
String tag_UID = "";  // Replace this with the UID of your tag!!!
String tagID = "";
String IBAN = "";
bool card = false;
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
int noCard = 0;

void cardCheck() {
  if (noCard >= 2) {
    card = false;
    tagID = "";
    tag_UID = "";
    Serial.println(F("No card detected"));
  }

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    noCard++;
    delay(500);  // Poll every half second
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    delay(500);
    return;
  }

  noCard = 0;
  if (tagID == "") {
    for (uint8_t i = 0; i < 4; i++) {
      tagID.concat(String(mfrc522.uid.uidByte[i], HEX));  // Convert the UID to a single String
    }
    tagID.toUpperCase();
  }

  // Card detected, do something
  Serial.println(F("Card detected"));
  card = true;
  if (tag_UID == "") {
    tag_UID = tagID;
  }
  delay(500);
}

void readData() {
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST PART
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST PART
  for (uint8_t i = 0; i < 16; i++)
  {
    int a = 0;
    a += (int)(buffer1[i]);
    Serial.print(buffer1[i]);
    if (a != 0) {
      Serial.println((char)a);
      IBAN += (char)a;
    } else {
      break;
    }
  }
  Serial.print("\n");

  //---------------------------------------- GET SECOND PART

  byte buffer2[18];
  block = 5;

  /*status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }*/

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT SECOND PART
  for (uint8_t i = 0; i < 16; i++) {
    int b = 0;
    b += (int)(buffer2[i]);
    Serial.print(buffer2[i]);
    if (b != 0 && b >= '0' && b <= '9') {   // Limits to only numbers
      Serial.println((char)b);
      IBAN += (char)b;
    } else {
      break;
    }
  }
  Serial.print("\n");
  Serial.print(F("IBAN: "));
  Serial.println(IBAN);
}

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  SPI.begin();         // SPI bus
  mfrc522.PCD_Init();  // Initialise MFRC522
}

void loop() {
  cardCheck();
  while (card && tagID == tag_UID) {
    Serial.print("Tag ID: ");
    Serial.println(tagID);
    IBAN = "";
    readData();

    cardCheck();
  }
}