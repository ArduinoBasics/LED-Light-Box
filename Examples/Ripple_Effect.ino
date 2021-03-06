/* ======================================================================================
          Project: Arduino LED Ripple effect sketch
           Author: Scott C
          Created: 19th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a ripple effect on a strand of 12mm Diffused 
     			   Flat Digital RGB LED Pixels (25 LEDs) arranged in a circular/spiral pattern.  
     			   This project makes use of the FastLED library v3.0.3 (http://fastled.io/). 
     			  
     			  
     			  LEDs from OpenLab Australia: 
     			  http://openlab.com.au/shop/12mm-diffused-flat-digital-rgb-led-pixels-strand-of-25/
     			  
     			  LED Pixel Strip        Arduino UNO
     			  ==================================
     			  Red Wire  = VCC   ==>                  (5V from external power supply)
     			  Blue Wire = GND   ==> GND
     			Yellow Wire = Data  ==> Digital Pin 2
     			 Green Wire = Clock ==> Digital Pin 3
     			 
     			 
========================================================================================= */

#include "FastLED.h"           	// This sketch uses the FastLED library                                    
 
#define DATA 2      		   	// Data connected to Digital Pin 2 on the Arduino                                     
#define CLOCK 3         	   	// Clock connected to Digital Pin 3 on the Arduino                             
#define LED_TYPE WS2801        	// This LED strip uses the WS2801 chipset.                                   
#define NUM_LEDS 25            	// There are 25 LEDs on this strand

//Global Variables
byte counter=0;					// counter is used to control the brightness and colour of LEDs
byte brightnessA = 0;            // brightness of the leds
byte brightnessB = 0;
byte brightnessC = 0;
byte brightnessD = 0;
byte hue=0;						// hue of LEDs
byte hueBias=0;

CRGB leds[NUM_LEDS];            // the array of LEDs                                




//==========================================================================
void setup() {
  //If you have a different LED strip, you may need to modify the next line
  //For this LED strand, you need to define both the data and the clock connections
  LEDS.addLeds<LED_TYPE, DATA, CLOCK, RGB>(leds, NUM_LEDS); 
  FastLED.clear();
}



//==========================================================================
void loop() {
  delay(20);     //This slows the breathing transition slightly
  counter--;
  if(counter==0){
  	hueBias=hueBias+2;
  }
  
  brightnessA = sin8(counter);   			//This function provides a nice brightness transition
  brightnessB = sin8(counter+20);
  brightnessC = sin8(counter+40);
  brightnessD = sin8(counter+60);
  
  hue = brightnessA+hueBias;
  leds[18] = CHSV(hue , 255, brightnessA);
  
  hue = brightnessB+hueBias;
  for (int i=12; i<18; i++){
    leds[i] = CHSV(hue , 255, brightnessB);  // Set the colour and brightness of the LEDs
  }
  
  hue = brightnessC+hueBias;
  for (int i=0; i<12; i++){
    leds[i] = CHSV(hue , 255, brightnessC);  // Set the colour and brightness of the LEDs
  }
  
  hue = brightnessD+hueBias;
  for (int i=19; i<25; i++){
    leds[i] = CHSV(hue , 255, brightnessD);  // Set the colour and brightness of the LEDs
  }
  
  FastLED.show();							// Show the new colour and brightness
} 
