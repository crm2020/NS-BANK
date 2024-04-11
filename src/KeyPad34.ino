#include <Key.h>
#include <Keypad.h>

String pin = "1234";
String enteredPin = "";
String hiddenPin = "";

char getPadKey() {
  const byte rows = 4;
  const byte cols = 4;
  char keys[rows][cols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };
  byte rowPins[rows] = {2, 3, 4, 5};
  byte colPins[cols] = {7, 8, 9, 10};
  Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
  
  return keypad.getKey();
}

void reset() {
  enteredPin = "";
  hiddenPin = "";
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void enter() {
  if (enteredPin == pin) {
    Serial.println("PIN Correct");
  } else {
    Serial.println("PIN Incorrect");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void loop() {
  char key = getPadKey();
  if (getPadKey() != 0 && enteredPin.length() < 4) {
    Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  }
  if (getPadKey() == 35) {
    enter();
  }
  if (getPadKey() == 42) {
    reset();
  }
  if (getPadKey() != 0 && getPadKey() < 58 && getPadKey() > 47) {
    if (enteredPin.length() < 4) {
      enteredPin += getPadKey();
      hiddenPin = "";
      for (int i = 0; i < enteredPin.length(); i++) {
        hiddenPin += '*';
      }
      Serial.println(hiddenPin);
    }
  }
  while (key == getPadKey()){}
}
