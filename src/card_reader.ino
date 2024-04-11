#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53
#define RST_PIN 5

byte readCard[4];
String tag_UID = "279FC912";  // Replace this with the UID of your tag!!!
String tagID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

bool cardCheck() {
  tagID = "";
  //Check if a new tag is detected and readable or not. If not return.
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read the 4 byte UID
    for (uint8_t i = 0; i < 4; i++) {
      tagID.concat(String(mfrc522.uid.uidByte[i], HEX));  // Convert the UID to a single String
    }
    tagID.toUpperCase();
    mfrc522.PICC_HaltA();  // Stop reading
    
    return true;
  } else {
    return false;
  }
}

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  SPI.begin();         // SPI bus
  mfrc522.PCD_Init();  // Initialise MFRC522
}

void loop() {
  while (cardCheck()) {
    Serial.println(tagID);
    if (tagID == tag_UID) {
      Serial.println("Success");
    }
  }
}