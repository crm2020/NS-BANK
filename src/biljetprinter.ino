#define LENGTH 3

int bakjeMotor[2] = {11, 12};

int inputs[3][2] = {
  {46, 47},
  {44, 45},
  {42, 43}
};

int IRSens[3] = {36, 35, 34};

int geld[3] = {4, 6, 1}; // 10, 20, 50

void bakjeIn() {  // Misschien als pinpas eruit wordt gehaald
  analogWrite(bakjeMotor[0], 0);
  analogWrite(bakjeMotor[1], 0);
}

void bakjeUit() {
  analogWrite(bakjeMotor[0], 200);
  analogWrite(bakjeMotor[1], 200);
  delay(10000);
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
      while (digitalRead(IRSens[j]) == 1) {}  // Als IR sensor niks ziet, wacht
      geld[j]--;
      stop();
      delay(500);
    }
  }
  delay(1000);
  //bakjeUit();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0; i < LENGTH; i++) {
    pinMode(inputs[i][0], OUTPUT);
    pinMode(inputs[i][1], OUTPUT);
    pinMode(IRSens[i], INPUT);
  }
  pinMode(bakjeMotor[0], OUTPUT);
  pinMode(bakjeMotor[1], OUTPUT);

  printGeld();
}

void loop() {
  // put your main code here, to run repeatedly:
}