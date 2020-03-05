
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  9;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int ledState = HIGH;        // variable for reading the  led status
int blinkCounter = 0;       //variable for keeping count through the loop



void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
     blinkCounter++;
    if(blinkCounter > 3000){
       ledState = !ledState;
        blinkCounter = 0; }
     digitalWrite(ledPin, ledState);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
