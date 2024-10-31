/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KrvstenBratenAudioProcessor::KrvstenBratenAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

KrvstenBratenAudioProcessor::~KrvstenBratenAudioProcessor()
{
}

//==============================================================================
const juce::String KrvstenBratenAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KrvstenBratenAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KrvstenBratenAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KrvstenBratenAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KrvstenBratenAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KrvstenBratenAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KrvstenBratenAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KrvstenBratenAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KrvstenBratenAudioProcessor::getProgramName (int index)
{
    return {};
}

void KrvstenBratenAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KrvstenBratenAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void KrvstenBratenAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KrvstenBratenAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KrvstenBratenAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<float> block (buffer);
        
    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        auto* channelData = block.getChannelPointer(channel);
        auto& random = juce::Random::getSystemRandom();
        
        for (int sample = 0; sample < block.getNumSamples(); ++sample) {
            if (crumbleVal < 1) return;
            const int startNum = sample - crumbleVal > 0 ? sample - crumbleVal : sample;
            const int endNum = sample + crumbleVal < block.getNumSamples() ? sample + crumbleVal : sample;
            const auto crust = channelData[random.nextInt (juce::Range<int> (startNum, endNum))];
            channelData[sample] = crust;
//            channelData[sample] = (channelData[sample] + crust) / 2;
        }
    }
}

//==============================================================================
bool KrvstenBratenAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KrvstenBratenAudioProcessor::createEditor()
{
    return new KrvstenBratenAudioProcessorEditor (*this);
}

//==============================================================================
void KrvstenBratenAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KrvstenBratenAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KrvstenBratenAudioProcessor();
}
