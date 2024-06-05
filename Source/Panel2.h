/*
  ==============================================================================

    Panel2.h
    Created: 29 May 2024 10:47:48pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "ConfigurableSlider.h"
#include "xyPad.h"

namespace Gui {
class Panel2 : public juce::Component
{
public:
        Panel2(juce::AudioProcessorValueTreeState& apvts) :
                parameters(apvts),
                gainAttachment(parameters, "gain", gainSlider),
                panAttachment(parameters, "pan", panSlider)
    {
        addAndMakeVisible(gainSlider);
        addAndMakeVisible(panSlider);
        addAndMakeVisible(gainLabel);
        addAndMakeVisible(panLabel);
        addAndMakeVisible(xyPad);
        
        addAndMakeVisible(slider1);
        addAndMakeVisible(slider2);
        addAndMakeVisible(slider3);
        addAndMakeVisible(slider4);
        
        gainSlider.setTextValueSuffix(" dB");
        configureSliderColour(gainSlider, juce::Colours::violet);
        configureSliderColour(slider1, juce::Colours::violet);
        configureSliderColour(slider2, juce::Colours::violet);
        configureSliderColour(panSlider, juce::Colours::cyan);
        configureSliderColour(slider3, juce::Colours::cyan);
        configureSliderColour(slider4, juce::Colours::cyan);

        gainLabel.setJustificationType(juce::Justification::centred);
        panLabel.setJustificationType(juce::Justification::centred);
        gainLabel.attachToComponent(&gainSlider, false);
        panLabel.attachToComponent(&panSlider, false);

        xyPad.registerSlider(&gainSlider, Gui::xyPad::Axis::Y);
        xyPad.registerSlider(&slider1, Gui::xyPad::Axis::Y);
        xyPad.registerSlider(&slider2, Gui::xyPad::Axis::Y);
        
        xyPad.registerSlider(&panSlider, Gui::xyPad::Axis::X);
        xyPad.registerSlider(&slider3, Gui::xyPad::Axis::X);
        xyPad.registerSlider(&slider4, Gui::xyPad::Axis::X);
    }
    ~Panel2()
    {
        xyPad.deregisterSlider(&gainSlider);
        xyPad.deregisterSlider(&panSlider);
        xyPad.deregisterSlider(&slider1);
        xyPad.deregisterSlider(&slider2);
        xyPad.deregisterSlider(&slider3);
        xyPad.deregisterSlider(&slider4);
    }
    void paint(juce::Graphics& g) override
            {
                const juce::DropShadow dropShadow{ juce::Colours::black.withAlpha(0.5f), 10, {} };
                dropShadow.drawForRectangle(g, xyPad.getBoundsInParent());
            }

    void configureSliderColour(juce::Slider& slider, const juce::Colour& colour)
            {
                slider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, colour.withBrightness(0.6f));
                slider.setColour(juce::Slider::ColourIds::thumbColourId, colour);
            };

    void resized() override
    {
        const auto container = getLocalBounds().reduced(20);
        auto bounds = container;
        
        const auto createCenteredBounds = [](juce::Component& component, const juce::Rectangle<int>& bounds)
        {
            const auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());
            component.setBounds(bounds.withSizeKeepingCentre(size, size));
        };
        
        auto leftSliders = bounds.removeFromLeft(container.proportionOfWidth(0.25f)).reduced(20);
        createCenteredBounds(gainSlider, leftSliders.removeFromTop(leftSliders.proportionOfHeight(0.7f)));
        createCenteredBounds(slider1, leftSliders.removeFromLeft(leftSliders.proportionOfWidth(0.5f)));
        createCenteredBounds(slider2, leftSliders);
        
        createCenteredBounds(xyPad, bounds.removeFromLeft(container.proportionOfWidth(0.5f)).reduced(20));
        
        auto rightSliders = bounds.reduced(20);
        createCenteredBounds(panSlider, rightSliders.removeFromTop(rightSliders.proportionOfHeight(0.7f)));
        createCenteredBounds(slider3, rightSliders.removeFromLeft(rightSliders.proportionOfWidth(0.5f)));
        createCenteredBounds(slider4, rightSliders);
        
        
    }
private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::AudioProcessorValueTreeState& parameters;
    
    juce::Label gainLabel {"gainLabel", "Gain"}, panLabel{"panLabel", "Pan"};
    juce::Slider gainSlider{ juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
    juce::Slider panSlider{ juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow };
    
    SliderAttachment gainAttachment, panAttachment;
    Gui::xyPad xyPad;
    
    ConfigurableSlider slider1{ *this, xyPad};
    ConfigurableSlider slider2{ *this, xyPad};
    ConfigurableSlider slider3{ *this, xyPad};
    ConfigurableSlider slider4{ *this, xyPad};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Panel2)
};
}


