
#include "SoftwareSerial.h"
#include "Adafruit_Pixie.h"

#define NUMPIXELS 1 // Number of Pixies in the strip
#define PIXIEPIN  6 // Pin number for SoftwareSerial output
#define BUTTON_PIN 2  // Pin number for Button input

SoftwareSerial pixieSerial(-1, PIXIEPIN);

Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &pixieSerial);
// Alternately, can use a hardware serial port for output, e.g.:
// Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &Serial1);

int buttonState = 0;         // variable for reading the pushbutton status


void setup() {
  int i;
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Ready to Pixie!");

  pixieSerial.begin(115200); // Pixie REQUIRES this baud rate
  // Serial1.begin(115200);  // <- Alt. if using hardware serial port

  strip.setBrightness(200);  // Adjust as necessary to avoid blinding
  strip.show();
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
        if (buttonState == HIGH) {
       strip.setPixelColor(0, 255, 150, 0);
        strip.show();

    } else{
       strip.setPixelColor(0, 0, 0, 0);
        strip.show();
    }
}
