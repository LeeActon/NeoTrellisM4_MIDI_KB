#pragma once

#include "NeoTrellisM4_MIDI_KB.h"
#include "Button.h"

class ChordSelector : public Button
{
    int chordIndex;
    int chordsPlaying;
    static unsigned short int chordNotes[];
    static long int chordColors[];
public:
  ChordSelector()
  {
    this->chordIndex = 0;
    this->chordsPlaying = 0;
  }
  virtual void Press();
  virtual void Release()
    {
    }
  int chordDelay = 10;
  void Chord(int rootNote, bool on);
};

extern ChordSelector chordSelector;
