#include "Listener.h"         // Include the listener class

const int soundPin = 0;       // Pin for the microphone
const int motorPin = 6;       // Pin for the motor

unsigned int sample;          // Hold the microphone's sample in a given frame

Listener fireAlarm(4, 100, 0, 0, 50, 10000);  // setup a listener for fire alarms
Listener gunShot(7, 100, 0, 0, 50, 1);        // setup a listener for gunshots
// This list of listeners would arbitrarily increase for every sound we want to detect.

void setup () {
  Serial.begin(9600);         // Setup a consol output stream for debugging/developing
  pinMode(motorPin, OUTPUT);  // Assign the vibration motor's pin to output
  pinMode(soundPin, INPUT);   // Assign the microphone breakout board's pin to input
}

void loop () {
  sample = analogRead(soundPin);  // Read from the microphone each frame.
  // This may be optimized later on to check if any listener needs a sample that frame.

  // Run through the sound detection opperation for each listener.
  fireAlarm.tick(sample);
  gunShot.tick(sample);
  // As more listeners are added, they would be added below line 25, calling their tick method.

  // If any listeners detect their sounds, triggered will be set to TRUE.
  if (Listener::triggered) {
    Serial.println("Sound detected, activating motor.");
    digitalWrite(motorPin, HIGH); // Turn the vibration motor on.
    delay(1000);                  // Wait one second.
    digitalWrite(motorPin, LOW);  // Turn the vibration motor off.
    Listener::triggered = false;  // Reset the triggered variable back to FALSE;
  }

}
