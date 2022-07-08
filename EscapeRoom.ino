#include <analogWrite.h>
#include <Adafruit_VL53L0X.h>

// Declares the Lidar sensor
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Sonar Pins
// Front Right Sensor for checking walls
const int pinFROut = 19;
const int pinFRIn = 23;
// Front Left Sensor for checking walls
const int pinFLOut = 12;
const int pinFLIn = 14;

// Wheels
const int RB = 5; // Right Back
const int RF = 18; // Right Front
const int LB = 17; // Left Back
const int LF = 16; // Left Front

void setup()
{
  pinMode(pinFROut, OUTPUT); // Sets the pinFROut as an Output
  pinMode(pinFRIn, INPUT); // Sets the pinFRIn as an Input
  pinMode(pinFLOut, OUTPUT); // Sets the pinFLOut as an Output
  pinMode(pinFLIn, INPUT); // Sets the pinFLIn as an Input
  pinMode(RB, OUTPUT); // Sets the RB as an output
  pinMode(RF, OUTPUT); // Sets the RF as an output
  pinMode(LB, OUTPUT); // Sets the LB as an output
  pinMode(LF, OUTPUT); // Sets the LF as an output

  // Stops the code if the lidar isn't working
  if (!lox.begin())
  {
    while(1);
  }
}

void loop()
{
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  // lox = LiDar
  // pinFROut & pinFRIn = checks front-right sensor for walls
  // pinFLOut & pinFLIn = checks front-left sensor for walls
  // 
  // RB, RF, LB, LF = engines (right-left, back-front)
  if (measure.RangeStatus != 4) {
    if (measure.RangeMilliMeter > 700)
    {
      drive(0,200,200,0);
      delay(400);
      drive(200,200,0,0);
      delay(800);
    }
    else
    {
      if(sonar(pinFROut, pinFRIn) < 19)
      {
        drive(210, 0, 0, 160);
        delay(600);
        drive(200,200,0,0);
      }
      else if(sonar(pinFLOut, pinFLIn) < 20)
      {
        drive(0, 210, 160, 0);
        delay(600);
        drive(200,200,0,0);
      }
    }  
  }
}

// Function that stars or stops the motors based on input speeds
void drive(int RFs, int LFs, int RBs, int LBs)
{
  analogWrite(RF, RFs);
  analogWrite(LF, LFs);
  analogWrite(RB, RBs);
  analogWrite(LB, LBs);
}

// Function that takes two pins and then reads the sonar info from those two pins
double sonar(int pinOut, int pinRead)
{
  // Defines speed of sound and declares local variables
  // The speed of sound is used for calculating the distance
  #define SOUND_SPEED 0.034
  long duration;
  float distanceCm;
  
  // Clears the pinOut if it was running
  digitalWrite(pinOut, LOW);
  delayMicroseconds(2);
  
  // Sets the pinOut on HIGH state for 10 micro seconds and then to low again
  digitalWrite(pinOut, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinOut, LOW);
  
  // Reads the pinRead, returns the sound wave travel time in microseconds
  duration = pulseIn(pinRead, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  // Returns the distance in cm
  return distanceCm;
} 
