#include <Arduino.h>
#include <analogWrite.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C
#define SSD1306_NO_SPLASH

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Motor config
int motorPinLA = 5; //Linkerwiel achteruit
int motorPinLV = 18; //Linkerwiel vooruit
int motorPinRV = 16; //Rechterwiel vooruit
int motorPinRA = 17; //Rechterwiel achteruit

// IR config
int ldrRight = 34;
int ldrLeft = 39;
int pinR = 0;
int pinL = 0;
int colorThreshold = 2700;




void setup(){
  Serial.begin(9600);


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Infinite loop to stop the program from executing the rest of the code.
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  pinMode(motorPinRA, OUTPUT);
  pinMode(motorPinRV, OUTPUT);
  pinMode(motorPinLV, OUTPUT);
  pinMode(motorPinLA, OUTPUT);
}

void loop(){
  // clear display so we can send new data to it.
  display.clearDisplay();

  // reset cursor to top right corner of the screen.
  display.setCursor(0,0);
  display.println("PinR: " + String(analogRead(ldrRight)));
  display.println("PinR: " + String(analogRead(ldrLeft)));
  display.display();
  
  //Read the IR pins
  int pinR = analogRead(ldrRight) / colorThreshold;
  int pinL = analogRead(ldrLeft) / colorThreshold;

    //if both pins reaches the threshold, stop the robot from moving.
  if(pinL >= 1 && pinR >= 1){
     stopVehicle();
    
    //if pin right reaches the threshold turn the robot left with % power
  }else if(pinL == 0 && pinR >= 1){
    turnLeft(50);

    //if pin left reaches the threshold turn the robot left with % power
  }else if(pinL >= 1 && pinR == 0){
    turnRight(50);
    
    // continue moving forward if the threshold is not reached on either pins.
  }else if(pinL == 0 && pinR == 0){
    driveForward(40);
  }
}
