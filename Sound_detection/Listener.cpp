#include "Listener.h"
#include <Arduino.h>

bool Listener::triggered = false; // Shared variable between listeners. Keeps track of if any have been triggered.

unsigned long startMillis = 0;    // The time at which a detection cycle starts
unsigned int range = 0;           // The difference in detected microphone values over a detection cycle

unsigned int micMax = 0;       // The highest detected microphone value over a detection cycle
unsigned int micMin = 1024;    // The lowest detected microphone value over a detection cycle

// Construct a listener object. Assign parameters to local variables using initializers.
Listener::Listener(int vMin, int vMax, int pMin, int pMax, int w, int f) :
volumeMin(vMin), volumeMax(vMax), pitchMin(pMin), pitchMax(pMax), window(w), frequency(f) {
}

// Perform the main functionality of the listeners. Essentially the listener object's main loop
void Listener::tick(unsigned int sample) {
  // State machine. The listener can be at the start of a loop, middle of a loop, or end of a loop.

  // Start of a loop
  if (millis() - startMillis > window * frequency || startMillis == 0 ) {   // Special case: startMillis == 0; code always runs upon start
    startMillis = millis();   // Track the beginning of the current loop
    range = 0;                // Reset range
    micMax = 0;            // Reset max
    micMin = 1024;         // Reset min
  
  // Middle of a loop
  } else if (millis() - startMillis < window * frequency) {
    if (millis() % frequency == 0) {          // If the current frame is an active frame for the listener...
      if (sample < 1024) {
        if (sample > micMax) micMax = sample; // ...update maximum detected value.
        if (sample < micMin) micMin = sample; // ...update minimum detected value.
      }
    }
  
  // End of a loop
  } else {
    range = micMax - micMin;              // Update range with collected microphone data values.
    double volts = (range * 5.0) / 1024;  // Convert this range to the average voltage across the microphone during the loop.

    Serial.println(volts);                // Display this voltage to the consol.

    // Check if the detected voltage is within the listener's range for detection.
    // This would ideally be scaled to measure pitch and other aspects of sounds for more detailed detection.
    if (volts > volumeMin && volts < volumeMax) {
      triggered = true;                   // Set triggered to TRUE if sound is detected.
    }
  }
}
