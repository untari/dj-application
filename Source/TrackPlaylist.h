/*
  ==============================================================================

    TrackPlaylist.h
    Created: 26 Aug 2023 3:17:59pm
    Author:  bichito

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class TrackPlaylist
{
  public:
    TrackPlaylist(juce::File _file);
    // Variable stores the file for the track.
    juce::File file;
    // Stores the URL, title and length.
    juce::URL URL;
    juce::String title;
    juce::String length;
    // Compare two TrackPlaylist objects.
    bool operator==(const juce::String& other)const;
};