#include <Adafruit_NeoPixel.h>

// RGB strip is connected to pin 10
#define DO_PIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(150, DO_PIN, NEO_GRB + NEO_KHZ800);


// ================================================================
void setup() 
{
  // Initialize all pixels to 'off'
  strip.begin();

  // The whimpy power supply can't handle a full power, limit brightness a bit
  strip.setBrightness(127); // 0 = off; 255=max brightness
  allSet(0);
  strip.show(); 

  // Initialize random generator
  randomSeed(analogRead(0));  
}
 

// ================================================================
void loop() 
{
  // A few standard effects Sophia liked
  // Select a random effect from this bunch
  int effect = random(1, 5);
  byte color = random(0, 255);
  
  switch(effect)
  {
    case 1:
        // Chase effect
        // Repeat a few times
        for (int i=0; i < random(1, 3); i++)
        {
          color = random(0, 255);
          theaterChase(Wheel(color), 30);
        }
        break;
      
    case 2:
        // Rainbow chase
        // Repeat a few times
        for (int i=0; i < random(1, 3); i++)
        {
          theaterChaseRainbow(30);
        }
        break;
        
    case 3:
        // Wipe effect
        // Repeat a few times
        for (int i=0; i < random(2, 5); i++)
        {
          color = random(0, 255);
          colorWipe(Wheel(color), 20);
        }
        break;
        
    case 4:
        // Standard rainbow
        // Repeat a few times
        for (int i=0; i < random(3, 7); i++)
        {
          rainbow(20);
        }
        break;
        
    case 5:
        // Equal ranbow
        // Repeat a few times
        for (int i=0; i < random(1, 3); i++)
        {
          rainbowCycle(20);
        }
        break;
  }
}


// ================================================================
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


// Set all pixels to the same color
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


// Rainbow effect
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
