#include "Synth/PolyphonicSound.h"

bool PolyphonicSound::appliesToNote (int /*midiNoteNumber*/)
{
    return true;
}

bool PolyphonicSound::appliesToChannel (int /*midiChannel*/)
{
    return true;
}