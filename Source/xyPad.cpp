/*
  ==============================================================================

    xyPad.cpp
    Created: 2 Apr 2024 5:36:28pm
    Author:  斉藤孝亮

  ==============================================================================
*/

#include "xyPad.h"

namespace Gui {
/*
  xyPad Thumb section
 */
xyPad::Thumb::Thumb()
{
    constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize, thumbSize);
}
void xyPad::Thumb::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::white);
    g.fillEllipse(getLocalBounds().toFloat());
}

void xyPad::Thumb::mouseDown(const juce::MouseEvent &event)
{
    dragger.startDraggingComponent(this, event);
}

void xyPad::Thumb::mouseDrag(const juce::MouseEvent &event)
{
    dragger.dragComponent(this, event, &constrainer);
    if(moveCallBack)
        moveCallBack(getPosition().toDouble());
    
}

void xyPad::Thumb::mouseDoubleClick(const juce::MouseEvent &event)
{
    
}

/*
 xyPad Slider Section
 */
xyPad::xyPad()
{
    addAndMakeVisible(thumb);
    thumb.moveCallBack = [&](juce::Point<double> position)
    {
        const std::lock_guard<std::mutex> lock(vectorMutex);
        const auto bounds = getLocalBounds().toDouble();
        const auto w = static_cast<double>(thumbSize);
        
        for(auto* slider : xSliders)
        {
            slider -> setValue(juce::jmap(position.getX(), 0.0, bounds.getWidth() - w, slider -> getMinimum(), slider -> getMaximum()));
        }
        for (auto* slider : ySliders)
        {
            slider -> setValue(juce::jmap(position.getY(), bounds.getHeight() - w, 0.0,  slider -> getMinimum(), slider -> getMaximum()));
            
        }
    };
}

void xyPad::resized()
{
    thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
    if(!xSliders.empty())
        sliderValueChanged(xSliders[0]);
    if (!ySliders.empty())
        sliderValueChanged(ySliders[0]);
}

void xyPad::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 10.f);
}

void xyPad::registerSlider(juce::Slider *slider, Axis axis)
{
    slider -> addListener(this);
    const std::lock_guard<std::mutex> lock(vectorMutex);
    if(axis == Axis::X)
        xSliders.push_back(slider);
    if (axis == Axis::Y)
        ySliders.push_back(slider);
}

void xyPad::deregisterSlider(juce::Slider *slider)
{
    slider ->removeListener(this);
    // Lock
    // Could use juce::ScopedLock and juce::CriticalSection
    const std::lock_guard<std::mutex> lock(vectorMutex);
    
    // Remove/Erase
    xSliders.erase(std::remove(xSliders.begin(), xSliders.end(), slider), xSliders.end());
    ySliders.erase(std::remove(ySliders.begin(), ySliders.end(), slider), ySliders.end());
}

void xyPad::sliderValueChanged(juce::Slider *slider)
{
//    avoid loopback
    if(thumb.isMouseOverOrDragging(false))
        return;
    
//    figure out if the slider belongs to xSlider or ySliders
    const auto isXAxisSlider = std::find(xSliders.begin(), xSliders.end(), slider) != xSliders.end();
    const auto bounds = getLocalBounds().toDouble();
    const auto w = static_cast<double>(thumbSize);
    if (isXAxisSlider) 
    {
        thumb.setTopLeftPosition(juce::jmap(slider -> getValue(), slider -> getMinimum(), slider -> getMaximum(), 0.0, bounds.getWidth() - w), thumb.getY());
    }
    else
    {
        thumb.setTopLeftPosition(thumb.getX(), juce::jmap(slider -> getValue(), slider -> getMinimum(), slider -> getMaximum(), bounds.getHeight() - w, 0.0));
        
    }
    repaint();
}

}

/* std::remove() */
/* filter + sort */
/* sort of like a filter and sort algorithm */
/* where it actually doed is it goes through*/
/* the range that is specified within this collection*/
/* ant then finds the all slider that doesnt match the filter*/
/* term that we've given here*/

