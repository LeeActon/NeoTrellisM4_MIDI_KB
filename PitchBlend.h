#pragma once

#include "NeoTrellisM4_MIDI_KB.h"
#include "MIDIControl.h"

class PitchBlend : public MIDIControl
	{
	public:
		PitchBlend(const char* name) : MIDIControl(0, 0, 16383, name)
			{
			this->deltaThreshold = 100;
			}

		virtual void SendMIDI()
			{
			neoTrellisM4.pitchBend(this->value);
			}
	};
