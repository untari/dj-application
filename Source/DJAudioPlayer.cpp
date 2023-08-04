/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 3 Aug 2023 4:57:51pm
    Author:  bichito

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer()
{

}
DJAudioPlayer::~DJAudioPlayer()
{

}
//==============================================================================
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
  formatManager.registerBasicFormats();
  transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate)
}
void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
  transportSource.getNextAudioBlock(bufferToFill);
}
void DJAudioPlayer::releaseResources()
{
  transportSource.releaseResources();
}

// function that allow us to control it
void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {      
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader,
            true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());         
    }
}
void DJAudioPlayer::setGain(double gain)
{

}
void DJAudioPlayer::setSpeed(double ratio)
{

}
void DJAudioPlayer::setPosition(double posInSecs)
{

}

void DJAudioPlayer::start()
{

}
void DJAudioPlayer::stop()
{
  
}