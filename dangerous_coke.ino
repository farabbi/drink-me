/* Drink Me
 *  by Jiuxin Zhu and Edanur Kuntman, Oct 19, 2018
 */

#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>

CapacitiveSensor cs = CapacitiveSensor(9,6); // 10M resistor between pins 9 & 6, pin 6 is sensor pin, add a wire and or foil if desired

// set neopixels
#define PIN 12
#define NUMPIXELS 4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int motorPin = 10;

unsigned long next_print = 0; // timer for printing sensor values to Serial
unsigned long next_switch = 0; // timer for blinking red lights

int state = 0; // 0: normal state; 1: reaching state; 2: contact state
int old_state = 0;

bool is_on = false; // flag for blinking neopixels

unsigned long show_start = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pixels.begin();
  for (int i = 0; i < 4; i = i + 1) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void loop()
{
  // read and print sensor value
  long sensor_value = cs.capacitiveSensor(30);
  if (millis() > next_print) {
    Serial.println(sensor_value); // print sensor output
    next_print = millis() + 200; // print sensor value every 200 ms
  }

  if (sensor_value < 300) { // 300: threshold when player is reaching the Coke
    state = 0;
  } else if (sensor_value < 1000) { // 1000: threshold when player touchs the Coke
    state = 1;  
  } else {
    state = 2;  
  }

  // neopixels
  if (state == 1) { 
    // neopixels turn red when player is close to the Coke
    for (int i = 0; i < 4; i = i + 1) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    pixels.show();
  } else if (state == 2 && old_state != 2) { 
    // neopixels turn red and blink when player holds the Coke
    // 1. turn off neopixels
    // 2. set neopixels' flag
    // 3. set next switch time
    for (int i = 0; i < 4; i = i + 1) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();
    is_on = false;
    next_switch = millis() + 500;
  } else if (state == 2 && old_state == 2) {
    if (millis() > next_switch) {
      if (!is_on) {
        // turn neopixels on
        for (int i = 0; i < 4; i = i + 1) {
          pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        }
        pixels.show();
        is_on = true;
        next_switch = millis() + 500;
      } else {
        // turn neopixels off
        for (int i = 0; i < 4; i = i + 1) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        }
        pixels.show();
        is_on = false;
        next_switch = millis() + 500;
      }
    }  
  } else {
    // neopixel show
    if (old_state != 0) {
      show_start = millis();
    }
    neopixel_show();
//    for (int i = 0; i < 4; i = i + 1) {
//      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    }
//    pixels.show();
  }

  // motor vibrates when player holds the Coke, and the speed increase when player is reaching the Coke
  if (state == 2) {
    analogWrite(motorPin, 255);  
  } else if (state == 1) {
    analogWrite(motorPin, map(sensor_value, 300, 1000, 0, 255));
  } else {
    analogWrite(motorPin, 0);
  }

  old_state = state;
  
  // music pauses when player is close to the Coke
  // play warning sound when player holds the Coke
}

void neopixel_show() {
    unsigned long frame = (millis() - show_start) % 8304;
    if (frame < 80) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 279) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 478) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 677) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 876) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 1118) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 1245) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 1637) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 1787) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 2156) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 2361) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 2566) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 2771) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 2976) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 3218) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 3333) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 3737) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 3887) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 4244) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 4444) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 4644) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 4844) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 5044) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 5282) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 5487) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 5692) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 5897) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 6102) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 6344) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 6557) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 6770) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 6983) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 7196) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 7370) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 7555) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 7901) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    } else if (frame < 8039) {
      pixels.setPixelColor(0, pixels.Color(198, 10, 236)); // purple
      pixels.setPixelColor(1, pixels.Color(198, 10, 236));
      pixels.setPixelColor(2, pixels.Color(198, 10, 236));
      pixels.setPixelColor(3, pixels.Color(198, 10, 236));
    } else if (frame < 8304) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    }
    pixels.show();
}
