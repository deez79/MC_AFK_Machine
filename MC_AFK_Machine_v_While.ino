//**************************************************************************************
//
//  TITLE:   Minecraft Realm AFK Machine
//  AUTHOR:  derek.schulman@gmail.com
//  DATE:    12/14/2015
//
//**************************************************************************************



//**************************************************************************************
// Info
//**************************************************************************************
/*
  This project is to create a button for running minecraft realm AFK.
 */

//***************************************************************************************
// Schematic
//***************************************************************************************
/*

Teensy 3.2
____________
|          |
|          |
|          |
|     13   | ----------------------- ledPin --------------------------------------------
|          |
|     17   | ----------------------- clickLED -----------------------------------------
|          |
|     19   | ----------------------- activeLED ----------------------------------------
|          |
|     15   | ----------------------- buttonPin  -------------------------------------
|          |
|          |
|     5v   | -------------------------------------------
|     gnd  | -------------------------------------------
|          |
|          |
------------

*/

//***************************************************************************************
// Main Sketch
//***************************************************************************************

#include <Mouse.h>

//*****************************************
// Constants
//*****************************************
  const int buttonPin = 15;      // the number of the pushbutton pin Default 2
  const int ledPin =  13;				// the number of the LED pin.  Used to show that board is connected.
  const int activeLED = 19;      // the number of the LED pin used to show the machine is active
  const int clickLED = 17;       // the number of the click indicator LED

//*****************************************
// Variables
//*****************************************
  int buttonState = 0;        // variable for reading the pushbutton status 0 default is not clicked
  int eventTime = 10;					// Time to wait after button click before clicking again. (add 3 seconds for application delay)
											        // Note each number passed to flash represents 1 second.

//*****************************************
// Functions
//*****************************************
void appOff(){
    digitalWrite(activeLED, LOW);      	// turn LED OFF
    digitalWrite(clickLED, LOW);        // turn LED OFF
    Serial.println("Machine OFF");
}    // end appOff()

void appOn(){
    digitalWrite(activeLED, HIGH);        // turn LED ON
    Serial.println("Machine ON");
    clicky();                      // run clicky function
}    // end appOff()

void clicky(){
    // click activate Makey, Makey needs to be grounded to activate: If LED is connected, LED turns off
      Mouse.click(MOUSE_RIGHT);  //Used to actual act as click on mouse.
      Serial.println("Mouse Click");
      blink(clickLED);
}  	//end makeyClick()

void blink(int PIN){
   digitalWrite(PIN, HIGH);
   delay(500);
   digitalWrite(PIN, LOW);
}	// end blink()

void flash(int count){
  for(int p=0; p<count; p++){
    blink(ledPin);
    delay(500);
  } //end for
}   //end flash()

void workingIfLoop() {
    buttonState = digitalRead(buttonPin);   // read the state of the pushbutton value:
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH
  if (buttonState == HIGH) {            //button IS clicked
    appOn();
    delay(eventTime * 1000);

  }
  else {  //button NOT clicked
    appOff();
  }

}

//*****************************************
// Setup
//*****************************************
void setup() {



  // initialize pins as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(activeLED, OUTPUT);
  pinMode(clickLED, OUTPUT);


  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // turn on ledPin to show that machine is connected:
  digitalWrite(ledPin, HIGH);

  Mouse.begin();  // initiate the Mouse library
  Serial.begin(9600); //initiate serial output



}

//*****************************************
// Loop
//*****************************************
void loop(){
  buttonState = digitalRead(buttonPin);   // read the state of the pushbutton value:
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH
  while (buttonState == HIGH) {            //button IS clicked
    appOn();
    for(int i=0; i<(eventTime*2); i++){
      buttonState = digitalRead(buttonPin);   // read the state of the pushbutton value:
      if(buttonState == LOW){
        break;
      }
      else{
        delay(500);
        Serial.println(i);
      }

    }   //end for loop
  }     //end while loop
  if (buttonState == LOW) {  //button NOT clicked
    appOff();
  }

}	//end Loop()
