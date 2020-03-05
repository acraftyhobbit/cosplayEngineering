const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin
   

int ledState = HIGH;   // variable for reading the LED status  
int buttonState = 0;   // variable for reading the pushbutton status
int previousButtonState = LOW;    //variable for previous button status


long time = 0;         //time is in milliseconds
long debounce = 200;   //the debounce time, increase if output flickers

int mode = 0;           //variable for keeping track of the mode
int blinkCounter = 0;   //variable for keeping count through the loop

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup()
{
   // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop()
{
   buttonState = digitalRead(buttonPin);
//if button changed state wait a bit to ignore the noise on the circuit keep track of it through time
  if (buttonState == HIGH && previousButtonState == LOW && millis() - time > debounce){
    mode++;
    if(mode > 3) mode = 0;
    if (mode == 3) {
      if (ledState == LOW) brightness = 0;
      else brightness == 255;
      }
    time = millis();    
  }
  if (mode == 0) {
    //turn off LED:
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    }
  if (mode == 1) {
    //turn on LED:
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
  }
  if (mode == 2){
    //make the LED blink:
     blinkCounter++;
  if(blinkCounter > 30){
    ledState = !ledState;
     blinkCounter = 0; }
     digitalWrite(ledPin, ledState);
  }
  if(mode ==3){
   // turn LED on and change the brightness for each time through the loop:
    brightness = brightness + fadeAmount;
    analogWrite(ledPin, brightness);
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
  }
  }

   previousButtonState = buttonState; //record the button status
}
