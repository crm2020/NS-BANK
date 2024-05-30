#include <Wire.h>
#define LENGTH 3

int bakjeMotor[2] = {6, 7};

int inputs[3][2] = {
  {12, 13},
  {10, 11},
  {8, 9}
};

int IRSens = 2;

int geld[3] = {4, 6, 1}; // 10, 20, 50

void bakjeIn() {
  analogWrite(bakjeMotor[0], 200);
  analogWrite(bakjeMotor[1], 0);
  delay(2000);  // check timing
  analogWrite(bakjeMotor[0], 0);
  analogWrite(bakjeMotor[1], 0);
}

void bakjeUit() {
  analogWrite(bakjeMotor[0], 0);
  analogWrite(bakjeMotor[1], 200);
  delay(1500);  // check timing
  analogWrite(bakjeMotor[0], 0);
  analogWrite(bakjeMotor[1], 0);
  delay(20000);
  bakjeIn();
}

void draai(int num) {
  Serial.print(num);
  Serial.println(" draait");
  analogWrite(inputs[num][0], 200);
  analogWrite(inputs[num][1], 0);
}

void stop() {
  for (int k = 0; k < LENGTH; k++) {
    analogWrite(inputs[k][0], 0);
    analogWrite(inputs[k][1], 0);
  }
}

void printGeld() {
  // Ergens check voor reed sensor als we die gaan gebruiken (!!)
  for (int j = 0; j < LENGTH; j++) {
    while (geld[j] > 0) {
      draai(j);
      while (digitalRead(IRSens) == 1) {}  // Als IR sensor niks ziet, wacht
      geld[j]--;
      stop();
      delay(500);
    }
  }
  delay(2000);
  bakjeUit();
}

void krijgGeld() {
  int j = 0;
  while (Wire.available()) { // peripheral may send less than requested
    int i = Wire.read(); // receive a byte as int
    geld[j] = i;
    j++;
    Serial.print(j); Serial.print(": "); Serial.println(i);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(1);  // join i2c bus with address 1
  Wire.onReceive(krijgGeld);

  for (int i = 0; i < LENGTH; i++) {
    pinMode(inputs[i][0], OUTPUT);
    pinMode(inputs[i][1], OUTPUT);
  }
  pinMode(IRSens, INPUT);
  pinMode(bakjeMotor[0], OUTPUT);
  pinMode(bakjeMotor[1], OUTPUT);

  printGeld();
}

void loop() {
  // put your main code here, to run repeatedly:
}