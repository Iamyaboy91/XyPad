/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "xyPad.h"
#include "ConfigurableSlider.h"
#include "Panel1.h"
#include "Panel2.h"


//==============================================================================
/**
*/
class XyPadAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    XyPadAudioProcessorEditor (XyPadAudioProcessor&);

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    XyPadAudioProcessor& audioProcessor;
    
    juce::AudioProcessorValueTreeState& parameters;
    
    Gui::Panel1 panel1;
    Gui::Panel2 panel2;
    juce::TabbedComponent tabbedComponent { juce::TabbedButtonBar::TabsAtTop };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XyPadAudioProcessorEditor)
};
