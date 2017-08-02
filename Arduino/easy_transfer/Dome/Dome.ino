#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include "SoftwareSerial.h"
#include "MP3FLASH16P.h"
MP3FLASH16P myPlayer;

int audioState = 0;

//PSI,LOGICS AND HOLOJECTOR NEOPIXELS
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(13, PIN, NEO_GRB + NEO_KHZ800);
uint16_t currentPixel = 0;// what pixel are we operating on
uint16_t currentColour = 0;

//RADAR EYE
int value ;
//int radarEyeLEDPin = 5;
int holoLEDPin = 3;
long time=0;
int periode = 2000;

int speakerPin = 0;
int voiceBrightness;

void setup(void)
{
    Serial.begin(115200);
    //Serial.begin(9600);
    Serial.println("BB-8 Head");
   
    myPlayer.init(2);
    
    //pinMode(radarEyeLEDPin, OUTPUT); 
    pinMode(holoLEDPin, OUTPUT); 
    pinMode(speakerPin, INPUT);
    
    // put your setup code here, to run once:
    strip.begin();
    setFrontLogics(255);
    setSideLogics(255);
    strip.show(); // Initialize all pixels to 'off'
    
    
    //play startup sound
    if(!myPlayer.isBusy()){
        myPlayer.playFile(37);
        delay(100);
     }
    
}
 
void loop(void)
{
    if (audioState == 1) {
           playSound();
    }
    
    time = millis();
    value = 128+127*cos(2*PI/periode*time);
    //analogWrite(radarEyeLEDPin, value);           // sets the value (range from 0 to 255)
    analogWrite(holoLEDPin, value);
    
    voiceBrightness = constrain(map(analogRead(speakerPin), 700, 1024, 0, 255), 0, 255);
    //analogWrite(PSILEDPin, voiceBrightness);
    
    setFrontLogics(value);
    setSideLogics(value);
    setPixelColor(0,255,255,51, voiceBrightness);
    strip.show(); 
}


void playSound() {

   if(!myPlayer.isBusy()){
          int randSnd = random(0,19)*2+1;
          myPlayer.playFile(randSnd);
          delay(100);
   }
}

void setFrontLogics(uint16_t brightness) {
  uint16_t i ;

  for (i=1; i<5; i++) {
      setPixelColor(i, 57, 100, 195, brightness);
   }
   
   for (i=5; i<9; i++) {
      setPixelColor(i, 0, 255, 0, brightness);
   }
}

void setSideLogics(uint16_t brightness) {
   uint16_t i ;
   
   for (i=9; i<14; i++) {
      setPixelColor(i, 255, 255, 51, brightness);
   }
  
}

void setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint16_t brightness) {
   strip.setPixelColor(n, (brightness*r/255) , (brightness*g/255), (brightness*b/255));  
}

void rainbowCycleCustom() {
  strip.setPixelColor(currentPixel, Wheel(((currentPixel * 256 / strip.numPixels())+currentColour) & 255, 1 ));
  strip.show();;

  currentColour++;
  if(currentColour >= 256){
    currentColour = 0;
  }
  
  currentPixel++;
  if(currentPixel == strip.numPixels()){
    currentPixel = 0;
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, float opacity) {
  if(WheelPos < 85) {
   return strip.Color((WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color((255 - WheelPos * 3) * opacity, 0, (WheelPos * 3) * opacity);
  } else {
   WheelPos -= 170;
   return strip.Color(0, (WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity);
  }
}
