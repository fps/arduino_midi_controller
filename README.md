# arduino_midi_controller

A simple MIDI controller sketch for a simple MIDI controller device. It sends MIDI over the USB port such that it can be read by e.g. ttymidi on the receiving side. Sorry, no USB HID MIDI, since my arduino can't do that (diecimila).

# Requirements:

* An arduino of any kind
* 5 switches of the kind that open on press and close on release (or the other way around - need to adapt the code a little depending on which way around they are)
* Some cables
* Some soldering iron and lead
* The ArduinoMidiLibrary (import it to the sketch)

