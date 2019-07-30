/*
 * Countdown Timer
 * 
 * Connect a push button between 5V and Pin 7. Use a 10k Ohm 
 * pull-down resistor.
 * 
 * Connect an LED and a suitable current-limiting resistor
 * between Pin 13 and GND. Or use the built-in LED. Up to you.
 * 
 * When the button is pressed, a countdown timer will start.
 * Monitor the serial port to view the output.
 * 
 * Created by Adam Corrie on 30/07/2019
 * Licensed under the GNU General Public License v3.0
 * 
 */

#define buttonPin 7 // define buttonPin as Pin 7
#define ledPin 13 // define ledPin as Pin 13

int countdownTimerDuration = 10; // set the number of seconds the countdown timer lasts
String countdownTimerMessage = "BOOM!"; // set a message to display when the countdown timer completes

// Global variables for the timer functionality
bool countingDown;
int countdownTimerPosition;
unsigned long secondsTimer;
int previousButtonState;

void setup() {
  countingDown = false; // initialise the variable
  pinMode(buttonPin, INPUT); // configure buttonPin as an INPUT pin
  pinMode(ledPin, OUTPUT); // configure ledPin as an OUTPUT pin
  previousButtonState = LOW; // initialise the variable; LOW is a logical 0
  Serial.begin(9600); // start serial communication at 9,600 baud
}

void loop() {
  // check button state and store in local variable
  int currentButtonState = digitalRead(buttonPin);
  // check if the button has just been pressed
  if ((previousButtonState == LOW) && (currentButtonState == HIGH)) {
    // set countdown timer flag to true, signalling the start of the countdown timer
    countingDown = true;
    // set the countdown timer duration
    countdownTimerPosition = countdownTimerDuration;
    // print countdown timer starting position to the serial port
    Serial.println(countdownTimerPosition);
    // call the startSecondsTimer function
    startSecondsTimer();
    // debounce the button with a 50ms delay
    delay(50); 
  }
  // store current button state for next cycle
  previousButtonState = currentButtonState;
  // check if the countdown timer is running
  if (countingDown) {
    // check if one second has elapsed
    if (millis() > secondsTimer) {
      // decrement the countdown position
      countdownTimerPosition--;
      // check if the countdown position is 1 or greater
      if (countdownTimerPosition > 0) {
        // print countdown timer position to the serial port
        Serial.println(countdownTimerPosition);
        // restart the seconds timer
        startSecondsTimer();
      }
      else if (countdownTimerPosition == 0) {
        // print countdown timer completion message to the serial port
        Serial.println(countdownTimerMessage);
        // set ledPin to HIGH
        digitalWrite(ledPin, HIGH);
        // restart the seconds timer
        startSecondsTimer();
      }
      else {
        // set ledPin to LOW
        digitalWrite(ledPin, LOW);
        // set countdown timer flag to false, signalling the end of the countdown timer
        countingDown = false;
      }
    }
  }
}

// custom function for starting the timer
void startSecondsTimer() {
  // capture the current time in milliseconds and add 1000ms
  secondsTimer = millis() + 1000;
}
