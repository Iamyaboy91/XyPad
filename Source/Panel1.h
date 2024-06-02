/*
  ==============================================================================

    Panel1.h
    Created: 29 May 2024 10:47:32pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "xyPad.h"



namespace Gui {
class Panel1 : public juce::Component
{
    public:
    Panel1(juce::AudioProcessorValueTreeState& apvts) :
            parameters(apvts),
            gainAttachment(parameters, "")
    private:
};
}
