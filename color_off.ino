// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int redPin = 11;       // the number of the LED pin
const int greenPin = 10;    // the number of the LED pin
const int bluePin = 9;    // the number of the LED pin 
   

int buttonState = 0;    // variable for reading the pushbutton status
int previousButtonState = LOW;  //variable for previous button status
int mode = 0;           //variable for keeping track of the mode
long time = 0;         //time is in milliseconds
long debounce = 200;   //the debounce time, increase if output flickers



void setup()
{
  // initialize the LED pins as an output:
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
  // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);


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
    setColor(0, 0, 0);
    }
  if (mode == 1){
    setColor(0, 255, 255);  // set the light to aqua
  }   
  previousButtonState = buttonState; //record the button status
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
