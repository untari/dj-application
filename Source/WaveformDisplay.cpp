/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 11 Aug 2023 1:43:53pm
    Author:  bichito

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(
      juce::AudioFormatManager &formatManagerToUse,
      juce::AudioThumbnailCache &cacheToUse) : audioThumb(1000, formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::orange);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("file not loaded...", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
