#include <Arduino.h>
#include <Key.h>
#include <Keypad.h>

//buttons
#define button1 8
#define button2 9
#define button3 10
#define button4 11
#define button5 12
#define button6 13

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {':', '0', ';'}
};
byte rowPins[rows] = {1, 2, 3, 4};
byte colPins[cols] = {5, 6, 7};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int buttons[6] = {
        button1,
        button2,
        button3,
        button4,
        button5,
        button6
};

long i = 2;

void setup() {
    Serial.begin(9600);

    for (int b: buttons) {
        pinMode(b, INPUT_PULLUP);
    }
}


void loop() {
    char key = keypad.getKey();
    if (key){
        Serial.write(key-'0'+200);
    }

    int button = 0;
    for (int b:buttons) {
        if (!digitalRead(b)){
            button = b;
        }
    }
    if (button) {
        Serial.write(button-7+100);
    }

//    i *= 2;
//    Serial.write(300);
//
//    Serial.write('A');
    delay(100);
}