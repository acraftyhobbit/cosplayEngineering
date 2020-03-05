// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin
   

int ledState = HIGH;    // variable for reading the led status
int buttonState = 0;    // variable for reading the pushbutton status

int previousButtonState = LOW;  //variable for previous button status
int mode = 0;           //variable for keeping track of the mode
long time = 0;         //time is in milliseconds
long debounce = 200;   //the debounce time, increase if output flickers



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
  if (buttonState == HIGH && previousButtonState == LOW && millis() - time > debounce) {
    mode++; 
    if(mode > 1) mode = 0;
    time = millis();    
  }
  if (mode == 0) {
    // turn off the LED
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    }
  if (mode == 1){
     ledState = HIGH;
     digitalWrite(ledPin, ledState);
  }   
  previousButtonState = buttonState; //record the button status
}
