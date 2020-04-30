#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2 // Digital pin connected to the button.

#define PIXEL_PIN    6  // Digital pin connected to the lights.

#define PIXEL_COUNT 7  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

boolean oldState = LOW; // button state variable
int mode = 0;  // Currently-active mode

long counter = 0; // current count of the cycle
long maxCount = 10000; // max level to cycle counter adjust to change the speed

int location = 0; //number of the light location

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
    //turn off the lights
      strip.clear();
      strip.show();
      break;
    case 1:
    //turn  on the lights in a chase pattern
      counter++;
      if (counter == maxCount) {
        lightChase(strip.Color(255, 255, 0), location); // white
        counter = 0;
        location++;
        if (location == 3) {
          location = 0;
        }
      }
      break;


  }
}

void lightChase(uint32_t color, int location) {
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'i' counts up from 'location' to end of strip in steps of 3...
      for (int i = location; i < strip.numPixels(); i += 3) {
        strip.setPixelColor(i, color); // Set pixel 'i' to value 'color'
      }
      strip.show(); // Update strip with new contents
  }
