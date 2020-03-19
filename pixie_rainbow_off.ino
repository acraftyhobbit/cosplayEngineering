
#include "Adafruit_Pixie.h"
#include "SoftwareSerial.h"


#define NUMPIXELS 1 // Number of Pixies in the strip
#define PIXIEPIN  6 // Pin number for SoftwareSerial output
#define BUTTON_PIN 2  // Pin number for Button input

SoftwareSerial pixieSerial(-1, PIXIEPIN);

Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &pixieSerial);

int buttonState = 0;         // variable for reading the pushbutton status
int currentColor = 0;       // variable for reading the current color


void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pixieSerial.begin(115200); // Pixie REQUIRES this baud rate
  
  strip.setBrightness(200);  // Adjust as necessary to avoid blinding
  strip.show();
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, Wheel(currentColor));
    }
    strip.show();
    currentColor++;
    delay(25);
    
    if (currentColor == 255) {
        currentColor=0;
    }

  } else {
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
