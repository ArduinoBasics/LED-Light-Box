/* ======================================================================================
          Project: Arduino LED Lightning effect sketch
           Author: Scott C
          Created: 19th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a Lightning effect on a strand of 12mm Diffused 
     			   Flat Digital RGB LED Pixels (25 LEDs) arranged in a circular/spiral pattern.  
     			   This project makes use of the FastLED library (http://fastled.io/). 
     			  
     			  
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
byte counter=0;					

int spark = 0;
int sparkCheck = 0;

byte hue = 0;

CRGB leds[NUM_LEDS];            // the array of LEDs                                

CRGB tempLED;


//==========================================================================
void setup() {
  //If you have a different LED strip, you may need to modify the next line
  //For this LED strand, you need to define both the data and the clock connections
  LEDS.addLeds<LED_TYPE, DATA, CLOCK, RGB>(leds, NUM_LEDS); 
  FastLED.clear();
}



//==========================================================================
void loop() {
	hue++;
	delay(30);
	int x = random8(25);
	leds[x] = CHSV(hue, 255, random(80,100));
	FastLED.show();
	delay(80);
		
	for(int i=0; i<NUM_LEDS; i++){
		leds[i].fadeToBlackBy(1);
	}

	if(random8(100)<1){
		for(int i=0; i<25; i++){
			int z = random(24);
			tempLED = leds[z];
			if(random(100)<50){
				leds[z] = CHSV(hue, 0, 250);
				FastLED.show();
				delay(50);
				leds[z]=tempLED;
			}
			
		}
	}
	
} 

