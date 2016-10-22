/* ======================================================================================
          Project: Arduino LED Spiral effect sketch
           Author: Scott C
          Created: 19th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a Spiral effect on a strand of 12mm Diffused 
     			   Flat Digital RGB LED Pixels (25 LEDs) arranged in a circular/spiral pattern.  
     			   This project makes use of the FastLED library 3.0.3 (http://fastled.io/). 
     			  
     			  
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
int groupA[] = {0,11,10,9,8,7,6,5,4,3,2,1};
int groupB[] = {12,17,16,15,14,13};
int groupC[] = {18,24,23,22,21,20,19};

int spark = 0;
int sparkCheck = 0;

byte hue = 0;
byte hueA;
byte hueB;
byte hueC;

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
	hue = hue + 30;
	hueA = hue;
	showLEDS(groupA, 12);
	hue= hue + 30;
	hueB=hue;
	showLEDS(groupB, 6);
	hue= hue + 30;
	hueC = hue;
	showLEDS(groupC, 7);
	darkfader(groupA, 12, hueA);
	darkfader(groupB, 6, hueB);
	darkfader(groupC, 7, hueC);
	//delay(300);
} 

void showLEDS(int myArray[], int arraySize){
	for (int i=0; i<arraySize; i++){
		leds[myArray[i]] = CHSV(hue, 255, 150);
		FastLED.show();
		delay(80);
	}
}

void darkfader(int myArray[], int arraySize, byte myHue){
	for(int j=0; j<40; j++){
		for(int i=0; i<arraySize; i++){
			spark=random8(j,80);
			sparkCheck=random8(0,40);
			if(spark>sparkCheck){
				leds[myArray[i]].fadeToBlackBy(100);
			} else {
				leds[myArray[i]] = CHSV(myHue, 255, 100-j);
			}
			FastLED.show();
			delay(5);
		}
		
		
	}
}
