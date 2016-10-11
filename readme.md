# Arduino Glowing Pumpkin

For Halloween this year, I wanted to place a glowing pumpkin in one of the front dormers of our house. I didn't want to have a simple, single color light inside, but something more interactive, so I decided to make this an Arduino project with some tri-color LEDs inside to display different colors. I used a NeoPixel ring, so I had a ring of LEDs I could work with to illuminate the pumpkin. I wanted the pumpkin to glow randomly, but I also wanted it to flash periodically to catch viewer's attention. Of course, this was easy to code on the Arduino. 

## Hardware List

For my implementation of this, I used the following hardware:

+ [13" craft pumpkins at Michael's](http://www.michaels.com/13in-orange-craft-pumpkin-by-ashland/10476419.html).
+ [Adafruit Trinket - Mini Microcontroller - 5V Logic](https://www.adafruit.com/products/1501).
+ [NeoPixel Ring - 16 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/1463).
+ [5V 2.4A Switching Power Supply w/ 20AWG 6' MicroUSB Cable](https://www.adafruit.com/products/1995)
 
I used the 16 LED NeoPixel because that's what I had, I probably should have used the [NeoPixel Jewel - 7 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/2226) or the [NeoPixel Ring - 12 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/1643).

## Assembly

I started by soldering the connector wires to the NeoPixel ring using the instructions found on the [Adafruit web site](https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections). I drilled a small hole in the top of a small enclosure and fed the wires through the hole then glued the NeoPixel ring to the top of the enclosure using Super Glue. Next, I drilled a slightly larger hole in the side of the enclosure, removed the USB connector on the end of the power supply and fed it through the hole. Next, I stripped the red and black power supply wires and soldered them to the V+ and Ground pads on the bottom of the Trinket.

## Programming

Next I used a USB cable connected between the Trinket and my development system to download the code into the Trinket from the Arduino IDE. With the cable unplugged (after successfully downloading the software), I could screw down the lid on the enclosure, supply power and the lights started glowing.

## Operation

The main loop in the application picks a number between 0 and 10, and if the number is greater than 8, it kicks off the `flicker` function (described later). If less than 8, it picks a random color from the colors array and calls the `rotateLights` function to cycle the ring's LEDs to the selected color.  

	void loop() {
	  if ((int)random(10) > 8){
	    flicker();
	  } else {
  	    //rotate the lights, picking a random color and a random delay value from 50-500
	    rotateLights(colors[(int)random(1, numColors)], (int)random(50, 500));
	  }
	}

The `flicker` function sets the ring's LEDs to white then flickers them a random number of times, each for a random duration. The `flashCount` variable is set to an integer between 1 and 7 then  used as a loop counter for the flashes. The function sets a random value that controls how long the lights stay on as well as another random value to control how long of a pause there is between flashes. The end result is that it looks like a short or something is causing a white spark every so often. Pretty cool, eh?

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

Finally, the `rotateLights` function, sets the ring's LEDs to a single color sequentially, pausing a random amount of time between each (the same delay between each LED changing color, but a different delay every time the function is called). The function doesn't turn off the lights when it's done, so it has the effect of the ring's lights transitioning from one random color to another. So, it looks like a sort of multi-color glow every time the function is called.  

	void rotateLights(int c[], int delVal) {
	  for (int i = 0; i < NUMPIXELS; i++) {
	    pixels.setPixelColor(i, pixels.Color(c[0], c[1], c[2]));
	    pixels.show(); // This sends the updated pixel color to the hardware.
	    delay(delVal); // Delay for a period of time (in milliseconds).
	  }  
	}

No effort is made to keep `rotateLights` from getting the same color twice in a row, so, in those cases, it just seems like the lights stay at one color longer.

***

If you find this code useful, and feel like thanking me for providing it, please consider making a purchase from [my Amazon Wish List](https://amzn.com/w/1WI6AAUKPT5P9). You can find information on many different topics on my [personal blog](http://www.johnwargo.com). Learn about all of my publications at [John Wargo Books](http://www.johnwargobooks.com). 
            