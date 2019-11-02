/*

Code by: 
M.Hashir

This is a code for password protected digital lock

Hardware:
- Arduino
- 16x2 Character LCD
- 16 Male to female wires
- 1 pot
- 1 4x4 keypad
- 8 male to male wires

 Connections:
 
 LCD and Arduino
•	Connect pin 1 of LCD to GND of Arduino board.
•	Connect pin 2 of LCD to 5V of Arduino board.
•	Connect pin 3 of LCD to centre leg of pot. Connect one of the remaining legs of pot (potentiometer) to GND of Arduino and the third leg of pot to 5V of Arduino board.
•	Connect pin 4 of LCD to pin 12 of Arduino board.
•	Connect pin 5 of LCD to GND of Arduino board.
•	Connect pin 6 of LCD to pin 11of Arduino board.
•	Connect pin 11 of LCD to pin 5 of Arduino board.
•	Connect pin 12 of LCD to pin 4 of Arduino board.
•	Connect pin 13 of LCD to pin 3 of Arduino board.
•	Connect pin 14 of LCD to pin 2 of Arduino board.
•	Connect pin 15 of LCD to pin 5V of Arduino board.
•	Connect pin 16 of LCD to pin GND of Arduino.

 Keypad and Arduino
 * When keypad is facing towards you, connect pins of keypad to Arduino in the following sequence
    A0, A1, A2, A3, 6, 7, 8, 9

Note:
pin A5 and pin 11 of Arduino can be used as GND for this code.
 */


#define namount 48                  //do not edit this line

#include <LiquidCrystal.h>          //library file added
#include <Keypad.h>                 //library file added

int setpassword = 2580;             //THIS IS THE CORRECT PASSWORD

int RS = 12;                        //connect RS of LCD to this pin
int E = 10;                         //connect E of LCD to this pin
int D4 = 5;                        //connect D4 of LCD to this pin
int D5 = 4;                        //connect D5 of LCD to this pin
int D6 = 3;                        //connect D6 of LCD to this pin
int D7 = 2;                        //connect D7 of LCD to this pin

const byte ROWS = 4;                //four rows
const byte COLS = 4;                //three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},             //row 1 of keypad
  {'4', '5', '6', 'B'},             //row 2 of keypad
  {'7', '8', '9', 'C'},             //row 3 of keypad
  {'*', '0', '#', 'D'}              //row 4 of keypad
};

byte rowPins[ROWS] = { A0,A1,A2,A3};     //connect to the row pinouts of the keypad -- left most 4 pins
byte colPins[COLS] = { 6,7,8,9 };    //connect to the column pinouts of the keypad  -- right most 4 pins


LiquidCrystal lcd(RS,E,D4,D5,D6,D7);
//rs, e, d4, d5, d6, d7


int led = 13;                       //we are using pin 13 led to indicate correct password
int password = 0;                   //do not edit this line
int gnd =A5;                        //we have made this pin GND
int gnd2 = 11;                      //we have made this pin GND

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//rs, e, d4, d5, d6, d7
void setup() {
pinMode(led,OUTPUT);                //do not edit this line
pinMode(gnd,OUTPUT);                //do not edit this line
digitalWrite(gnd,LOW);              //do not edit this line
pinMode(gnd2,OUTPUT);               //do not edit this line
digitalWrite(gnd2,LOW);             //do not edit this line

lcd.begin(16,2);                    //16x2 LCD is used

lcd.print("Welcome! To the");       //Prints this msg first on 1st line
lcd.setCursor(0, 1);                //move to character 0 on line 1
lcd.print("Password Machine");      //print this msg
delay(3000);                        //wait
lcd.clear();                        //then clear your LCD

}


void loop() {
  char key = keypad.getKey();       //do not edit
  digitalWrite(led, LOW);           //by default, LED remains LOW
  lcd.setCursor(0, 0);              //move to character 0 on line 0
  lcd.print("Enter Password:- ");   //print this msg
  delay(400);                       //wait
  lcd.clear();                      //then clear lcd
 
 
  if ((key >= '0') && (key <= '9')) {
    password = password * 10 + key - namount;
    Serial.println(password);
  }

  if (password > 9999) {            //the lines following this comment run when password entered is of more than 4 digits
    password = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong passcode");
    delay(3000);
    lcd.clear();
  }

  lcd.setCursor(0, 1);              //do not edit

  if (password == 0) {              //do not edit
    lcd.print("    ");              //do not edit
  }
  else if (password <= 9) {         //do not edit
    lcd.print("*   ");              //do not edit
  }
  else if (password <= 99) {        //do not edit
    lcd.print("**  ");              //do not edit
  }
  else if (password <= 999) {       //do not edit
    lcd.print("*** ");              //do not edit
  }
  else {                            //do not edit
    lcd.print("****");              //do not edit
  }


  if (key == 'A') {                        //A is enter
    if (password == setpassword) {         //following lines run when correct password is entered
      lcd.clear();
      lcd.print("CORRECT");
      lcd.setCursor (0, 1);
      lcd.print("PASSWORD! :)");
digitalWrite(led,HIGH);                    //if password is correct turn on led
delay(10000);                              //wait for  10s
      password = 0;         
digitalWrite(led,LOW);                     //turn OFF led
    
  }                                        //till here
    else {                                 //following lines run when wrong password is entered
    lcd.clear();                           //Donot edit this line
      lcd.setCursor(0, 0);                 //Donot edit this line
      lcd.print("Incorrect");              //Donot edit this line
      lcd.setCursor(0, 1);                 //Donot edit this line
      lcd.print("Password! :(");           //Donot edit this line
      password = 0;                        //Donot edit this line
      delay(1000);                         //Donot edit this line
      lcd.clear();                         //Donot edit this line
    }
  }

}
