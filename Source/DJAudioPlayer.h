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
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
   
    // Initialize the audio player and to allocate any resources that the audio player needs.
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    // Get the next block of audio data from the audio player. 
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill);
    // Release any resources that the audio player was using.
    void releaseResources();

    // Loads an audio file from a URL. The audioURL parameter is a pointer to the URL of the audio file.
    void loadURL(juce::URL audioURL);
    // The gain is a value that controls the volume of the audio player.
    void setGain(double gain);
    // Controls how fast the audio player plays the audio file.
    void setSpeed(double ratio);
    // The playback position is the point in the audio file that is currently being played.
    void setPosition(double posInSecs);
    // Sets the playback position of the audio player relative to the current position.
    void setPositionRelative(double pos);
    // Start and stop the audio player playing.
    void start();
    void stop();

    // Get the relative position of the playhead
    double getPositionRelative();
    // Gets length in seconds
    double getLengthInSeconds();

  private:
    // Manager for audio formats.
    juce::AudioFormatManager& formatManager;
    // This object will be used to read audio data from a file.
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    // This object will be used to play the audio data from the readerSource object.
    juce::AudioTransportSource transportSource;
    // Resample the audio data from the transportSource object.
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
};