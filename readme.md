# Arduino Glowing Pumpkin

For Halloween this year, I wanted to place a glowing pumpkin in one of the front dormers of our house. I didn't want to have a simple, single color light inside, but something more interactive, so I decided to make this an Arduino project with some tri-color LEDs inside to display different colors. I used a NeoPixel ring, so I had a ring of LEDs I could work with to illuminate the pumpkin. I wanted the pumpkin to glow randomly, but I also wanted it to flash periodically to catch viewer's attention. Of course, this was easy to code on the Arduino. 

## Hardware List

For my implementation of this, I used the following hardware:

+ [13" Orange Craft Pumpkin by Ashland](http://www.michaels.com/13in-orange-craft-pumpkin-by-ashland/10476419.html).
+ [Adafruit Trinket - Mini Microcontroller - 5V Logic](https://www.adafruit.com/products/1501).
+ [NeoPixel Ring - 16 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/1463).
+ [5V 2.4A Switching Power Supply w/ 20AWG 6' MicroUSB Cable](https://www.adafruit.com/products/1995)
 
I started with the 16 LED NeoPixel because that's what I had on hand. Later, I switched to the [NeoPixel Jewel - 7 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/products/2226). When you look at the code, you'll see two blocks of code at the start of the application that control settings for the NeoPixels. Be sure to uncomment the code for your NeoPixel configuration and comment out the other block of code before you compile the application. 

## Assembly

I started by soldering the connector wires to the NeoPixel ring using the instructions found on the [Adafruit web site](https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections). The NeoPixel takes three connections: 

+ 5V (red wire, if possible)
+ Ground (black wire, if possible)
+ Data In (any color)

> **Note:** Be sure to connect a wire to the *Data In* connector on the NeoPixel, not *Data Out*.

Next, I drilled a small hole in the top of a small enclosure and fed the wires from the NeoPixel through the hole then glued the NeoPixel ring to the top of the enclosure using a hot glue gun. You could probably use SuperGlue, but you'll have to make sure the NeoPixel ring is flush against the cover to use this approach. 

Next, I drilled a hole in the side of the enclosure right at the top edge of the case (where the case and cover connect). This allows me to lay the USB cable in the case and attach the cover, but also remove it later if I need to. In my first iteration of this, I removed the USB connector on the end of the power supply, stripped the red and black power supply wires and soldered them to the V+ and Ground pads on the bottom of the Trinket. For the next batch, I left the USB connector on the cable and just plugged it in.

Don't plug it in quite yet, we need the USB connection on the Trinket board to load the application later.

> **Note:** Tie a knot in the USB cable inside the case to ensure someone doesn't accidentally pull the wire out of the case. The power supply I selected only has power wires (not any data wires) in the cable, so it's easy to manipulate into a knot.

Finally, I soldered the data wire from the NeoPixel to the Trinket's `D2` pin (lower-right corner of the image), the red wire to the Trinket's `5V` connector (lower-right corner of the image), and the black wire to the `GROUND` connector (upper-left side of the image). I picked D2 for the NeoPixel data input connection because it made it easier for me to solder the wires. I have one wire connected to `GROUND` and the other two right next to each other on the other side of the board. 

![Adafruit Trinket 5V Pinouts](https://cdn-learn.adafruit.com/assets/assets/000/025/644/medium800/trinket5.png?1432753785)

## Programming

Next I used a USB cable connected between the Trinket and my development system to download the code into the Trinket from the Arduino IDE. With the cable unplugged (after successfully downloading the software), I could screw down the lid on the enclosure, supply power and the lights started glowing. Refer to [Introducing Trinket](https://learn.adafruit.com/introducing-trinket/introduction) for instructions on how to setup your development system and download code to the microcontroller.

## Customizing the Code for Your Hardware Configuration

### Trinket Settings

The project code is setup for my specific hardware configuration. If you're not running the 5V trinket, you can remove the following lines of code:

	// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
	#if defined (__AVR_ATtiny85__)
	  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
	#endif

The code is inside of an `if` statement, so it won't execute anyway if you aren't running on a Trinket 5v, but your code can never be too clean IMHO.

### Digital Output Pin

If you connect the NeoPixel ring to a different Trinket digital output pin (there are 5 - look for the purplish-blue symbols in the figure, they're labeled 0 through 4), look for the following code in the application:

	// specifies the Trinket pin the NeoPixel is connected to. For this project, it's pin 2.
	#define PIN            2

Change the `2` in the code to the pin number for your configuration

### Number of NeoPixel LEDs

If you're using a NeoPixel with a different number of LEDs, look for the following code in the application:

	// Specifies the number of NeoPixels that are attached to the Trinket
	// Change this value if you're using a 12 LED ring or some other NeoPixel configuration
	#define NUMPIXELS      16

Change the `16` for `NUMPIXELS` to the number of LEDs in your NeoPixel. Also, NeoPixels eat up a bunch of power, so if you run the code and the lights don't work like you're expecting, try reduce the number in `NUMPIXELS` to see if it works better when not using all LEDs in your NeoPixel. 

### NetPixel Constants

The enhance code readability, I defined a bunch of color constants in the code. The original NeoPixel devices used **RGB (Red, Green, Blue)** LEDs, so my constants (and the code to initialize the NeoPixel library) used to three value color constants. If you're using one of these NeoPixels, be sure the following lines of code in the application are *uncommented* like they are in the example below: 

	//For normal NeoPixels, use this:
	Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
	// color definitions
	uint32_t cBlue = pixels.Color(0, 0, 255);
	uint32_t cGreen = pixels.Color(0, 255, 0);
	uint32_t cNone = pixels.Color(0, 0, 0);
	uint32_t cOrange = pixels.Color(255, 128, 1);
	uint32_t cPurple = pixels.Color(128, 0, 128);
	uint32_t cRed = pixels.Color(255, 0, 0);
	uint32_t cWhite = pixels.Color(255, 255, 255);
	uint32_t cYellow = pixels.Color(255, 215, 0);

Newer NeoPixel devices added a 4th color: white (actually, white isn't a color, it's light made up of all colors, but for this discussion, what I mean is that Adafruit added a 4th LED to the NeoPixel array, a white one). This required a change in the code since I now needed 4 value color arrays for my color constants. So, if you're using a **RGBW (Red Green, Blue, White)** NeoPixel, comment out the previous block of code and uncomment the following lines: 

	// for RGBW NeoPixels, you have to switch to this:
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

## Application Code

The application's `setup` function initializes the NeoPixel array and the random number generator. 

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
            