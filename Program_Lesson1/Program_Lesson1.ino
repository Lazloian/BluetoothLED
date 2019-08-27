#include <FastLED.h> //Including the library go to Sketch, include Library

#define num_leds 10 //!!!change for real lesson!!!
#define data_pin 6//pin for sending data to the leds

int power_pin = 9; //pin that will provide the power to the led strip

CRGB leds[num_leds]; //creates an led object leds with the number of leds as num_leds

void setup() { //Code that runs once on startup

  FastLED.addLeds<NEOPIXEL, data_pin>(leds, num_leds); //Tells arduino that there is an led strip at data_pin and the number of led

  pinMode(data_pin, OUTPUT); //Sets the data_pin and power_pin as outputs
  pinMode(power_pin, OUTPUT); //power_pin sends power (500mA) and data sends data

}

void loop() { //code that runs continuously

  digitalWrite(power_pin, HIGH); //Gives power through the power_pin
  
  leds[0] = CRGB::Blue; //selecting the led strip and which led to send the color to
  leds[1] = CRGB::White; //note that the first led is led 0 not 1
  leds[2] = CRGB::Blue;

  FastLED.show(); //Turns the LEDs to the current color assigned

  //Another way to assign the color of the leds is to use a for loop

  for (int i = 0; i <= num_leds; i++) { //create a new int i and set it to 0, run the loop as long as i is less than or equal to
    leds[i] = CRGB::Blue;               //num_leds and after each time it loops add 1 to i. Set leds[i] to Blue
  }

  

}
