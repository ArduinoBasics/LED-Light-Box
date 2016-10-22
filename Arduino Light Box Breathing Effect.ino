/* ======================================================================================
          Project: Arduino LED Light Box - Breathing effect sketch
           Author: Scott C
          Created: 18th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a breathing effect on a strand of 12mm Diffused 
     			  Flat Digital RGB LED Pixels (25 LEDs).  This project makes use of the 
     			  FastLED library v3.0.3 (http://fastled.io/). 
     			  
     			  
     			  You can get the LEDs from OpenLab Australia: 
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
byte brightness = 0;			// brightness of LEDs
byte hue=0;						// hue of LEDs
byte minHue = 0;                // Control the hue range (this is the lower limit)
byte maxHue = 40;               // Control the hue range (this is the upper limit)

CRGB leds[NUM_LEDS];            // the array of LEDs                                

/*====================================================================
  setup(): will run only once
=====================================================================*/

void setup() {
  //If you have a different LED strip, you may need to modify the next line
  //For this LED strand, you need to define both the data and the clock connections
  LEDS.addLeds<LED_TYPE, DATA, CLOCK, RGB>(leds, NUM_LEDS); 
  FastLED.clear();
}


/*====================================================================
  loop(): will run indefinitely
=====================================================================*/

void loop() {
  //This slows the breathing transition slightly
  delay(10);     
  
  //This function provides a nice brightness transition
  counter++;
  brightness = sin8(counter);   			
  
  //Delay at extremities for extra effect
  if(brightness > 254){
  	delay(500);							
  } else if (brightness <2 ){
  	delay(500);	
  
  //Change the Hue slightly with every "breath"	
  	minHue=minHue+10;						
  	maxHue=maxHue+10;
  }
  
  //Hue changes with brightness, but the hue limited by the minHue and maxHue variables.
  hue = map(brightness, 0, 255, minHue, maxHue);  
  
  //Set the  hue and brightness of each LED
  for (int i=0; i<NUM_LEDS; i++){
    leds[i] = CHSV(hue , 255, brightness);  // Set the colour and brightness of the LEDs
  }
  
  //Show the next frame of the LED animation
  FastLED.show();						
} 
