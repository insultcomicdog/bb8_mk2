// =======================================================================================
//  Bruton's Drive Remote:SHADOW :  Small Handheld Arduino Droid Operating Wand for BB8
// =======================================================================================
//                          Last Revised Date: 07/12/2017
//                      Written By: James VanDusen (jlvandusen)
//                            Inspired by KnightShade
//     learn more at http://jimmyzsbb8.blogspot.com or http://jimmyzsr2.blogspot.com
// =======================================================================================
//
//         This program is free software: you can redistribute it and/or modify it .
//         This program is distributed in the hope that it will be useful,
//         but WITHOUT ANY WARRANTY; without even the implied warranty of
//         MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// =======================================================================================
//   Note: You will need a Arduino UNO to run this sketch,
//
//
// =======================================================================================

// =======================================================================================
//                          Debug Code settings
// =======================================================================================

// Make sure you set the Primary Controller (if you set the mac address - 
// you will no longer need to pair the controller)
// EepromEX: https://github.com/thijse/Arduino-EEPROMEx
// USB Shield 2.0 Library: https://github.com/felis/USB_Host_Shield_2.0
// SHADOW Reference information: https://github.com/ti9327/SHADOW
//
//
// =======================================================================================
// =======================================================================================
//#define ADKmega     // Allows use on Mega ADK USB embedded devices
#define UNO         // Allows use of SHADOW controllers on UNO boards
//#define SFX_ENABLE
//#define DEBUG       // enables debug mode displaying any errors etc.
//#define DEBUG_NAV   // Displays raw button presses and commands sent to PS3 Nav controllers
//#define DOMECOMS    // Allows BT to/from dome using the same USB/BT Controller


#ifdef ADKmega
#include <adk.h>
#include <USB.h>
#endif
#include <usbhub.h>
#include <PS3BT.h>    // https://github.com/felis/USB_Host_Shield_2.0
#include <avr/wdt.h>
#include <SPP.h>
#ifdef dobogusinclude // Satisfy the IDE, which needs to see the include statment in the ino too.
  #include <spi4teensy3.h>
  #include <SPI.h>
#endif

#include "Arduino.h"

#ifdef SFX_SERIAL
#include "Adafruit_Soundboard.h"  // allow serial UAT modes communications.
#endif
// Connect UG to GND (to start the sound board in Uart mode)
// Connect Arduino RX to the TX sound board
// Connect Arduino TX to the RX sound board
// Connect RST to another microcontroller pin, when toggled low, it will reset the sound board into a known state
// If you want to know when sound is being played, the ACT pin is LOW when audio is playing - this output also controls the red ACT LED
// https://learn.adafruit.com/adafruit-audio-fx-sound-board
// https://cdn-learn.adafruit.com/downloads/pdf/adafruit-audio-fx-sound-board.pdf





int state = 0;
int stateLast = 0;

long currentMillis;
long previousMillis;
long interval = 80;
long previousMillisScreen;
unsigned long bodyCalibrationMillis;

float bodyBatt = 0.0;
float domeBatt = 0.0;
float remoteBatt = 0.0;
int bodyStatus;
int driveSpeed = 55;
int lastDriveSpeed = 55;
int lastBodyStatus = 0;
int calibrationMarker;

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];   

boolean newData = false;

long but8Millis;
int but8State;


// define USB and PS3BT information for Arduino
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class to support 2 controllers */
//SPP SerialBT(&Btd); // This will set the name to the defaults: "Arduino" and the pin to "0000"
//SPP SerialBTBT(&Btd,"Lauszus's Arduino","0000"); // You can also set the name and pin like so
SPP SerialBT(&Btd,"BB8","0000"); // Create a BT Serial device(defaults: "Arduino" and the pin to "0000" if not set)

PS3BT *PS3Nav = new PS3BT(&Btd);
PS3BT *PS3Nav2 = new PS3BT(&Btd);

#ifdef DOMECOMS

#endif



String PS3MoveNavigatonPrimaryMAC = "00:06:F5:64:60:3E"; //If using multiple controlers, designate a primary
boolean isPS3NavigatonInitialized = false;
boolean isSecondaryPS3NavigatonInitialized = false;
boolean isStickEnabled = true;

boolean WaitingforReconnect = false;
boolean WaitingforReconnectDome = false;

boolean mainControllerConnected = false;
boolean domeControllerConnected = false;

#ifdef SFX_SERIAL

/* https://learn.adafruit.com/adafruit-audio-fx-sound-board
/* https://cdn-learn.adafruit.com/downloads/pdf/adafruit-audio-fx-sound-board.pdf */
//SoftwareSerial sfx = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, SFX_RST);
#endif

//Used for PS3 Fault Detection
uint32_t msgLagTime = 0;
uint32_t lastMsgTime = 0;
uint32_t currentTime = 0;
uint32_t lastLoopTime = 0;
int badPS3Data = 0;

bool firstMessage = true;
String output = ""; // We will store the data in this string

