
#ifndef print2digits_h
#include "Arduino.h"

#include <Wire.h>
#include <Time.h> // included in setting time for RTC and displaying it
#include <DS1307RTC.h> // includes RTC functions
#include <LiquidCrystal_I2C.h> // includes LCD functions
#include<EEPROM.h>
#include <RTClib.h>
#include <Servo.h> // includes servo functions


#define buttonPin0 10 // defines buttons as pins in Arduino
#define buttonPin1 11
#define buttonPin2 12

int buttonState0 = 0; // "Set Alarm" button defined as integer
int old_buttonState0 = 0; // previous state of buttonState0
int state = 0; //defines state as integer
int count1 = 0; // counts button presses for hour button
int count2 = 0; // counts button presses for minute button
int buttonState1 = 0; // defines buttonState1 as integer
int buttonState2 = 0; // defines buttonState2 as integer


LiquidCrystal_I2C lcd(0x27,16,2); // sets LCD parameters in 2x16

Servo servo1;     // defines servo1 using Arduino function for servos
Servo servo2;     // defines servo2 using Arduino function for servos
int pos1 = 95;    // defines the 95 degree position on the servo as the variable pos1
int pos2 = 0;     // defines the 0 degree position on the servo as the variable pos2

void print2digits(int number) {   // void made to create double digit numbers out of all numbers
  if (number >= 0 && number < 10) { // if the number is a single digit, put a "0 before it            *in order to keep all numbers as double digits for uniformity*
    lcd.print('0'); // prints a 0 before the number
  }
  lcd.print(number); // prints the number after the 0
}
#endif
