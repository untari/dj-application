/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 3 Aug 2023 4:57:51pm
    Author:  bichito

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource
{
  public: 
    // constructor
    DJAudioPlayer();
    ~DJAudioPlayer();
   
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);

    void start();
    void stop();
};