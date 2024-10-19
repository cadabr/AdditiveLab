#pragma once

#include <JuceHeader.h>

struct PolyphonicSound final : public SynthesiserSound
{
    bool appliesToNote (int /*midiNoteNumber*/) override;
    bool appliesToChannel (int /*midiChannel*/) override;
};
