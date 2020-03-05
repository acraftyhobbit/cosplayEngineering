// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the BUTTON status
int ledState = HIGH;        // variable for reading the LED status
int previousButtonState = LOW;  //variable for previous button status


int mode = 0;           //variable for keeping track of the mode
int blinkCounter = 0;   //variable for keeping count through the loop

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by



void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    if (previousButtonState == LOW){
    mode++;
    if(mode > 2) mode = 0;
    }
   previousButtonState = HIGH; 
   if (mode == 0){
    //turn on LED:
    digitalWrite(ledPin, ledState);
  }
  if (mode == 1){
    //make the LED blink:
     blinkCounter++;
  if(blinkCounter > 30){
    ledState = !ledState;
     blinkCounter = 0; }
     digitalWrite(ledPin, ledState);
  }
  if(mode == 2){
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
  analogWrite(ledPin, brightness);

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
      }
     }    
  } else {
    // turn LED off:
    previousButtonState = LOW;
    digitalWrite(ledPin, LOW);
    
  }
}
