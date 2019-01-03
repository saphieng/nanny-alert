/*
 * Project nanny-alert
 * Description: Device that can be used to alert for help running on an electron
 * Author: Cameron Owen
 * Date: 29/12/18
 */
#include "application.h"
#include "Particle.h"
#include <math.h>
SYSTEM_MODE(SEMI_AUTOMATIC);
// Electron Specific Setup
// A FuelGauge named 'fuel' for checking on the battery state
FuelGauge fuel;

// Setup code for speaker
int speakerPin = A4;
//RGB Setup code
int led_r = D5;
int led_g = D6;
int led_b = D7;

//RDB colour definitions
#define RED  0
#define BLUE  1
#define GREEN  2
#define ORANGE  3
#define PURPLE  4
#define WHITE   5
#define BLACK   6

//System states
#define CONNECTING 10
#define ALERT 11
#define CHARGING 12
#define NORMAL 13

//Remote Reciever IO
int a_btn = D0;
int b_btn = D1;
int c_btn = D2;
int d_btn = D3;
int aux_power = D4;
int manual_btn = A0;
long pressTime = 0;

//Global variables
bool prevAlertState = FALSE;
bool  alertTriggered = FALSE;
bool charging = TRUE;
bool assistanceRequired = FALSE;
int currentSystemState = NORMAL;
bool blackout = FALSE;

// setup() runs once, when the device is first turned on.
void setup() {
  //external RGB
  pinMode(led_r,OUTPUT);
  pinMode(led_g,OUTPUT);
  pinMode(led_b,OUTPUT);
  //input setups
  pinMode(manual_btn, INPUT_PULLDOWN);
  //pinMode(a_btn, INPUT_PULLDOWN);
  //pinMode(b_btn, INPUT_PULLDOWN);
  //pinMode(c_btn, INPUT_PULLDOWN);
  pinMode(d_btn, INPUT_PULLDOWN);
  pinMode(aux_power, INPUT_PULLDOWN);
  setRGBColour(ORANGE);
  Particle.function("batt", batteryStatus);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  //Check if particle is connected
  if (Particle.connected() == false) {
    Particle.connect();
  }

  //Monitor if auxilary power is connected
  charging = digitalRead(aux_power);

  //Monitor the button state
  alertTriggered = checkAlertButtons();
  if (alertTriggered){
    pressTime = millis();
    while(alertTriggered && ((millis()-pressTime) <= 3000)){
      alertTriggered = checkAlertButtons();
    }
    if (millis()-pressTime > 3000){
      resetAlarm();
    }
    else{
      sendForHelp();
    }
  }

  monitorSystemState();
  prevAlertState = alertTriggered;
  delay(100);
}

//Set The RGB based on the state of the SYSTEM
void monitorSystemState (){
  //Assitcance is required
  if (assistanceRequired){
    setRGBColour(RED);
    currentSystemState = ALERT;
  }
  //Particle not connected
  else if (Particle.connected() == false){
    setRGBColour(ORANGE);
    currentSystemState = CONNECTING;
  }
  //System is running on battery
  else if (!charging){
    setRGBColour(PURPLE);
    if (!blackout){
      blackout = TRUE;
      Particle.publish("bo", PRIVATE);
    }
    currentSystemState = CHARGING;
  }
  //System in normal state and running off power
  else{
    setRGBColour(GREEN);
    if (blackout){
      blackout = FALSE;
      Particle.publish("pr", PRIVATE);
    }
    currentSystemState = NORMAL;
  }
}
//IFTTT functions for alerting
void sendForHelp(){
    assistanceRequired = TRUE;
    tone(speakerPin,1000,1000);
    Particle.publish("sfh", PRIVATE);
}

void resetAlarm(){
    assistanceRequired = FALSE;
    setRGBColour(BLUE);
    noTone(speakerPin);
    Particle.publish("fa", PRIVATE);
    delay(1000);
}

void testAlert(){
    setRGBColour(ORANGE);
    tone(speakerPin,1000,1000);
    Particle.publish("ta", PRIVATE);
    delay(1000);
}

//Set each individual RGB Colour
//---------------------------------------------------------------
void setRGBColour (int colour){
  switch(colour){
    case RED:
      controlRGB(TRUE,FALSE,FALSE);
      break;
    case BLUE:
      controlRGB(FALSE,FALSE,TRUE);
      break;
    case GREEN:
      controlRGB(FALSE,TRUE,FALSE);
      break;
    case ORANGE:
      controlRGB(TRUE,TRUE,FALSE);
      break;
    case PURPLE:
      controlRGB(TRUE,FALSE,TRUE);
      break;
    case WHITE:
      controlRGB(TRUE,TRUE,TRUE);
      break;
    case BLACK:
      controlRGB(FALSE,FALSE,FALSE);
      break;
    default:
      controlRGB(FALSE,FALSE,FALSE);
  }
}
//Write the IO lines that control the RGB
void controlRGB (bool red, bool green, bool blue){
  digitalWrite(led_r,red);
  digitalWrite(led_g,green);
  digitalWrite(led_b,blue);
}

//Check if any of the buttons that trigger the an alert have been pressed
bool checkAlertButtons (){
  return digitalRead(manual_btn) || digitalRead(d_btn);
}

// Lets you remotely check the battery status by calling the function "batt"
// Triggers a publish with the info (so subscribe or watch the dashboard)
// and also returns a '1' if there's >10% battery left and a '0' if below
int batteryStatus(String command){
    // Publish the battery voltage and percentage of battery remaining
    // if you want to be really efficient, just report one of these
    // the String::format("%f.2") part gives us a string to publish,
    // but with only 2 decimal points to save space
    Particle.publish("B",
          "v:" + String::format("%.2f",fuel.getVCell()) +
          ",c:" + String::format("%.2f",fuel.getSoC()),
          60, PRIVATE
    );
    // if there's more than 10% of the battery left, then return 1
    if (fuel.getSoC()>10){ return 1;}
    // if you're running out of battery, return 0
    else { return 0;}
}
