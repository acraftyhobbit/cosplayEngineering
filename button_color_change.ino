// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int redPin = 11;       // the number of the LED pin
const int greenPin = 10;    // the number of the LED pin
const int bluePin = 9;    // the number of the LED pin 
         
boolean buttonState = LOW; //varabile for the button state
boolean previousButtonState = HIGH;  //variable for previous button status
int mode = 0;           //variable for keeping track of the mode


void setup()
{
  // initialize the LED pins as an output:
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
  // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);

void loop() {
  // Get current button state.
  buttonState = digitalRead(buttonPin);

  // Check if state changed from high to low (button press).
  if((buttonState == LOW) && (previousButtonState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW) {      // Yes, still low
      if(++mode > 6) mode = 0; // Advance to next mode, wrap around after #6
      switch(mode) {           
        case 0:
          setColor(0, 0, 0);  // off
          break;
        case 1:
          setColor(255, 0, 0);  // light color is red
          break;
        case 2:
          setColor(0, 255, 0);  // light color is green
          break;
        case 3:
          setColor(0, 0, 255);  // light color is blue
          break;
       case 4:
          setColor(255, 255, 0);  // light color is yellow
          break;
       case 5:
          setColor(0, 255, 255);  // light color is aqua
          break;
      case 6:
          setColor(80, 0, 80);  // light color purple
          break;
      }
    }
  }

  // Set the last-read button state to the previous state.
  previousButtonState = buttonState;
}

void setColor(int red, int green, int blue)
{
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
