#include <DueTimer.h>

#if 0
#include <midi_Message.h>
#include <MIDI.h>
#include <midi_Namespace.h>
#include <midi_Defs.h>
#include <midi_Settings.h>
#endif

#include<Arduino.h>
#include <ControlChain.h>

ControlChain control_chain;

const int buttonPinBase = 3;
const int numberOfButtons = 5;

int lastButtonState[numberOfButtons] = { LOW, LOW, LOW, LOW, LOW };

float controlState[numberOfButtons] = { 0, 0, 0, 0, 0 };
cc_actuator_config_t cc_actuator_configs[numberOfButtons];


#if 0
MIDI_CREATE_DEFAULT_INSTANCE();
#endif

void setup() 
{
  #if 0
  MIDI.begin(1);

  Serial.begin(38400);
  #endif
  
  control_chain.init();
  
  const char *uri = "https://nu.fps.io/mod_button_box_hack";
  cc_device_t *device = control_chain.newDevice("ModButtonBoxHack", uri);
  
  // We use INPUT_PULLUP to use the included pullup resistors 
  // in the microcontroller
  for (int button = 0; button < numberOfButtons; ++button)
  {
    pinMode(buttonPinBase + button, INPUT_PULLUP);
    
    cc_actuator_configs[button].type = CC_ACTUATOR_MOMENTARY;
    cc_actuator_configs[button].name = "Button";
    cc_actuator_configs[button].value = &controlState[button];
    cc_actuator_configs[button].min = 0.0;
    cc_actuator_configs[button].max = 1.0;
    cc_actuator_configs[button].supported_modes = CC_MODE_TOGGLE | CC_MODE_TRIGGER;
    cc_actuator_configs[button].max_assignments = 1;
    
    cc_actuator_t *actuator;
    actuator = control_chain.newActuator(&cc_actuator_configs[button]);
    control_chain.addActuator(device, actuator);
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
        controlState[button] = 1;
      } 
      else
      {
        controlState[button] = 0;
      }
    }
    
    // Store away the current state for the transition detection
    lastButtonState[button] = state;
  }
  
  // Delay a couple of millisecs to avoid rapid firing while closing/opening a switch
  delay(10);
}
