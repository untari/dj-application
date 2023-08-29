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

    //implement button listener
    void buttonClicked(juce::Button *) override;
    //implement slider listener
    void sliderValueChanged(juce::Slider *slider) override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void timerCallback() override;
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                            const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

private:

    int id;
    
    juce::LookAndFeel_V4 otherLookAndFeel;
    juce::TextButton playButton{"PLAY"};
    // add loop button
    juce::ToggleButton loopButton{"LOOP"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    juce::Label speedSliderLabel;
    juce::Label volSliderLabel;
    juce::Label posSliderLabel;

    DJAudioPlayer* player;

    WaveformDisplay waveformDisplay;
    
    void loadFile(juce::URL audioURL);
    
    friend class PlaylistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
