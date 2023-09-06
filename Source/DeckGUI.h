/*
  ==============================================================================

    DeckGUI.h
    Created: 4 Aug 2023 4:06:27pm
    Author:  bichito

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer,
                 public juce::LookAndFeel_V4
{
public:
    DeckGUI(DJAudioPlayer* player,
      juce::AudioFormatManager &formatManagerToUse,
      juce::AudioThumbnailCache &cacheToUse
    );
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // Implement button, slider listener.
    void buttonClicked(juce::Button *) override;
    void sliderValueChanged(juce::Slider *slider) override;

    // Drag and Drop the file
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    // Function is called periodically by a timer.
    void timerCallback() override;
    // Draw a rotary slider.
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                            const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

private:
    // A unique identifier for the deck.
    int id;
    // A custom look and feel for the deck.
    juce::LookAndFeel_V4 otherLookAndFeel;
    // Adds button to play the audio file.
    juce::TextButton playButton{"PLAY"};
    // Adds loop button
    juce::ToggleButton loopButton{"LOOP"};
    // Adds stop button
    juce::TextButton stopButton{"STOP"};
    // Adds load button
    juce::TextButton loadButton{"LOAD"};
    
    // A slider to control the volume.
    juce::Slider volSlider;
    // A slider to control the playback speed of the audio file.
    juce::Slider speedSlider;
    // A slider to control the playback possition of the audio file.
    juce::Slider posSlider;

    //  A label for the speed, volume and possition slider.
    juce::Label speedSliderLabel;
    juce::Label volSliderLabel;
    juce::Label posSliderLabel;

    // A pointer to the audio player object.
    DJAudioPlayer* player;

    // A waveform display for the audio file.
    WaveformDisplay waveformDisplay;
    // Function to load an audio file into the deck.
    void loadFile(juce::URL audioURL);
    // class declares that the PlaylistComponent class is a friend of the DeckGUI class. 
    // Means that the PlaylistComponent class can access the private members of the DeckGUI class.
    friend class PlaylistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
