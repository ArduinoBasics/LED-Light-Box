/* ======================================================================================
          Project: Arduino LED Sweep effect sketch
           Author: Scott C
          Created: 19th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a sweep effect on a strand of 12mm Diffused 
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
int groupA[] = {24,23,8,9,10,11,17,16,7,22,6,15,18,12,0,1,13,14,5,21,4,3,2,19,20};

byte hue = 0;
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
	showLEDS(groupA, 25);
} 

void showLEDS(int myArray[], int arraySize){
	for (int i=0; i<arraySize; i++){
		counter++;
		hue = sin8(counter);
		leds[myArray[i]] = CHSV(hue, 255, 128);
		FastLED.show();
		delay(30);
		
	}
}
