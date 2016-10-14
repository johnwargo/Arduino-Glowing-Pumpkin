# Arduino Glowing Pumpkin

For Halloween this year, I wanted to place a glowing pumpkin in one of the front dormers of our house. I didn't want to have a simple, single color light inside, but something more interactive, so I decided to make this an Arduino project with some tri-color LEDs inside to display different colors. I used a NeoPixel ring, so I had a ring of LEDs I could work with to illuminate the pumpkin. I wanted the pumpkin to glow randomly, but I also wanted it to flash periodically to catch viewer's attention. Of course, this was easy to code on the Arduino. 

## Hardware List

For my implementation of this, I used the following hardware:

+ [13" Orange Craft Pumpkin by Ashland](http://www.michaels.com/13in-orange-craft-pumpkin-by-ashland/10476419.html).
+ [Adafruit Trinket - Mini Microcontroller - 5V Logic](https://www.adafruit.com/products/1501).
+ [NeoPixel Ring - 16 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/1463).
+ [5V 2.4A Switching Power Supply w/ 20AWG 6' MicroUSB Cable](https://www.adafruit.com/products/1995)
 
I used the 16 LED NeoPixel because that's what I had, I probably should have used the [NeoPixel Jewel - 7 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/2226) or the [NeoPixel Ring - 12 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/1643).

## Assembly

I started by soldering the connector wires to the NeoPixel ring using the instructions found on the [Adafruit web site](https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections). I drilled a small hole in the top of a small enclosure and fed the wires through the hole then glued the NeoPixel ring to the top of the enclosure using Super Glue. Next, I drilled a slightly larger hole in the side of the enclosure, removed the USB connector on the end of the power supply and fed it through the hole. Next, I stripped the red and black power supply wires and soldered them to the V+ and Ground pads on the bottom of the Trinket.

## Programming

Next I used a USB cable connected between the Trinket and my development system to download the code into the Trinket from the Arduino IDE. With the cable unplugged (after successfully downloading the software), I could screw down the lid on the enclosure, supply power and the lights started glowing.

## Customizing the Code for Your Hardware Configuration

The project code is setup for my specific hardware configuration:

+ Adafruit Trinket 5v
+ Adafruit NeoPixel 16 LED ring connected to the Trinket's pin 2

Looking at the code, if you're not running the 5V trinket, you can remove the following lines of code:

	// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
	#if defined (__AVR_ATtiny85__)
	  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	#endif

The code is inside of an if statement, so it won't execute anyway if you aren't running on a Trinket 5v, but your code can never be too clean.

If you connect the NeoPixel ring to a different Trinket digital output pin, look for the following code in the application:

	// specifies the Trinket pin the NeoPixel is connected to. For this project, it's pin 2.
	#define PIN            2

Change the `2` in the code to the pin number for your configuration

If you're using a NeoPixel with a different number of LEDs, look for the following code in the application:

	// Specifies the number of NeoPixels that are attached to the Trinket
	// Change this value if you're using a 12 LED ring or some other NeoPixel configuration
	#define NUMPIXELS      16

Change the `16` for `NUMPIXELS` to the number of LEDs in your NeoPixel. Also, NeoPixels eat up a bunch of power, so if you run the code and the lights don't work like you're expecting, try reduce the number in `NUMPIXELS` to see if it works better when not using all LEDs in your NeoPixel. 

## Application Code

The main loop in the application picks a number between 0 and 10, and if the number is greater than 8, it kicks off the `flicker()` function (described later). If less than 8, it picks a random color from the colors array and calls the `rotateLights()` function to cycle the ring's LEDs to the selected color.  

	void loop() {
	  //generate a random integer between 1 and 10
	  //if it's a 9 or a 10, ...
	  if ((int)random(11) > 8) {
	    //do that flicker thing
	    flicker();
	  } else {
	    //otherwise, pick a random color and set each pixel individually to that color
	    //with a random time delay between setting each pixel       
	    stepLights(colors[(int)random(1, numColors + 1)], (int)random(50, 500));
	  }
	}

The `flicker()` function sets the ring's LEDs to white then flickers them a random number of times, each for a random duration. The `flashCount` variable is set to an integer between 1 and 7 then  used as a loop counter for the flashes. The function sets a random value that controls how long the lights stay on as well as another random value to control how long of a pause there is between flashes. The end result is that it looks like a short or something is causing a white spark every so often. Pretty cool, eh?

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

Finally, the `stepLights()` function, sets the ring's LEDs to a single color sequentially, pausing a random amount of time between each (the same delay between each LED changing color, but a different delay every time the function is called). The function doesn't turn off the lights when it's done, so it has the effect of the ring's lights transitioning from one random color to another. So, it looks like a sort of multicolored glow every time the function is called.  

	void stepLights(uint32_t c, int delayVal) {
	  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
	    pixels.setPixelColor(i, c);
	    //send the updated pixel color to the hardware.
	    pixels.show(); 
	    //wait for the specified period of time (in milliseconds)
	    delay(delayVal); 
	  }
	}

No effort is made to keep `stepLights()` from getting the same color twice in a row, so, in those cases, it just seems like the lights stay at one color longer.

***

If you find this code useful, and feel like thanking me for providing it, please consider making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9). You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com). 
            