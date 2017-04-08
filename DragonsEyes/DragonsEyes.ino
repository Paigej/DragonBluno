#include <Adafruit_NeoPixel.h>
#include "PlainProtocol.h"

#define PIN 6
#define PIXEL_COUNT 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN, NEO_GRB + NEO_KHZ800);

//PlainProtocol constructor, define the Serial port and the baudrate.
PlainProtocol myBLUNO(Serial,115200);

   int red  = 100;
   int green= 0;
   int blue = 50;

void setup() {
  
  myBLUNO.init();   
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

 if (myBLUNO.available()) {    //receive valid command
      
        if(myBLUNO.receivedCommand =="RGBLED"){ 
            
            red  = (myBLUNO.receivedContent[0]);
            green= (myBLUNO.receivedContent[1]);
            blue = (myBLUNO.receivedContent[2]);

            //Defaut Bluno App does sets minimum to zero causing color to be too white
            //zero out color if at minimum
            if (red == 60){red=0;}
            if (green == 60){green=0;}
            if (blue == 60){blue=0;}
              
            colorWipe(strip.Color(red, green, blue), 50); // R
            }
    }  

  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(100, 0, 50), 50); // Blue
  //colorWipe(strip.Color(30, 0, 20), 50); // Blue
  //Send a theater pixel chase in...
  //theaterChase(strip.Color(20, 50, 0), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 50); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue

}

// Fill the dots one after the other with a color

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      //delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
    // strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
     strip.setPixelColor(i, (Wheel(((i * 256 / strip.numPixels()) + j)& 255)));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//Creates a color wheel with dimmed colors
uint32_t dimWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(85 - WheelPos , 0, WheelPos*2);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos*2, 85 - WheelPos*2);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos*2, 85 - WheelPos*2, 0);
  }
}

