#include "NeoTrellisM4.h"
#include <Adafruit_ADXL343.h>
#include "NeoTrellisM4_MIDI_KB.h"

#include "Button.h"
#include "ChordSelector.h"
#include "Note.h"
#include "MIDIControl.h"
#include "PitchBlend.h"

static Adafruit_ADXL343 accel = Adafruit_ADXL343(1, &Wire1);

int xCC = 1;  //choose a CC number to control with x axis tilting of the board. 1 is mod wheel, for example.

int last_xbend = 0;
int last_ybend = 0;

Adafruit_NeoTrellisM4 neoTrellisM4 = Adafruit_NeoTrellisM4();

Note C3Note(MIDI_C(3));
Note D3Note(MIDI_D(3));
Note E3Note(MIDI_E(3));
Note F3Note(MIDI_F(3));
Note G3Note(MIDI_G(3));
Note A3Note(MIDI_A(3));
Note B3Note(MIDI_B(3));

Note C4Note(MIDI_C(4));
Note D4Note(MIDI_D(4));
Note E4Note(MIDI_E(4));
Note F4Note(MIDI_F(4));
Note G4Note(MIDI_G(4));
Note A4Note(MIDI_A(4));
Note B4Note(MIDI_B(4));

Note C5Note(MIDI_C(5));
Note D5Note(MIDI_D(5));
Note E5Note(MIDI_E(5));
Note F5Note(MIDI_F(5));
Note G5Note(MIDI_G(5));
Note A5Note(MIDI_A(5));
Note B5Note(MIDI_B(5));

Note C6Note(MIDI_C(6));
Note D6Note(MIDI_D(6));
Note E6Note(MIDI_E(6));
Note F6Note(MIDI_F(6));
Note G6Note(MIDI_G(6));
Note A6Note(MIDI_A(6));
Note B6Note(MIDI_B(6));

Button* rgpButtonMatrix[BUTTON_ROWS][BUTTON_COLUMNS] =
	{
		{ &chordSelector, &C6Note, &D6Note, &E6Note, &F6Note, &G6Note, &A6Note, &B6Note},
		{ NULL,           &C5Note, &D5Note, &E5Note, &F5Note, &G5Note, &A5Note, &B5Note},
		{ NULL,           &C4Note, &D4Note, &E4Note, &F4Note, &G4Note, &A4Note, &B4Note},
		{ NULL,           &C3Note, &D3Note, &E3Note, &F3Note, &G3Note, &A3Note, &B3Note},
	};

PitchBlend pitchBlend("pitch blend (x)");

MIDIControl midiControlModulation(1, 0, 127, "mod (y)");
MIDIControl midiControlVolume(7, 0, 127, "vol (y)");
MIDIControl midiControlBalance(8, 0, 127, "bal (y)");
MIDIControl midiControlExpression(0x0B, 0, 127, "expression (y)");

MIDIControl* pMIDIControlX = &pitchBlend;
MIDIControl* pMIDIControlY = &midiControlModulation;

void setup()
	{
	Serial.begin(115200);

	neoTrellisM4.begin();
	//neoTrellisM4.setBrightness(80);

	for (int row = 0; row < BUTTON_ROWS; row++)
		{
		for (int column = 0; column < BUTTON_COLUMNS; column++)
			{
			Button* pButton = rgpButtonMatrix[row][column];

			if (pButton != NULL)
				pButton->SetRowColumn(row, column);
			}
		}
	neoTrellisM4.enableUSBMIDI(true);
	neoTrellisM4.setUSBMIDIchannel(MIDI_CHANNEL);

	if (!accel.begin())
		{
		Serial.println("Accelerometer failed to start");
		}
	}

unsigned long msLastReport = 0;
float prevX = 0;
float prevY = 0;
float prevZ = 0;
void loop()
	{
	neoTrellisM4.tick();

	while (neoTrellisM4.available())
		{
		keypadEvent e = neoTrellisM4.read();
		int key = e.bit.KEY;
		int keyRow = key / 8;
		int keyColumn = key % 8;

		Button* pButton = rgpButtonMatrix[keyRow][keyColumn];

		Serial.print("Keypad key: ");
		Serial.print(key);

		if (e.bit.EVENT == KEY_JUST_PRESSED)
			{
			Serial.println(" pressed");
			if (pButton != NULL)
				pButton->Press();
			}
		else if (e.bit.EVENT == KEY_JUST_RELEASED)
			{
			Serial.println(" released");
			if (pButton != NULL)
				pButton->Release();
			}
		}

	sensors_event_t event;
	accel.getEvent(&event);
	unsigned long msNow = millis();
	if (msNow > msLastReport + 100)
		{
		msLastReport = msNow;
		float deltaX = event.acceleration.x - prevX;
		float deltaY = event.acceleration.y - prevY;
		float deltaZ = event.acceleration.z - prevZ;
		prevX = event.acceleration.x;
		prevY = event.acceleration.y;
		prevZ = event.acceleration.z;
		/* Display the results (acceleration is measured in m/s^2) */
#if 0
		Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
		Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
		Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  "); Serial.println("m/s^2 ");
#endif
#if 0
		float threshold = 0.2;
		if ((abs(deltaX) > threshold) || (abs(deltaY) > threshold) || (abs(deltaZ) > threshold))
			{
			Serial.print("deltaX: "); Serial.print(deltaX); Serial.print("  ");
			Serial.print("deltaY: "); Serial.print(deltaY); Serial.print("  ");
			Serial.print("deltaZ: "); Serial.print(deltaZ); Serial.print("  "); Serial.println("");
			}
#endif
		}

	pMIDIControlX->Update(event.acceleration.x);
	pMIDIControlY->Update(event.acceleration.y);
	neoTrellisM4.sendMIDI();

	delay(10);
	}
