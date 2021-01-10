#include <Adafruit_NeoPixel.h>

// RGB strip is connected to pin 10
#define DO_PIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, DO_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  // Initialize all pixels to 'off'
  strip.begin();

  // The whimpy power supply can't handle a full power, limit brightness a bit
  strip.setBrightness(127); // 0 = off; 255=max brightness
  allSet(0);
  strip.show(); 
}
 

void loop() 
{
  // A few standard effects Sophia liked
  // TODO: Make sequence random with random colors
  
  // A few chases
  theaterChase(strip.Color(0, 0, 255), 30);  // Blue
  theaterChase(strip.Color(255, 0, 0), 30);  // Red
  theaterChase(strip.Color(0, 255, 0), 30);  // Green
  theaterChaseRainbow(30);
  theaterChaseRainbow(30);
  theaterChaseRainbow(30);
  allSet(0); 
  
  // Wipes
  colorWipe(strip.Color(255, 0, 0), 50);  // Red  
  colorWipe(strip.Color(0, 0, 255), 50);  // Blue
  colorWipe(strip.Color(0, 255, 0), 50);  // Green
  allSet(0); 

  // Standard rainbow
  rainbow(20);
  rainbow(20);
  rainbow(20);
  rainbow(20);
  rainbow(20);
  allSet(0); 
  
  // Equal rainbow
  rainbowCycle(20);
  rainbowCycle(20);
  allSet(0); 
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
      strip.setPixelColor(strip.numPixels() - i - 1, c);
      strip.show();
      delay(wait);
  }
}


void allSet(uint32_t c)
{
  for (int i=0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, c);
  }
  strip.show();
}


// Running dots
void runningDots(uint32_t c, uint32_t dots, uint8_t wait) 
{
  for (int q=0; q < strip.numPixels(); q++) 
  {
    // All off
    for (int i=0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, 0);
    }
    
    // Dots on
    for (int i=0; i < dots; i++) 
    {
      strip.setPixelColor(strip.numPixels() - (i + q) - 1, c);
    }
    strip.show();
   
    delay(wait);   
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j < 256*5; j++) 
  { 
    // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) 
{
  for (int j=0; j<50; j++) 
  {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) 
    {
      for (int i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) 
  {     
    // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) 
    {
        for (int i=0; i < strip.numPixels(); i=i+3) 
        {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) 
        {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  if(WheelPos < 85) 
  {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) 
  {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else 
  {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
