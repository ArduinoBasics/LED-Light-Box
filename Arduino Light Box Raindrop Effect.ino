/* ======================================================================================
          Project: Arduino LED Light Box - Raindrop sketch
           Author: Scott C
          Created: 18th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a randomised raindrop effect on a strand of 12mm Diffused 
      			   Flat Digital RGB LED Pixels (25 LEDs).  This project makes use of the 
      			   FastLED library v3.0.3 (http://fastled.io/). 
     			  
     			  
     			  You can get these LEDs from OpenLab Australia: 
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
byte brightness[NUM_LEDS];      // The brightness of each LED is controlled individually through this array
byte hue[NUM_LEDS];             // The hue of each LED is controlled individually through this array
struct CRGB leds[NUM_LEDS];     // This is the array of LEDs    
byte startVal[NUM_LEDS];		// The startVal array helps to randomise the LED pattern
byte minHue =0;                 // Keeps the hue within a certain range - this is the lower limit
byte maxHue =30;                // Keeps the hue within a certain range - this is upper limit
byte maxBrightness = 200;       // Limits the brightness of the LEDs
 
    
/*===================================================================
  setup(): The following code is only run once
====================================================================*/

void setup() {
  //If you have a different LED strip, you may need to modify the next line
  //For this LED strand, you need to define both the data and the clock connections
  LEDS.addLeds<LED_TYPE, DATA, CLOCK, RGB>(leds, NUM_LEDS); 
  
  //Clear the LED strip
  FastLED.clear();
  
  //This helps to create a truly random pattern each time
  random16_add_entropy(random());

  //Initialise the startVal and hue arrays
  for(int i = 0; i<NUM_LEDS; i++){
    startVal[i] = random8();
    hue[i] = random(minHue, maxHue);
  }
}


/*===================================================================
  loop(): The following code runs indefinitely
====================================================================*/

void loop() {
	
  //Cycle through each LED
  for(int i = 0; i<NUM_LEDS; i++){
    
    //The brightness of each LED is based on the startValue, 
    //and has a sinusoidal pattern
    startVal[i]++;
    brightness[i] = sin8(startVal[i]);
    
    //Set the hue and brightness of each LED
    leds[i] = CHSV(hue[i], 255, map(brightness[i],0,255,0,maxBrightness));
    
    //This helps to further randomise the pattern
    if(random(1000)<100){
      startVal[i] = startVal[i]+2;
    }
    
    //The hue will only change when the LED is "off"
    if(brightness[i] <3){
      //Randomise the hue for the next on off cycle
      hue[i] = random(minHue, maxHue); 
      
      //Each time an LED turns off, the hue "range" is incremented.
      //This allows the LEDs to transition through each colour of the rainbow
      minHue++;
      maxHue++;
    }
  }
  
  FastLED.show();   // Show the next frame of the LED pattern
  delay(10);        // Slow down the animation slightly
} 