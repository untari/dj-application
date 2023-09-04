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

// Creates a new TrackPlaylist object with the file's name and URL.
TrackPlaylist::TrackPlaylist(juce::File _file): file(_file),
                                title(_file.getFileNameWithoutExtension()),
                                URL(juce::URL{ _file})
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    DBG("Created new track with title: " <<title);
}

// Compares two TrackPlaylist objects and returns true if they have the same title.
bool TrackPlaylist::operator==(const juce::String& other) const
{
  // Returns true if the title of the first TrackPlaylist object is equal to the title of the second TrackPlaylist object.
    return title == other;
}