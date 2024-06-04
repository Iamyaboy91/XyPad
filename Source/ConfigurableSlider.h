/*
  ==============================================================================

    ConfigurableSlider.h
    Created: 4 Jun 2024 9:45:57pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
namespace Gui 
{
class ConfigurableSlider : public juce::Slider
{
public:
    ConfigurableSlider(juce::Component& parent, xyPad& xyPad):
    juce::Slider(RotaryHorizontalVerticalDrag, NoTextBox),
    parent(parent), xyPad(xyPad)
    {
        juce::PopupMenu::Item registerXAxis{ "Register to X Axis" };
        registerXAxis.action = [&]
        {
            xyPad.deregisterSlider(this);
            xyPad.registerSlider(this, xyPad::Axis::X);
            congfigureSliderColor(juce::Colours::violet);
        };
        juce::PopupMenu::Item registerYAxis{"Register to Y Axis"};
        registerYAxis.action = [&]
        {
            xyPad.deregisterSlider(this);
            xyPad.registerSlider(this, xyPad::Axis::Y);
            congfigureSliderColor(juce::Colours::cyan);
        };
        juce::PopupMenu::Item reset("Reset");
        reset.action = [&]
        {
            xyPad.deregisterSlider(this);
            congfigureSliderColor(juce::Colours::grey);
        };
        
        popupMenu.addItem(registerXAxis);
        popupMenu.addItem(registerYAxis);
        popupMenu.addSeparator();
        popupMenu.addItem(reset);
        
    }
    
private:
    void mouseDown(const juce::MouseEvent& event) override
    {
        const auto modifiers = juce::ComponentPeer::getCurrentModifiersRealtime();
        if(modifiers.isRightButtonDown())
        {
            const auto options = juce::PopupMenu::Options().withParentComponent(&parent);
            popupMenu.showMenuAsync(options);
        }
        else
        {
            juce::Slider::mouseDown(event);
        }
    }
    
    void congfigureSliderColor(const juce::Colour& color)
    {
        setColour(rotarySliderFillColourId, color.withBrightness(0.6f));
        setColour(thumbColourId, color);
    }
    
    juce::Component& parent;
    xyPad& xyPad;
    juce::PopupMenu popupMenu;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ConfigurableSlider)
};
}
