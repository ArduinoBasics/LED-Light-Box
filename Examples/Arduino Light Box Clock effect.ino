/* ======================================================================================
          Project: Arduino LED Clock effect sketch
           Author: Scott C
          Created: 19th August 2015
      Arduino IDE: 1.6.4
LED pixel chipset: WS8201
          Website: http://arduinobasics.blogspot.com/p/arduino-basics-projects-page.html
      Description: This sketch will create a clock-like  effect on a strand of 12mm Diffused 
      			   Flat Digital RGB LED Pixels (25 LEDs) arranged in a circular/spiral pattern.  
     			   This project makes use of the FastLED library 3.0.3(http://fastled.io/). 
     			  
     			  
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
byte counterA=0;
byte counterB=0;
byte counterC=0;
byte hue=0;						// hue of LEDs
byte brightness = 255;          // LED brightness
CRGB leds[NUM_LEDS];            // the array of LEDs                                
long timeCounter = 0;
byte sineWaveA = 0;
byte sineWaveB = 0;
byte bias = 0;



//==========================================================================
void setup() {
  //If you have a different LED strip, you may need to modify the next line
  //For this LED strand, you need to define both the data and the clock connections
  LEDS.addLeds<LED_TYPE, DATA, CLOCK, RGB>(leds, NUM_LEDS); 
  FastLED.clear();
  timeCounter = millis();
}



//==========================================================================
void loop() {

  //Update the clock face every second
  if(millis()-timeCounter>1000){
  	//One second has passed
  	timeCounter=millis();    
  	leds[counterA] = CHSV(hue , 255, brightness);
  	
	
	switch (counterB) {
	    case 1:
	      leds[23] = CHSV(hue , 255, brightness);
	      leds[24] = CHSV(hue , 255, brightness);
	      break;
	    case 2:
	      leds[19] = CHSV(hue , 255, brightness);
	      leds[20] = CHSV(hue , 255, brightness);
	      break;
	    case 3:
	      leds[22] = CHSV(hue , 255, brightness);
	      break;
	    case 4:
	      leds[21] = CHSV(hue , 255, brightness);
	      break;
	    default:
	      for(int i = 19; i<25; i++){
	      	leds[i] = CHSV(hue , 255, 0);
	      }
	}
	
  	counterB++;
  	if(counterB>4){	
  		counterA++;
  		if(counterA>11){
  			counterA=0;
  			for(int i = 0; i<12; i++){
  				leds[i] = CHSV(hue, 255, 0); 
  			}	
  		}
  		counterB=0;
  		hue = hue + 21;
  	}
  }
  
  	
  counterC=map((millis()-timeCounter),0,1100,0,255);
  sineWaveA = sin8(counterC);
  sineWaveB = sin8(counterC+40);
  for(int i = 12; i<18; i++){
  	bias = (i-11) * 43;
  	leds[i] = CHSV(hue , 255, sineWaveA);
  	leds[18] = CHSV(hue , 255, sineWaveB);
  	if(counterB==0){
  		leds[i] = CHSV(hue-21 , 255, sineWaveA);
  		leds[18] = CHSV(hue-21 , 255, sineWaveB);
  	}
  }
  FastLED.show();
} 
