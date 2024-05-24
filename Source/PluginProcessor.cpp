/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XyPadAudioProcessor::XyPadAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
parameters(*this, nullptr, "xypad", {
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "GAIN", 1 }, "Gain", juce::NormalisableRange<float>{-60.f, 0.f, 0.01f},0.f),
    std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "PAN", 1 }, "Pan", juce::NormalisableRange<float>{-1.f, 1.f, 0.01f},0.f)
})
{
    parameters.addParameterListener("GAIN", this);
    parameters.addParameterListener("PAN", this);
}

XyPadAudioProcessor::~XyPadAudioProcessor()
{
    parameters.removeParameterListener("GAIN", this);
    parameters.removeParameterListener("PAN", this);
}

//==============================================================================
const juce::String XyPadAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool XyPadAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool XyPadAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool XyPadAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double XyPadAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int XyPadAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int XyPadAudioProcessor::getCurrentProgram()
{
    return 0;
}

void XyPadAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String XyPadAudioProcessor::getProgramName (int index)
{
    return {};
}

void XyPadAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void XyPadAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32>(samplesPerBlock), static_cast<juce::uint32>(getTotalNumInputChannels())};
    gainProcessor.prepare(spec);
    panProcessor.prepare(spec);
    
    gainProcessor.setGainDecibels(parameters.getRawParameterValue("GAIN")->load());
    panProcessor.setPan(parameters.getRawParameterValue("PAN")->load());
    
}

void XyPadAudioProcessor::releaseResources()
{
    gainProcessor.reset();
    panProcessor.reset();
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool XyPadAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    return true;
}

void XyPadAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    juce::dsp::ProcessContextReplacing<float> context { audioBlock };
    
    gainProcessor.process(context);
    panProcessor.process(context);
    
    
}

//==============================================================================
bool XyPadAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* XyPadAudioProcessor::createEditor()
{
    return new XyPadAudioProcessorEditor (*this);
}

//==============================================================================
void XyPadAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void XyPadAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState& XyPadAudioProcessor::getApvts()
{
    return parameters;
}

void XyPadAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if(parameterID.equalsIgnoreCase("GAIN"))
        gainProcessor.setGainDecibels(newValue);
    if(parameterID.equalsIgnoreCase("PAN"))
        panProcessor.setPan(newValue);
    
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new XyPadAudioProcessor();
}
