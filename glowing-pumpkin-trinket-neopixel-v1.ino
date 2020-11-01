/**************************************************
   Glowing Pumpkin Project

   By John M. Wargo
   September 24, 2016
 **************************************************/
//===================
// Adafruit Libs
//===================
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// specifies the Trinket pin the NeoPixel is connected to. For this project, it's pin 2.
#define PIN            2
// Specifies the number of NeoPixels that are attached to the Trinket
// Change this value if you're using a 12 LED ring or some other NeoPixel configuration
#define NUMPIXELS      7

//For normal NeoPixels, use this:
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// color definitions
//uint32_t cBlue = pixels.Color(0, 0, 255);
//uint32_t cGreen = pixels.Color(0, 255, 0);
//uint32_t cNone = pixels.Color(0, 0, 0);
//uint32_t cOrange = pixels.Color(255, 128, 1);
//uint32_t cPurple = pixels.Color(128, 0, 128);
//uint32_t cRed = pixels.Color(255, 0, 0);
//uint32_t cWhite = pixels.Color(255, 255, 255);
//uint32_t cYellow = pixels.Color(255, 215, 0);

//// for RGBW NeoPixels, you have to switch to this:
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
// color definitions
uint32_t cBlue = pixels.Color(0, 0, 255, 0);
uint32_t cGreen = pixels.Color(0, 255, 0, 0);
uint32_t cNone = pixels.Color(0, 0, 0, 0);
uint32_t cOrange = pixels.Color(255, 128, 1, 0);
uint32_t cPurple = pixels.Color(128, 0, 128, 0);
uint32_t cRed = pixels.Color(255, 0, 0, 0);
uint32_t cWhite = pixels.Color(0, 0, 0, 255);
uint32_t cYellow = pixels.Color(255, 215, 0, 0);

////colors is an array of all of the colors
int numColors = 7;
uint32_t colors[] = {cBlue, cGreen, cOrange, cPurple, cRed, cWhite, cYellow};

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  // Initialize the NeoPixel library
  pixels.begin();
  // show any lights that should be on (in this case, none)
  pixels.show();

  //Initialize the random number generator with a random seed pulled from
  //analog pin #3
  randomSeed(analogRead(3));
}

void loop() {
  //generate a random integer between 1 and 10
  //  if it's a 9 or a 10, ...
  if ((int)random(11) > 8) {
    //do that flicker thing
    flicker();
  } else {
    //otherwise, pick a random color and set eac+h pixel individually to that color
    //with a random time delay between setting each pixel
    stepLights(colors[(int)random(1, numColors + 1)], (int)random(50, 500));
  }
}

void flicker() {
  // how many times are we going to flash?
  int flashCount = (int)random(1, 7);
  //flash the lights in white flashCount times
  //with a random duration and random delay between each flash
  for (int i = 0; i < flashCount; i++) {
    // Set all pixels to white and turn them on
    setColor(cWhite);
    // Delay for a random period of time (in milliseconds)
    delay((int)random(50, 150));
    //clear the lights (set the color to none)
    setColor(cNone);
    // Delay for a random period of time (in milliseconds)
    delay((int)random(100, 500));
  }
}

void stepLights(uint32_t c, int delayVal) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    //send the updated pixel color to the hardware.
    pixels.show();
    //wait for the specified period of time (in milliseconds)
    delay(delayVal);
  }
}

// Fill the pixels with a specific color
void setColor(uint32_t c) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
  }
  pixels.show();
}
