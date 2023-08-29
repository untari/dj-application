/*
  ==============================================================================

    TrackPlaylist.h
    Created: 26 Aug 2023 3:17:59pm
    Author:  bichito

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TrackPlaylist
{
  public:
      TrackPlaylist(juce::File _file);
        juce::File file;
        juce::URL URL;
        juce::String title;
        juce::String length;
        bool operator==(const juce::String& other)const;
};