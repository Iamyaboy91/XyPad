/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XyPadAudioProcessorEditor::XyPadAudioProcessorEditor (XyPadAudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p),
gainAttachment(p.getApvts(), "GAIN", gainSlider),
panAttachment(p.getApvts(), "PAN", panSlider)
{
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(panSlider);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(panLabel);
    addAndMakeVisible(xyPad);
    
    gainLabel.setJustificationType(juce::Justification::centred);
    panLabel.setJustificationType(juce::Justification::centred);
    gainLabel.attachToComponent(&gainSlider, false);
    panLabel.attachToComponent(&panSlider, false);
    xyPad.registerSlider(&gainSlider, Gui::xyPad::Axis::Y);
    xyPad.registerSlider(&panSlider, Gui::xyPad::Axis::X);
    
    
    setSize (500, 300);
    setResizable(true, true);

}

XyPadAudioProcessorEditor::~XyPadAudioProcessorEditor()
{
    xyPad.deregisterSlider(&gainSlider);
    xyPad.deregisterSlider(&panSlider);
}

//==============================================================================
void XyPadAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    
}

void XyPadAudioProcessorEditor::resized()
{
    const auto container = getLocalBounds().reduced(20);
    auto bounds = container;
    
    gainSlider.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.25f)));
    xyPad.setBounds(bounds.removeFromLeft((container.proportionOfWidth(0.5))));
    panSlider.setBounds(bounds);
}
