#include <midi_Message.h>
#include <MIDI.h>
#include <midi_Namespace.h>
#include <midi_Defs.h>
#include <midi_Settings.h>


const int buttonPinBase = 3;     
const int numberOfButtons = 5;

int lastButtonState[numberOfButtons] = { LOW, LOW, LOW, LOW, LOW };
int lastMidiState[numberOfButtons] = { 0, 0, 0, 0, 0 };

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() 
{
  MIDI.begin(1);
  // Serial.begin(9600);
  Serial.begin(38400); // baud rate for mod duo
  for (int button = 0; button < numberOfButtons; ++button)
  {
    pinMode(buttonPinBase + button, INPUT_PULLUP);
  }
}

void loop() {
  // read the state of the pushbutton value:
  
  for (int button = 0; button < numberOfButtons; ++button)
  {
    int state = digitalRead(buttonPinBase + button);
    
    if (state != lastButtonState[button]) 
    {
      // Serial.print(button + buttonPinBase, DEC);
      
      if (state == HIGH) 
      {
        if (lastMidiState[button] == 0)
        {
          MIDI.sendControlChange(button + 1, 127, 1);
          lastMidiState[button] = 1;
        }
        else
        {
          MIDI.sendControlChange(button + 1, 0, 1);
          lastMidiState[button] = 0;
        }
      } 
    }
    
    lastButtonState[button] = state;
  }
  
  delay(10);
}
