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
volatile int Octave;
volatile int i;
volatile int Notes[10] [7] = {
  {0, 2, 4, 5, 7, 9, 11},
  {12, 14, 16, 17, 19, 21, 23},
  {24, 26, 28, 29, 32, 33, 35},
  {36, 38, 40, 41, 43, 45, 47},
  {48, 50, 52, 53, 55, 57, 59},
  {60, 62, 64, 65, 67, 69, 71},
  {72, 74, 76, 77, 79, 81, 83},
  {84, 86, 88, 89, 91, 93, 95},
  {96, 98, 100, 101, 103, 105, 107},
  {108, 110, 112, 113, 115, 117, 119}
};//Notes
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, HairlessMidiSettings);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
volatile unsigned int Velocity = 127;
volatile bool SB = 0;
volatile int LedPin[] = {2, 10, 11, 12, A0, A1, A2, A3}; //LedPin
volatile int LedNumber;
volatile int Buzzer;
void setup() {
  Serial.begin(115200);
  keypad.addEventListener(keypadEvent);
  for (i = 0; i != 8; i++) {
    pinMode(LedPin[i], OUTPUT);
  }
}

void loop() {
  char key = keypad.getKey();
}
void keypadEvent(KeypadEvent key) {
  switch (key) {
    case '1':
      NoteNumber = 0;
      LedNumber = 0;
      break;
    case '2':
      NoteNumber = 1;
      LedNumber = 1;
      break;
    case '3':
      NoteNumber = 2;
      LedNumber = 2;
      break;
    case '4':
      NoteNumber = 3;
      LedNumber = 3;
      break;
    case '5':
      NoteNumber = 4;
      LedNumber = 4;
      break;
    case '6':
      NoteNumber = 5;
      LedNumber = 5;
      break;
    case '7':
      NoteNumber = 6;
      LedNumber = 6;
      break;
    case '8':
      Velocity-=6;
      SB = 1;
      break;
    case '9':
      Velocity+=6;
      SB = 1;
      break;
    case '*':
      Velocity = 1;
      SB = 1;
      break;
    case '0':
      SB = 1;
      Velocity = 63;
      break;
    case '#':
      Velocity = 127;
      SB = 1;
      break;
  }
  volatile int Pot = analogRead(A4);
  if (Pot < 102.3) {
    Octave = 0;
  }
  else if (Pot < 204.6) {
    Octave = 1;
  }
  else if (Pot < 306.9) {
    Octave = 2;
  }
  else if (Pot < 409.2) {
    Octave = 3;
  }
  else if (Pot < 511.5) {
    Octave = 4;
  }
  else if (Pot < 613.8) {
    Octave = 5;
  }
  else if (Pot < 716.1) {
    Octave = 6;
  }
  else if (Pot < 818.4) {
    Octave = 7;
  }
  else if (Pot < 920.7) {
    Octave = 8;
  }
  else if (Pot < 1023) {
    Octave = 9;
  }
  if (SB) {
    if (Velocity>=128){
      Velocity = 127;
      }
    SB = 0;

  }
  else {
    switch (keypad.getState()) {
      case PRESSED:
        MIDI.sendNoteOn(Notes [Octave] [NoteNumber], Velocity, 1);
        digitalWrite(LedPin[LedNumber], HIGH);
        //Serial.println(Notes [Octave] [NoteNumber]);
        break;

      case RELEASED:
        MIDI.sendNoteOff(Notes [Octave] [NoteNumber], Velocity, 1);
        digitalWrite(LedPin[LedNumber], LOW);
        break;
    }
  }
}
