#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    // Initialize the audio source and to allocate any resources that the audio source needs.
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    // Function is called repeatedly to get the next block of audio data from the audio source.
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    //  Free any resources that the audio source was using.
    void releaseResources() override;

    // Draw and resize the audio source's UI.
    void paint (juce::Graphics& g) override;
    void resized() override;

private:

    juce::AudioFormatManager formatManager;
    //Store up to a 100 cachedwaveforms any one time
    juce::AudioThumbnailCache thumbCache{100};
    // Control the playback of the DJAudioPlayer objects.
    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    DJAudioPlayer player2{formatManager};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};
    // Play the audio files that are selected in the PlaylistComponent object.
    DJAudioPlayer playerForPlaylist{formatManager};
    // Mix the audio from the player1, player2, and playerForPlaylist objects.
    juce::MixerAudioSource mixerSource;
    // Display the list of audio files that are available to play.
    PlaylistComponent playlistComponent{&playerForPlaylist, &deckGUI1, &deckGUI2};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};