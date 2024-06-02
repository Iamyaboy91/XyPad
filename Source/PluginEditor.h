/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "xyPad.h"
#include "Panel1.h"
#include "Panel2.h"
#include "Panel3.h"


//==============================================================================
/**
*/
class XyPadAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    XyPadAudioProcessorEditor (XyPadAudioProcessor&);
    ~XyPadAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    using sliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    XyPadAudioProcessor& audioProcessor;
    juce::Slider gainSlider {juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow};
    juce::Slider panSlider {juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow};
    sliderAttachment gainAttachment, panAttachment;
    
    juce::Label gainLabel { "gainLabel", "Gain"};
    juce::Label panLabel {"panLabel", "Pan"};
    
    Gui::xyPad xyPad;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XyPadAudioProcessorEditor)
};
