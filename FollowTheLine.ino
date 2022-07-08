
#include <Arduino.h>
#include <analogWrite.h>
#include <Adafruit_SSD1306.h>

int ldrLeft = 34;
int ldrRight = 39;
int forwardLeft = 18;
int forwardRight = 16;
int reverseLeft = 5;
int reverseRight = 17;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(forwardLeft, OUTPUT);
  pinMode(forwardRight, OUTPUT);
  pinMode(reverseLeft, OUTPUT);
  pinMode(reverseRight, OUTPUT);
  pinMode(ldrRight, INPUT);
  pinMode(ldrLeft, INPUT);
  pinMode(ldrRight, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

int valueLdrLeft = analogRead(ldrLeft);
int valueLdrRight = analogRead(ldrRight);

Serial.println("Left: " + valueLdrLeft);
Serial.println("Right: " + valueLdrRight);

delay(500);

if(valueLdrLeft < 120 && valueLdrRight < 120 ) {
  moveForward(); }

}

void drive(int fL, int fR, int rL, int rR){
  analogWrite(forwardLeft, fL);
  analogWrite(forwardRight, fR);
  analogWrite(reverseLeft, rL);
  analogWrite(reverseRight, rR);
}

 void moveForward() {
  drive(160, 160, LOW, LOW);
}

 void moveBackwards() {
   drive(LOW, LOW, 200, 200);
 }

 void turnRight() {
   drive(180, 220, LOW, LOW);
 }

 void turnLeft() {
   drive(220, 180, LOW, LOW);
 }

 void stopVehicle() {
   drive(LOW, LOW, LOW, LOW);
 }

 
