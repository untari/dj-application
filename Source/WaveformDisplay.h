/*
  ==============================================================================

    WaveformDisplay.h
    Created: 11 Aug 2023 1:43:53pm
    Author:  bichito

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
                         
{
public:
    WaveformDisplay(
      juce::AudioFormatManager &formatManagerToUse,
      juce::AudioThumbnailCache &cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    // Method is called when the object that is listening to changes.
    void changeListenerCallback (juce::ChangeBroadcaster *source) override;
    // Loads an audio file from a URL.
    void loadURL(juce::URL audioURL);
    // Set the ralative position of the playhead.
    void setPositionRelative(double pos);

    
private:
    // Create a thumbnail of the audio file.
    juce::AudioThumbnail audioThumb;
    // Variable to stores whether the audio file has been loaded.
    bool fileLoaded;
    // Stores the current playback position of the audio file.
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
