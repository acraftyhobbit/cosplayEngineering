#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 7  // Number of NeoPixels

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

boolean oldState = LOW;
int mode = 0;

long counter = 0;
long maxCount = 500;
int fadeAmount = 1;
int brightness = 0;
int colorCycle = 0;

void setup() {
 pinMode(BUTTON_PIN, INPUT_PULLUP); // Initialize Button
  strip.begin(); // Initialize NeoPixel strip object
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);


  // Check if state changed from high to low (button press).
  if ((newState == HIGH) && (oldState == LOW)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == HIGH) {
      mode++;
      if (mode > 1) mode = 0;
    }
  }
  oldState = newState;
  switch (mode) {
    case 0:
      strip.clear();
      strip.show();
      brightness = 0;
      fadeAmount = 1;
      break;
    case 1:
      counter++;
      if (counter >= maxCount) {
        glowingBreath(brightness, colorCycle);
        brightness = brightness + fadeAmount;
        if (brightness == 0){ 
          colorCycle ++;
          if (colorCycle == 2){
            colorCycle= 0;
          }
        }
        if (brightness <= 0 || brightness >= 255) {
          fadeAmount = -fadeAmount;  
        }
        counter = 0;
      }
      break;
  }
}

void setStripColor(byte red, byte green, byte blue) {
  for (int i = 0; i < PIXEL_COUNT; i++ ) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}

void glowingBreath(int brightness, int colorCycle) {

  switch (colorCycle) {
    case 0: setStripColor(0, brightness, 0); break;
    case 1: setStripColor(brightness, brightness, 0); break;
  }
  strip.show();
}
