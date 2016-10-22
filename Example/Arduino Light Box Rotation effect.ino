/* ======================================================================================
          Project: Arduino LED Rotation effect sketch
           Author: Scott C
          Created: 19th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a rotation effect on a strand of 12mm Diffused 
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
byte counter=0;					// counter is used to control the brightness and colour of LEDs
/*int groupA[] = {0, 1, 2, 6, 7, 8, 12, 13, 15, 16, 18};
int groupB[] = {1, 2, 3, 7, 8, 9, 13, 16, 18};
int groupC[] = {2, 3, 4, 8, 9, 10, 13, 14, 16, 17, 18};
int groupD[] = {3, 4, 5, 9,10, 11, 14, 17, 18};
int groupE[] = {4, 5, 6, 10, 11, 0, 14, 15, 12, 17, 18};
int groupF[] = {5, 6, 7, 11, 0, 1, 12, 15, 18};
*/
int groupA[] = {0, 12, 18, 15, 6};
int groupB[] = {1, 18, 7, 22};
int groupC[] = {2, 13, 18, 16, 8, 19, 23};
int groupD[] = {3, 18,9};
int groupE[] = {4, 14, 18, 17, 10, 20, 24};
int groupF[] = {5, 18, 11, 21};
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
  counter++;
  
 
  FastLED.clear();
  switch (counter){
   case 1:
   		hue=hue+50;
   		showLEDS(groupA, 5);
   	break;
   case 2:
   		showLEDS(groupB, 4);
   	break;
   case 3:
   		showLEDS(groupC, 7);
   	break;
   case 4:
   		showLEDS(groupD, 3);
   	break;
   case 5:
   		showLEDS(groupE, 7);
   	break;
   case 6:
   		showLEDS(groupF, 4);
   		counter=0;
   	break;
  }
  FastLED.show();							// Show the new colour and brightness
  FastLED.delay(100);

} 

void showLEDS(int myArray[], int arraySize){
	for (int i=0; i<arraySize; i++){
		leds[myArray[i]] = CHSV(hue, 255, 128);
	}
}
