/*
  ==============================================================================

    xyPad.h
    Created: 2 Apr 2024 5:36:28pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace Gui {
class xyPad : public juce::Component, juce::Slider::Listener
{
public:
    enum class Axis { X, Y };
    
    class Thumb : public juce::Component
    {
    public:
        Thumb();
        void paint(juce::Graphics& g) override;
        void mouseDown(const juce::MouseEvent& event) override;
        void mouseDrag(const juce::MouseEvent& event) override;
        void mouseDoubleClick(const juce::MouseEvent& event) override;
        std::function<void(juce::Point<double>)> moveCallBack;
        
    private:
        juce::ComponentDragger dragger;
        juce::ComponentBoundsConstrainer constrainer;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb);
        
    };
        xyPad();
        void resized() override;
        void paint(juce::Graphics& g) override;
        void registerSlider(juce::Slider* slider, Axis axis );
        void deregisterSlider(juce::Slider* slider);
private:
        void sliderValueChanged(juce::Slider* slider) override;
    
        std::vector<juce::Slider*> xSliders, ySliders;
        Thumb thumb;
        std::mutex vectorMutex;
        static constexpr int thumbSize = 40;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(xyPad);
};
}
