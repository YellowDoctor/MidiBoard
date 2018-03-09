#include <Keypad.h>
#include <MIDI.h>
struct HairlessMidiSettings : public midi::DefaultSettings
{
  static const bool UseRunningStatus = false;
  static const long BaudRate = 115200;
};
volatile int NoteNumber;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
volatile int Notes[] = {72,74,76,77,79,81,83,84,86,};//Notes
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, HairlessMidiSettings);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
volatile unsigned int Channel = 1; 
volatile bool SB = 0;


void setup() {
  Serial.begin(115200);
  keypad.addEventListener(keypadEvent);
}

void loop() {
char key = keypad.getKey();
}
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
      Channel++;
      SB = 1;
      break;
    case '0':
      SB = 1;
      Chanel = 1; //Set Channel to one
      break;
    case '#':
      Channel--;
      SB = 1;
      break;
  }
  if (SB){
SB = 0;
  }
  else{
  switch (keypad.getState()) {
    case PRESSED:
      MIDI.sendNoteOn(Notes[NoteNumber], 127, Channel);
      break;

    case RELEASED:
      MIDI.sendNoteOff(Notes[NoteNumber], 127, Channel);
      break;
  }
  }
}
