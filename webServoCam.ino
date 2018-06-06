#include <Servo.h>

unsigned int joySWPin = 42;
unsigned int ledMorroPin = 43;
unsigned int servoXPin = 44;
unsigned int servoYPin = 45;

Servo servoX;
Servo servoY;
int angX = 0;
int angY = 0;

int joyX = 0;
int joyY = 0;
int joyXmap = 0;
int joyYmap = 0;
bool joySW = false;
bool joySWLastState = false;

int lastDebounceTime = 0;
bool lastButtonState = false;

String charStringSerialInput = "";
char charVector[20];
bool charEnd = false;



void setup() {

  Serial.begin(9600);
  pinMode(joySWPin, INPUT);
  pinMode(ledMorroPin, OUTPUT);
  pinMode(13, OUTPUT);
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);
  charStringSerialInput.reserve(20);

}

void loop() {


   if (charEnd) {

    charEnd = false;
    charStringSerialInput.toCharArray(charVector, 20);
    int serialInteger = atoi(charVector);

    if (serialInteger == 1) {
      digitalWrite(43, HIGH);
      digitalWrite(13, HIGH);
    }
    else if (serialInteger == 2) {
      digitalWrite(43, LOW);
      digitalWrite(13, LOW);
    }

    charStringSerialInput = "";
  }
  
  joyX = analogRead(A0);
  //delay(10);
  joyY = analogRead(A1);
  //delay(10);

  joyX = map(joyX, 0, 1024, 0, 180);
  joyY = map(joyY, 0, 1024, 0, 180);

  servoX.write(joyX);
  //delay(0);
  servoY.write(joyY);
  //delay(0);

  joySW = digitalRead(joySWPin);
  if (joySW != joySWLastState) {
    lastDebounceTime = millis();
    lastButtonState = joySW;
  }

  digitalWrite(ledMorroPin, joySW);

 

}

void serialEvent() {

  while (Serial.available()) {
    char inputChar = Serial.read();

    charStringSerialInput += inputChar;
    if (inputChar == '\n') {
      charEnd = true;
    }
  }
}



