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

// color definitions
int cBlue[] = {0, 0, 255};
int cGreen[] = {0, 255, 0};
int cOrange[] = {255, 128, 1};
int cPurple[] = {128, 0, 128};
int cRed[] = {255, 0, 0};
int cWhite[] = {255, 255, 255};
int cYellow[] = {255, 215, 0};
//colors is an array of all of the colors
int numColors = 7;
int colors[] = {cBlue, cGreen, cOrange, cPurple, cRed, cWhite, cYellow};

// specifies the Trinket pin the NeoPixel is connected to. For this project, it's pin 2.
#define PIN            2

// Specifies the number of NeoPixels that are attached to the Trinket
// Change this value if you're using a 12 LED ring or some other NeoPixel configuration
#define NUMPIXELS      16

// Let the NeoPixel library know how many LEDs we have and which pin it's connected to
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pixels.begin(); // This initializes the NeoPixel library.
  //cut the brightness in half (1 to 256)
  pixels.setBrightness(64);
  pixels.show();

  //Initialize the random number generator with a random seed pulled from
  //analog pin #3
  randomSeed(analogRead(3));
}

void loop() {
  if ((int)random(10) > 8) {
    flicker();
  } else {
    //rotate the lights, picking a random color and a random delay value from 50-500
    rotateLights(colors[(int)random(1, numColors + 1)], (int)random(50, 500));
  }
}

void flicker() {
  // how many times are we going to flash?
  int flashCount = (int)random(1, 7);
  //start flashing
  for (int i = 0; i < flashCount; i++) {
    // Set all pixels to white
    setColor(pixels.Color(127, 127, 127));
    delay((int)random(50, 150)); // Delay for a period of time (in milliseconds).
    clearPixels();
    delay((int)random(100, 500));
  }
}

void rotateLights(int c[], int delVal) {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(c[0], c[1], c[2]));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delVal); // Delay for a period of time (in milliseconds).
  }
}

void clearPixels() {
  setColor(pixels.Color(0, 0, 0));
}

// Fill the dots one after the other with a color
void setColor(uint32_t c) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
  }
}

