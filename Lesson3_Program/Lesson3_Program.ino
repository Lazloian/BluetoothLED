#include <FastLED.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);

#define num_leds 10
#define data_pin 6

CRGB leds[num_leds];

int power_pin = 9;

char character;

boolean flag = false;

String data0 = "0",
       data1 = "1";

String stringr = "", //Strings that will hold the rgb values
       string = "",
       stringb = "";

int g_place = 0, //Used as a reference point in finding the values of g and b
    r = 0, //rgb values that are used to set the color
    g = 0,
    b = 0;

void setup() {

  mySerial.begin(9600);
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, data_pin>(leds, num_leds);

  pinMode(data_pin, OUTPUT);
  pinMode(power_pin, OUTPUT);

  mySerial.print("Send data");

}

void loop() {

  digitalWrite(power_pin, HIGH);

  String Data = "";
  flag = false;

  while(mySerial.available()) {

    character = mySerial.read();
    Data.concat(character);
    flag = true;
    delay(100);
  }

  if (flag) {

    Data.trim();
    Serial.println(Data);

    if (Data.substring(0, 1) == "r") { //Checks is the data sent is an rgb value from the pc
      for (int i = 0; i < Data.length(); i++) {
        if (Data.substring(i, i + 1) == "g") { //finding where g is to find b and g
          g_place = i;
          stringr = Data.substring(1, i); //sets the value
        }
        else if (Data.substring(i, i + 1) == "b") { //find where b is to find both g and b
          stringg = Data.substring(g_place + 1, i);
          stringb = Data.substring(i + 1, Data.length());
        }
        Serial.println(Data.substring(i, i + 1));
      }
      r = stringr.toInt(); //converts the string rgb values to ints
      g = stringg.toInt();
      b = stringb.toInt();

      for (int i = 0; i <= num_leds; i++) {
        leds[i] = CRGB(r, g, b); //sets the color to the rgb values
      }
      FastLED.show();

      Serial.println(r); //To see if the values read by the arduino are the same ones sent from the pc
      Serial.println(g);
      Serial.println(b);
      Serial.println("Done");
    }

    if (Data == "0") {
      for (int i = 0; i <= num_leds; i++) {
        leds[i] = CRGB::Black;
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


