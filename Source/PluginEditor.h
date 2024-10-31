/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class KrvstenBratenAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    KrvstenBratenAudioProcessorEditor (KrvstenBratenAudioProcessor&);
    ~KrvstenBratenAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override;
    KrvstenBratenAudioProcessor& audioProcessor;
    
    juce::Slider crumble;
    juce::Image backgroundImage;
    juce::MouseCursor cursedCursor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KrvstenBratenAudioProcessorEditor)
};
