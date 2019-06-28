#pragma once

#define MIDI_C4 60
#define MIDI_D4 62
#define MIDI_E4 64
#define MIDI_F4 65
#define MIDI_G4 67
#define MIDI_A4 69
#define MIDI_B4 71
#define MIDI_A(o) (MIDI_A4 + (o - 4)*12)
#define MIDI_B(o) (MIDI_B4 + (o - 4)*12)
#define MIDI_C(o) (MIDI_C4 + (o - 4)*12)
#define MIDI_D(o) (MIDI_D4 + (o - 4)*12)
#define MIDI_E(o) (MIDI_E4 + (o - 4)*12)
#define MIDI_F(o) (MIDI_F4 + (o - 4)*12)
#define MIDI_G(o) (MIDI_G4 + (o - 4)*12)

class Note : public Button
	{
	private:
		int rootTone;
	public:
		Note(int rootTone)
			{
			this->rootTone = rootTone;
			}
		virtual void Press()
			{
			Button::Press();
			chordSelector.Chord(this->rootTone, true);
			}
		virtual void Release()
			{
			Button::Release();
			chordSelector.Chord(this->rootTone, false);
			}
	};
