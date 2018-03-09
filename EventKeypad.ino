/* @file EventSerialKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates using the KeypadEvent.
  || #
*/
#include <Keypad.h>
#include <MIDI.h>
struct HairlessMidiSettings : public midi::DefaultSettings
{
  static const bool UseRunningStatus = false;
  static const long BaudRate = 115200;
};
volatile int NoteNumber;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
volatile int Notes[] = {72,74,76,77,79,81,83,84,86,88,89,91};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, HairlessMidiSettings);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {
  Serial.begin(115200);
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}

void loop() {
char key = keypad.getKey();

//  if (key) {
//    Serial.println(key);
//  }
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key) {
  switch (key) {
    case '1':
      NoteNumber = 0;
      break;
    case '2':
      NoteNumber = 1;
      break;
    case '3':
      NoteNumber = 2;
      break;
    case '4':
      NoteNumber = 3;
      break;
    case '5':
      NoteNumber = 4;
      break;
    case '6':
      NoteNumber = 5;
      break;
    case '7':
      NoteNumber = 6;
      break;
    case '8':
      NoteNumber = 7;
      break;
    case '9':
      NoteNumber = 8;
      break;
    case '*':
      NoteNumber = 9;
      break;
    case '0':
      NoteNumber = 10;
      break;
    case '#':
      NoteNumber = 11;
      break;
  }
  switch (keypad.getState()) {
    case PRESSED:
      MIDI.sendNoteOn(Notes[NoteNumber], 127, 1);
      break;

    case RELEASED:
      MIDI.sendNoteOff(Notes[NoteNumber], 127, 1);
      break;

      //    case HOLD:
      //      if (key == '*') {
      //        blink = true;    // Blink the LED when holding the * key.
      //      }
      //      break;
  }
}
