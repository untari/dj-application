/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 23 Aug 2023 11:06:30am
    Author:  bichito

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");

    tableComponent.getHeader().addColumn("Track title", 0, 400);
    tableComponent.getHeader().addColumn("", 1, 200);
    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}

int PlaylistComponent::getNumRows()
{
  return trackTitles.size();
}

void PlaylistComponent::paintRowBackground (juce::Graphics & g, 
                      int rowNumber, 
                      int width, 
                      int height, 
                      bool rowIsSelected)
{
  if(rowIsSelected)
  {
    g.fillAll(juce::Colours::orange);
  }
  else{
    g.fillAll(juce::Colours::darkgrey);
  }
}
void PlaylistComponent::paintCell (juce::Graphics & g, 
                      int rowNumber,
                      int columnId,
                      int width,
                      int height,
                      bool rowIsSelected)
{
  g.drawText(trackTitles[rowNumber], 
            2, 0, 
            width - 4, height, 
            juce::Justification::centredLeft, 
            true);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

juce::Component*  PlaylistComponent::refreshComponentForCell (int rowNumber,
                          int columnId,
                          bool isRowSelected,
                          Component *existingComponentToUpdate)
{
  if(columnId == 1)
  {
    if(existingComponentToUpdate == nullptr)
    {
      juce::TextButton* btn = new juce::TextButton{"play"};
      btn -> addListener(this);
      existingComponentToUpdate = btn;
    }
  }
  return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
  std::cout << "PlaylistComponent::buttonClicked" << std::endl;
}