#ifdef SFX_SERIAL
String Sound[] = 
{"T00NEXT0OGG",
"T00NEXT1OGG",
"T00NEXT2OGG",
"T00NEXT3OGG",
"T00NEXT4OGG",
"T00NEXT5OGG",
"T00NEXT6OGG",
"T00NEXT7OGG",
"T00NEXT8OGG",
"T00NEXT9OGG",
"T01NEXT0OGG",
"T01NEXT1OGG",
"T01NEXT2OGG",
"T01NEXT3OGG",
"T01NEXT4OGG",
"T01NEXT5OGG",
"T01NEXT6OGG",
"T01NEXT7OGG",
"T01NEXT8OGG",
"T01NEXT9OGG",
"T02NEXT0OGG",
"T02NEXT1OGG",
"T02NEXT2OGG",
"T02NEXT3OGG",
"T02NEXT4OGG",
"T02NEXT5OGG",
"T02NEXT6OGG",
"T02NEXT7OGG",
"T02NEXT8OGG",
"T02NEXT9OGG",
"T03NEXT0OGG",
"T03NEXT1OGG",
"T03NEXT2OGG",
"T03NEXT3OGG",
"T03NEXT4OGG",
"T03NEXT5OGG",
"T03NEXT6OGG",
"T03NEXT7OGG",
"T03NEXT8OGG",
"T03NEXT9OGG",
"T04NEXT0OGG",
"T04NEXT1OGG",
"T04NEXT2OGG",
"T04NEXT3OGG",
"T04NEXT4OGG",
"T04NEXT5OGG",
"T04NEXT6OGG",
"T04NEXT7OGG",
"T04NEXT8OGG",
"T04NEXT9OGG",
"T05NEXT0OGG",
"T05NEXT1OGG",
"T05NEXT2OGG",
"T05NEXT3OGG",
"T05NEXT4OGG",
"T05NEXT5OGG"};
#endif

#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t ch1;
  int16_t ch2;
  int16_t ch3;
  int16_t ch4;
  int16_t ch5;
  int16_t ch6;
  int16_t but1;
  int16_t but2;
  int16_t but3;
  int16_t but4;
  int16_t but5;
  int16_t but6;
  
};

SEND_DATA_STRUCTURE mydata;

void setup(){
  Serial.begin(115200);
  ET.begin(details(mydata), &Serial);

  #ifdef SFX_SERIAL
  Serial1.begin(9600);
  #endif

  #ifndef UNO
  Serial2.begin(115200);
  #endif
  
  #if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  #endif
  if (Usb.Init() == -1) {
    #ifdef DEBUG
    Serial.print(F("OSC did not start - check compiler settings\n"));
    #endif
    while (1); //halt
  }
  #ifdef DEBUG
  Serial.print(F("\r\nSHADOW Bluetooth Library Started\n"));
  #endif
  //Setup for PS3 / PS4 NAV Controllers
  PS3Nav->attachOnInit(onInitPS3); // onInit() is called upon a new connection - you can call the function whatever you like
  PS3Nav2->attachOnInit(onInitPS3Nav2);



#ifdef SFX_SERIAL
  /* =========================================================================
  Change the FX Sound board into UAT mode for easier control
  * ========================================================================= */
  /* =========================================================================
  /* https://learn.adafruit.com/adafruit-audio-fx-sound-board
  /* https://cdn-learn.adafruit.com/downloads/pdf/adafruit-audio-fx-sound-board.pdf
  Connect UG to GND (to start the sound board in Uart mode) 
  Connect RX to the data-output pin from the microcontroller into the sound board 
  Connect TX to the data-output pin to the microcontroller from the sound board 
  Connect RST to another microcontroller pin, when toggled low, 
  it will reset the sound board into a known state
  If you want to know when sound is being played, 
  the ACT pin is LOW when audio is playing - this output also controls the red ACT LED
  * ========================================================================= */
  
  if (!sfx.reset()) {
    #ifdef DEBUG
    Serial.println("SFX Module Not found");
    #endif
    while (1);
  }
  else {
    #ifdef DEBUG
    Serial.println("SFX board found and configured in Uart mode");
    #endif
  }
#endif

}




void loop(){
//  readMain();           // Recieve calls from Main body - used currently for reseting the arduino
  if (SerialBT.connected) {
    if (firstMessage) {
      firstMessage = false;
      SerialBT.println(F("Hello from BB8")); // Send welcome message
    }
    if (Serial.available())
      SerialBT.write(Serial.read());
    if (SerialBT.available())
      Serial.write(SerialBT.read());
  }
  else
    firstMessage = true;
  Usb.Task();
  if ( !readUSB() )
    {
      //We have a fault condition that we want to ensure that we do NOT process any controller data!!!
      return;
    }
  GetMoveController();
  getMoveButtons();
  senddata();
    #ifdef DEBUG
    if (output != "") {
          String string = "PS3 Controller" + output;
          Serial.println(string);
          if (SerialBT.connected)
            SerialBT.println(string);
    }
    #endif

}






