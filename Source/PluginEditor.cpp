/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KrvstenBratenAudioProcessorEditor::KrvstenBratenAudioProcessorEditor (KrvstenBratenAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (250, 250);

    cursedCursor = juce::MouseCursor(juce::ImageCache::getFromMemory(BinaryData::_8449135_png, BinaryData::_8449135_pngSize).rescaled(40, 40), 0, 0);
    
    crumble.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    crumble.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    crumble.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentWhite);
    crumble.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::black);
    crumble.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::transparentWhite);
    crumble.setMouseCursor(cursedCursor);
    crumble.setVelocityModeParameters();
    crumble.setScrollWheelEnabled(true);
    crumble.setDoubleClickReturnValue(true, 0.f);
    crumble.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 190, 25);
    crumble.setTextValueSuffix(" kg krvstenbraten");
    crumble.setRange(0.f, 50.f, 0.01);
    crumble.setValue(25);
    crumble.addListener(this);
    addAndMakeVisible(&crumble);

}

void KrvstenBratenAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.crumbleVal = crumble.getValue();
}

KrvstenBratenAudioProcessorEditor::~KrvstenBratenAudioProcessorEditor()
{
}

//==============================================================================
void KrvstenBratenAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::kruste_png, BinaryData::kruste_pngSize);
    const juce::Image backgroundImageRescaled = backgroundImage.rescaled(80, 80);
    g.drawImageWithin(backgroundImageRescaled, 2, -15, getWidth(), getWidth(), juce::RectanglePlacement::doNotResize);
}

void KrvstenBratenAudioProcessorEditor::resized()
{
     
    crumble.setBounds(0, 0, 180, 180);
    crumble.setCentrePosition(getWidth() / 2, getHeight() / 2);
    
}
