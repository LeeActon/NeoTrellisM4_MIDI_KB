#include "NeoTrellisM4.h"
#include "ChordSelector.h"

ChordSelector chordSelector;

unsigned short int ChordSelector::chordNotes[CHORD_COUNT] =
	{
	//    110           00000000
	//    109           87654321
		(B000 << 8) | B00000000,  // None
		(B000 << 8) | B01001000,  // Major
		(B001 << 8) | B01001000,  // Major6th
		(B010 << 8) | B01001000,  // Dom7th
		(B100 << 8) | B01001000,  // Major7th
		(B000 << 8) | B10001000,  // Augmented
		(B010 << 8) | B10001000,  // Augmented7th
		(B000 << 8) | B01000100,  // Minor
		(B001 << 8) | B01000100,  // Minor6th
		(B010 << 8) | B01000100,  // Minor7th
		(B100 << 8) | B01000100,  // MinorMajor7th
		(B000 << 8) | B00100100,  // Diminished
		(B001 << 8) | B00100100,  // Diminished7th
		(B010 << 8) | B00100100,  // HalfDiminished7th
	};

long int ChordSelector::chordColors[CHORD_COUNT] =
	{
	//    RRGGBB
		0x000000,
		0x000080,
		0x008000,
		0x008080,
		0x800000,
		0x800080,
		0x808000,
		0x808080,
		0x0000FF,
		0x00FF00,
		0x00FFFF,
		0xFF0000,
		0xFF00FF,
		0xFFFF00,
	};

void ChordSelector::Press()
  	{
    if (this->chordsPlaying > 0)
      return;
  
    StateButton::Press();
  
  	Serial.print("chord: ");
  	Serial.print(this->state);
  	Serial.print(" notes: root");
    
    int notes = chordNotes[this->state];
    int semitone = 0;
    while (notes != 0)
        {
        semitone++;
        if ((notes & 1) != 0)
            {
            Serial.print(" + ");
            Serial.print(semitone);
            }
        notes >>= 1;
        }
    Serial.println();
  	}

void ChordSelector::Chord(int rootNote, bool on)
	{
	int note = rootNote;
  if (sharp)
      note++;
      
	if (on)
		{
		neoTrellisM4.noteOn(note, 64);
		Serial.print("noteOn: ");
		}
	else
		{
		neoTrellisM4.noteOff(note, 64);
		Serial.print("noteOff: ");
		}
	Serial.print(note);
	neoTrellisM4.sendMIDI(); // send any pending MIDI messages
	delay(chordDelay);

	int notes = chordNotes[this->state];
	while (notes != 0)
		{
		note++;
		if ((notes & 1) != 0)
			{
			if (on)
				{
				neoTrellisM4.noteOn(note, 64);
				}
			else
				{
				neoTrellisM4.noteOff(note, 64);
				}
			Serial.print(" + ");
			Serial.print(note);
			neoTrellisM4.sendMIDI(); // send any pending MIDI messages
			delay(chordDelay);
			}
		notes >>= 1;
		}
	Serial.println();
	if (on)
		this->chordsPlaying++;
	else
		this->chordsPlaying--;
	}
