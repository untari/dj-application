/*
  ==============================================================================

    DeckGUI.cpp
    Created: 4 Aug 2023 4:06:27pm
    Author:  bichito

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,  
    juce::AudioFormatManager &formatManagerToUse, 
    juce::AudioThumbnailCache &cacheToUse) : player(_player), 
                                             waveformDisplay(formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // configures volume & speed sliders to have a rotary knob appearance
    // also applying a custom look and feel for interection behaviour
    setLookAndFeel (&otherLookAndFeel);
    volSlider.setLookAndFeel (&otherLookAndFeel);
    speedSlider.setLookAndFeel (&otherLookAndFeel);
    volSlider.setSliderStyle (juce::Slider::Rotary);
    volSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    speedSlider.setSliderStyle (juce::Slider::Rotary);
    speedSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(playButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(speedSliderLabel);
    addAndMakeVisible(volSliderLabel);
    addAndMakeVisible(posSliderLabel);

    playButton.addListener(this);
    loopButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.00);
    posSlider.setRange(0.0, 1.0);

    //attaching text to the volume slider component
    volSliderLabel.setText("Volume", juce::NotificationType::dontSendNotification);
    volSliderLabel.attachToComponent(&volSlider, false);

    //attaching text to the volume speed slider component
    speedSliderLabel.setText("Speed", juce::NotificationType::dontSendNotification);
    speedSliderLabel.attachToComponent(&speedSlider, false);

    //attaching text to the volume speed slider component
    posSliderLabel.setText("Pos slider", juce::NotificationType::dontSendNotification);
    posSliderLabel.attachToComponent(&posSlider, false);

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
    //
    setLookAndFeel (nullptr);
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::red);
    g.setFont (14.0f);
    g.drawText ("Volume & Speed & Position", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    g.setColour (juce::Colours::slategrey);
    auto centralArea = getLocalBounds().toFloat().reduced(10.0f);
    g.drawRoundedRectangle (centralArea, 5.0f, 3.0f);
    
    juce::Array<juce::Colour> colours{ juce::Colours::slategrey, juce::Colours::slategrey, juce::Colours::slategrey
    };
    
    auto colourBarArea = centralArea.reduced(4.0f).withHeight(275.0f);
        
    auto colourArea= colourBarArea.withWidth(colourBarArea.getWidth()/colours.size());
    
    for (auto colour : colours)
    {
        g.setColour (colour);
        g.fillRect (colourArea);
        colourArea.translate (colourArea.getWidth(), 0.0f);
    }
}	

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight()/10;

    playButton.setBounds(rowH, rowH*9, getWidth()/6, rowH);
    loadButton.setBounds(rowH*4, rowH*9, getWidth()/6, rowH);
    stopButton.setBounds(rowH*7, rowH*9, getWidth()/6, rowH);
    loopButton.setBounds(rowH*10, rowH*9, getWidth()/6, rowH);

    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);

    waveformDisplay.setBounds(0, rowH*5, getWidth(), rowH*3);
    posSlider.setBounds(rowH*2,rowH*4, getWidth(), rowH);

    auto border = 4;

    auto area = getLocalBounds();

    auto dialArea = area.removeFromTop (area.getHeight() / 3);

    volSlider.setBounds (dialArea.removeFromLeft (dialArea.getWidth() / 2).reduced (border));
    speedSlider.setBounds (dialArea.reduced (border));

    // position for the labels
    volSliderLabel.setCentreRelative(0.42f, 0.15f);
    speedSliderLabel.setCentreRelative(0.93f, 0.14f);
    posSliderLabel.setCentreRelative(0.66f, 0.40f);
}

void DeckGUI::buttonClicked (juce::Button* button)
{
    if(button == &playButton)
    {
        std::cout << "button was clicked" << std::endl;
        player->start();
        repaint();
    }
    if(button == &stopButton)
    {
        std::cout << "stop was clicked" << std::endl;
        player->stop(); 
        repaint();
    }
    if(button == &loadButton)
    {
        // to open file browser
        juce::FileChooser chooser{"select a file.."};
        if(chooser.browseForFileToOpen())
        {
            player->loadURL(juce::URL{chooser.getResult()});
            waveformDisplay.loadURL(juce::URL{chooser.getResult()});
        }   
        repaint();
    }
}

void DeckGUI::sliderValueChanged (juce::Slider *slider)
{
    if(slider == &volSlider)
    {
        player->setGain(slider -> getValue());
    }
    if(slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if(slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag (const juce::StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFIleDrag" << std::endl;
    return true;
}
void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if(files.size() == 1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}

void DeckGUI::timerCallback()
{
    std::cout << "DeckGUI::timerCallback" << std::endl;
    // if loop button is clicked
    // and if the position more than 1. it is the end of the audio
    if (std::to_string(loopButton.getToggleState()) == "1") { 
        if (player->getPositionRelative() >= 1) {
            // Sets position back to the start of the audio file
            player->setPositionRelative(0);
            // Plays the audio
            player->start(); 
        }
    }
    // if loop button is not clicked
    // and the position more than 1. end of the audio
    if (std::to_string(loopButton.getToggleState()) == "0") {
        if (player->getPositionRelative() >= 1) { 
            // sets position back to the start of the audio
            player->setPositionRelative(0);
            // sets position back to the start of the audio file
            player->stop();
        }
    }
    // every 100ms, updates the waveform to show current timestamp for the audio
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)

{
 
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.1f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    // fill
    g.setColour (juce::Colours::orange);
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::red);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
    
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));

    // pointer
    g.setColour (juce::Colours::yellow);
    g.fillPath (p);
}

void DeckGUI::loadFile(juce::URL audioURL)
{
    DBG("DeckGUI::loadFile called");
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}