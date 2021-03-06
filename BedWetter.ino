////////////////////////////////////
// "The Bed Wetter" by Zac Primus //
////////////////////////////////////
#include "print2digits.h" // includes all the functions and definitions found in the header

void setup() 
{
  lcd.init(); // initiates the LCD
  lcd.backlight(); // turns on the backlight of the LCD
 
  pinMode(buttonPin0, INPUT);
  pinMode(buttonPin1, INPUT);  //buttons are made as Inputs
  pinMode(buttonPin2, INPUT);

  digitalWrite(buttonPin0, HIGH);
  digitalWrite(buttonPin1, HIGH);  //When the buttons are pressed, have them do something
  digitalWrite(buttonPin2, HIGH);

  servo1.attach(9); // establishes servo as output
  servo2.attach(8); // establishes servo as output
  servo1.write(pos1); // positions servo in starting position
  servo2.write(pos2); // positions servo in starting position
  

  lcd.backlight();  //Backlight ON if under program control
  lcd.setCursor(0,0);  //Line 1 on the LCD
  lcd.print("The Bed Wetter");  //Read name of the project when it turns on
  lcd.setCursor(2,1);  //Line 2 on the LCD
  lcd.print("by Zac Primus"); //Read name of the creator when it turns on
  delay(4000);  //Show for 4 seconds
   
  servo1.write(pos1); // positions servo in starting position
  servo2.write(pos2); // positions servo in starting position  
 }

void loop() 
{ 
  buttonState0 = digitalRead(buttonPin0);
  buttonState1 = digitalRead(buttonPin1);  // the action of reading the buttons placed into variables
  buttonState2 = digitalRead(buttonPin2);
  
  tmElements_t tm;  // Print our characters on the LCD
  lcd.backlight();  //Backlight ON if under program control

  if (buttonState0 == LOW && old_buttonState0 == HIGH) //if button 1 is pressed (set alarm button)
  { 
    state = 1-state; // the previous state of the button
    delay(10);
    
    lcd.setCursor(0,0); // Start at character 0 on line 0
    lcd.print("   SET ALARM   "); // 1st line says SET ALARM
    lcd.setCursor(0,1); // Start at character 1 on line 1
    lcd.print("                ");  // 2nd line goes blank

    delay(1400); //Show for 1.4 seconds
  }

  old_buttonState0 = buttonState0; // the previous state of the button uses the same pin

  if (state==1) // show the "ALARM TIME" until the set alarm button is pressed again
  {  
    lcd.setCursor(0,0); 
    lcd.print("   ALARM TIME   "); 
    lcd.setCursor(4,1); 
    lcd.print("HRS");  
    lcd.setCursor(11,1); 
    lcd.print("MIN"); 
  } 
  
  else if (RTC.read(tm)) // if "SET ALARM" button isn't pressed then read time and date
  {
    lcd.setCursor(0,0); //Start at character 0 on line 0
    lcd.print("TIME :"); //display the word "TIME"
    print2digits(tm.Hour); //display the hour in 2 digits
    lcd.print(':');
    print2digits(tm.Minute); //display the minutes in 2 digits
    lcd.print(':');
    print2digits(tm.Second); //display the seconds in 2 digits
    
    lcd.setCursor(0,1); //Start at character 0 on line 1
    lcd.print("DATE :");  //display the word "DATE"
    print2digits(tm.Month); //display the month in 2 digits
    lcd.print('/');
    print2digits(tm.Day); //display the day in 2 digits
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year)); //display the year in 2 digits
  }
  
  if (buttonState1 == LOW && state==1) //if button 2 is pressed (hour button)
  { 
    lcd.setCursor(1,1); //display here
    print2digits(count1); //keep track of the counts for the hour button in 2 digits
    count1++;  //count by 1
    delay(250);  // time between presses
    
    if (count1 >=24) // limit of 24 hours in a day
    { 
      count1 = 0;
    }
  }

  if (buttonState2 == LOW && state==1) //if button 3 is pressed (minutes button)
  { 
    lcd.setCursor(8,1); // display here
    print2digits(count2); //keep track of the counts for the minute button in 2 digits
    count2++;  // count by 1
    delay(250);  // time between presses
    
    if (count2 >=60) // limit of 60 minutes in an hour
    { 
      count2 = 0;
    }
  }
                    
  // if the numbers on the SET ALARM match the time, then begin the servo rotation                                                       
                                                            
  if (count1-1 == tm.Hour && count2-1 == tm.Minute && tm.Second%2 == 0) // if the counts on the buttons match the alarm time and if the seconds are even then rotate
  { 
    servo1.write(pos1+50); // rotate servo 1 50 degrees 
    servo2.write(pos2+40); // rotate servo 2 40 degrees  *different degrees because of equipment and human error in placement of servos and functionality of servos*
  } 
  
  else // if the time isnt the alarm time and/or the seconds are odd then keep servos at this position
  {                      
    servo1.write(pos1); // starting position for servo 1
    servo2.write(pos2); // starting position for servo 2
  }
} 

