#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
//#include <ZumoReflectanceSensorArray.h>
 
#define LED 13
#define IRPin 3
int IRval = 0;
int IRavg = 0;

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1500 // microseconds
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        400
#define FORWARD_SPEED     200
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
#define RAM 400 
#define INCHES_TO_ZUNITS 17142.0
#define SHOOT(distance, spd)(((INCHES_TO_ZUNITS * (distance)) / spd))

 
ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
 
//ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);
   
  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);  
  delay(1000);
}
 
void setup()
{
  // uncomment if necessary to correct motor directions
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);
   
  pinMode(LED, HIGH);
  pinMode(A4, INPUT);
  Serial.begin(9600);
  button.waitForButton(); 
//  waitForButtonAndCountDown();
}

void loop()
{
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }
  IRavg = 0;

  IRval = analogRead(A4);
  IRval += analogRead(A4);
  IRval += analogRead(A4);
  
  IRavg = IRval/3;
//  Serial.println(IRval);
//  delay(10);
  
  if (IRavg > 260)
  {
    motors.setSpeeds(RAM, RAM);
    delay(SHOOT(3, RAM));
  }
  else if (IRavg > 170)
  {
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(SHOOT(3, FORWARD_SPEED));
  }
  else
  {
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED); 
  }

//  sensors.read(sensor_values);
//  IRval = analogRead(IRPin);
  
//  while (IRval > 102)
//  {
//    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
//    IRval = analogRead(IRPin);
//  }
  
//  if (sensor_values[0] < QTR_THRESHOLD)
//  {
    // if leftmost sensor detects line, reverse and turn to the right
//    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
//    delay(REVERSE_DURATION);
//    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
//    delay(TURN_DURATION);
//    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
//  }
//  else if (sensor_values[5] < QTR_THRESHOLD)
//  {
//    // if rightmost sensor detects line, reverse and turn to the left
//    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
//    delay(REVERSE_DURATION);
//    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
//    delay(TURN_DURATION);
//    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
//  }
//  else
//  {
//    // otherwise, go straight
//    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
//  }
}
