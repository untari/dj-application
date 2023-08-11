/*
  ==============================================================================

    WaveformDisplay.h
    Created: 11 Aug 2023 1:43:53pm
    Author:  bichito

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component
{
public:
    WaveformDisplay(
      juce::AudioFormatManager &formatManagerToUse,
      juce::AudioThumbnailCache &cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void loadURL(juce::URL audioURL);

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
