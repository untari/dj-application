/*
  ==============================================================================

    TrackPlaylist.cpp
    Created: 26 Aug 2023 3:17:59pm
    Author:  bichito

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackPlaylist.h"
#include <filesystem>

//==============================================================================
TrackPlaylist::TrackPlaylist(juce::File _file): file(_file),
                                title(_file.getFileNameWithoutExtension()),
                                URL(juce::URL{ _file})
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    DBG("Created new track with title: " <<title);
}

bool TrackPlaylist::operator==(const juce::String& other) const
{
    return title == other;
}