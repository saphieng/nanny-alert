/*
 * Project nanny-alert
 * Description: Device that can be used to alert for help
 * Author: Cameron Owen
 * Date: 29/12/18
 */
#include "application.h"
SYSTEM_MODE(SEMI_AUTOMATIC);
// The Photon has 9 PWM pins: D0, D1, D2, D3, A4, A5, A7, RX and TX.
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

//Remote Reciever IO
int a_btn = D0;
int b_btn = D1;
int c_btn = D2;
int d_btn = D3;
int any_btn = D4;
int manual_btn = A0;
long pressTime = 0;

//Global variables
bool connectionState = FALSE;
bool prevAlertState = FALSE;
bool  alertTriggered = FALSE;

// setup() runs once, when the device is first turned on.
void setup() {
  //external RGB
  pinMode(led_r,OUTPUT);
  pinMode(led_g,OUTPUT);
  pinMode(led_b,OUTPUT);
  //input setups
  pinMode(manual_btn, INPUT_PULLDOWN);
  pinMode(a_btn, INPUT_PULLDOWN);
  pinMode(b_btn, INPUT_PULLDOWN);
  pinMode(c_btn, INPUT_PULLDOWN);
  pinMode(d_btn, INPUT_PULLDOWN);
  //pinMode(any_btn, INPUT);
  setRGBColour(ORANGE);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  //Check we still have connection
  if (!connectionState && Particle.connected()){
    setRGBColour(GREEN);
  }
  if (Particle.connected() == false) {
    setRGBColour(ORANGE);
    Particle.connect();
    //setRGBColour(GREEN);
  }

  //Monitor the button state
  alertTriggered = checkAlertButtons();
  if (alertTriggered){
    pressTime = millis();
    while(alertTriggered && ((millis()-pressTime) <= 3000)){
      alertTriggered = checkAlertButtons();
    }
    if (millis()-pressTime > 3000){
      //If the D button is being held, fire a test message
      if(digitalRead(d_btn)){
        testAlert();
      }
      else{
        resetAlarm();
      }
    }
    else{
      sendForHelp();
    }
  }
  connectionState = Particle.connected();
  prevAlertState = alertTriggered;
  delay(100);
}

//IFTTT functions for alerting
void sendForHelp(){
    setRGBColour(RED);
    tone(speakerPin,1000,1000);
    Particle.publish("SendForHelp");
    delay(1000);
}

void resetAlarm(){
    setRGBColour(BLUE);
    noTone(speakerPin);
    Particle.publish("FalseAlarm");
    delay(1000);
    setRGBColour(GREEN);
}

void testAlert(){
    setRGBColour(ORANGE);
    tone(speakerPin,1000,1000);
    Particle.publish("TestAlert");
    delay(1000);
    setRGBColour(GREEN);
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
      controlRGB(FALSE,TRUE,TRUE);
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
  return digitalRead(manual_btn) || digitalRead(a_btn)
          || digitalRead(b_btn) || digitalRead(c_btn) || digitalRead(d_btn);
}
