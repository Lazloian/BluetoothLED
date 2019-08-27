#include <FastLED.h>
#include <SoftwareSerial.h> //the library that allows us to open a serial port to send information

SoftwareSerial mySerial(7, 8); //RX, TX

#define num_leds 10
#define data_pin 6

int power_pin = 9;

char character; //A data type that holds one value (string, int, ect)

boolean flag = false; //Boolean is a value that is either true or false

String data0 = "0",
       data1 = "1"; //The data strings we will use to comapre to the incoming serial transmissions

CRGB leds[num_leds];

void setup() {

  mySerial.begin(9600);
  Serial.begin(9600); //Sets the rate for serial data transmission in bits per second

  FastLED.addLeds<NEOPIXEL, data_pin>(leds, num_leds);

  pinMode(data_pin, OUTPUT);
  pinMode(power_pin, OUTPUT);

  mySerial.print("Send data"); //Lets us know that the arduino is ready for serial communication

}

void loop() {

  digitalWrite(power_pin, HIGH);

  String Data = ""; //Creates a new string Data
  flag = false; //Flag is set to false again

  while(mySerial.available()) { //while the serial port is able to be read from the below code will run

    character = mySerial.read(); //sets character to the value that is sent
    Data.concat(character); //sets Data equal to the string value of character
    flag = true; //sets flag to true
    delay(100); //delay in order to not sent too much information
  }

  if (flag) { //runs when flag is set to true

    Data.trim(); //removes all spaces in front of or behind the string
    Serial.println(Data); //prints the string Data to the Serial monitor

    if (Data == "0") { //If Data equals the string "0" then if runs, the data sent through the serial port is a string
      for (int i = 0; i <= num_leds; i++) {
        leds[i] = CRGB::Black; //Sets the color to black which turns the LEDs off
      }
      FastLED.show();
    }
    else if (Data == "1") {
      for (int i = 0; i <= num_leds; i++) {
        leds[i] = CRGB::White;
      }
      FastLED.show();
    }
  }

  

}











