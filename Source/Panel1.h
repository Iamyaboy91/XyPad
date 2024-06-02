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
    gainAttachment(parameters, "gain", gainSlider),
    panAttachment(parameters, "pan", panSlider)
    {
        addAndMakeVisible(gainSlider);
        addAndMakeVisible(panSlider);
        addAndMakeVisible(gainLabel);
        addAndMakeVisible(panLabel);
        addAndMakeVisible(xyPad);
        
        const auto configureSliderColor = [](juce::Slider& slider, const juce::Colour& color)
        {
            slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, color.withBrightness(0.6f));
            slider.setColour(juce::Slider::ColourIds::thumbColourId, color);
        };
        
        configureSliderColor(gainSlider, juce::Colours::violet);
        configureSliderColor(panSlider, juce::Colours::cyan);
        gainSlider.setTextValueSuffix(" dB");
        
        gainLabel.setJustificationType(juce::Justification::centred);
        panLabel.setJustificationType(juce::Justification::centred);
        gainLabel.attachToComponent(&gainSlider, false);
        panLabel.attachToComponent(&panSlider, false);
    }
    
    ~Panel1()
    {
        xyPad.deregisterSlider(&gainSlider);
        xyPad.deregisterSlider(&panSlider);
    }
    
    void paint(juce::Graphics& g) override
    {
        const juce::DropShadow dropShadow( juce::Colours::black.withAlpha(0.5f), 10, {});
        dropShadow.drawForRectangle(g, xyPad.getBoundsInParent());
    }
    
    
    void resized() override
    {
        const auto container = getLocalBounds().reduced(20);
        auto bounds = container;
        
        const auto createCenteredBounds = [](juce::Component& component, const juce::Rectangle<int>& bounds)
        {
            const auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());
            component.setBounds(bounds.withSizeKeepingCentre(size, size));
        };
        
        createCenteredBounds(gainSlider, bounds.removeFromLeft(container.proportionOfWidth(0.25f)).reduced(20));
        createCenteredBounds(xyPad, bounds.removeFromLeft(container.proportionOfWidth(0.5f)).reduced(20));
        createCenteredBounds(panSlider, bounds.reduced(20));
        
    
    }
    
    
private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::AudioProcessorValueTreeState& parameters;
    
    juce::Label gainLabel { "gainLabel", "Gain" }, panLabel{"panLabel", "Pan"};
    
    juce::Slider gainSlider{ juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
    juce::Slider panSlider{ juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
    SliderAttachment gainAttachment, panAttachment;
    Gui::xyPad xyPad;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Panel1)
};
}
