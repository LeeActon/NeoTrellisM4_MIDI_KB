#pragma once

#include "NeoTrellisM4_MIDI_KB.h"
#include "StateButton.h"

#define CHORD_COUNT 14
class ChordSelector : public StateButton
    {
    int chordsPlaying;
    static unsigned short int chordNotes[CHORD_COUNT];
    static long int chordColors[CHORD_COUNT];
    public:
    ChordSelector() : StateButton(CHORD_COUNT, 0, chordColors)
        {
        }
        
    virtual void Press();
    int chordDelay = 10;
    void Chord(int rootNote, bool on);
    };

extern ChordSelector chordSelector;
