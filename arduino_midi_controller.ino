#include <MIDIUSB.h>


// The first pin of consecutive pins to attach our switches to
const int buttonPinBase = 3;
const uint8_t numberOfButtons = 5;

// An array of ints to remember the button states from the last loop
// so we can detect state transitions
int lastButtonState[numberOfButtons] = { LOW, LOW, LOW, LOW, LOW };

// An array of ints to remember the last CC we sent, so we can send 
// the corresponding different one on the next press
int lastMidiState[numberOfButtons] = { 0, 0, 0, 0, 0 };

void setup() 
{
  // We use INPUT_PULLUP to use the included pullup resistors 
  // in the microcontroller
  for (int button = 0; button < numberOfButtons; ++button)
  {
    pinMode(buttonPinBase + button, INPUT_PULLUP);
  }
}

void loop() {
  for (int button = 0; button < numberOfButtons; ++button)
  {
    int state = digitalRead(buttonPinBase + button);

    // Detect state transitions    
    if (state != lastButtonState[button]) 
    {
      // Going from low to high (on push)
      if (state == HIGH) 
      {
        // Check the last CC value we sent so we can send the right one now
        if (lastMidiState[button] == 0)
        {
          midiEventPacket_t packet = {0x0B, (uint8_t)(0xB0 | button), 0, 127};
          MidiUSB.sendMIDI(packet);
        }
        else
        {
          midiEventPacket_t packet = {0x0B, (uint8_t)(0xB0 | button), 0, 0};
          MidiUSB.sendMIDI(packet);
        }
        MidiUSB.flush();
      } 
    }
    
    // Store away the current state for the transition detection
    lastButtonState[button] = state;
  }
  
  // Delay a couple of millisecs to avoid rapid firing while closing/opening a switch
  delay(10);
}
