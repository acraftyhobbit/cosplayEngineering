#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define BUTTON_PIN   2 // Digtial pin connected to the button

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 7  // Number of lights on strand

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
int mode = 0; // // Currently-active mode


void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Initialize Button
  strip.begin(); // Initialize NeoPixel strip object
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
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
    //turn the light on
      setColor(strip.Color(0,   255,   0), 50);    // Red
      break;
  }
}

void setColor(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
