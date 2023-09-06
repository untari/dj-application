/*
  ==============================================================================

    PlaylistComponent.h
    Created: 23 Aug 2023 11:06:30am
    Author:  bichito

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <fstream>
#include "TrackPlaylist.h"
#include "DeckGUI.h"
#include <algorithm>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::TextEditor::Listener
{
  public:
    PlaylistComponent(DJAudioPlayer* _playerForPlaylist,
                      DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2);

    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    // method that returns the number of rows.
    int getNumRows() override;
    // draw the background of a row in the PlaylistComponent object.

    void paintRowBackground (juce::Graphics &,
                          int rowNumber, 
                          int width, 
                          int height, 
                          bool rowIsSelected) override;

    // Draw a cell.
    void paintCell (juce::Graphics &, 
                          int rowNumber,
                          int columnId,
                          int width,
                          int height,
                          bool rowIsSelected) override;

    // Refresh the content of a cell.
    juce::Component* refreshComponentForCell (
                                      int rowNumber,
                                      int columnID,
                                      bool isRowSelected,
                                      juce::Component *existingComponentToUpdate) override;

    // Method is called when button is clicked.
    void buttonClicked(juce::Button* button) override;

    // Object will be used to store the XML data for the playlist.
    std::unique_ptr<juce::XmlElement> sampleData;
    // To store the list of columns and data list in the playlist.
    juce::XmlElement* columnList = nullptr;
    juce::XmlElement* dataList = nullptr;
    // Integer that stores the number of rows in the playlist.
    int numRows = 0;

  private:

    // Vector of the TrackPlaylist.
    std::vector<TrackPlaylist> tracks;
    // Display a list of audio files.
    juce::TableListBox library;
    // Search for audio files in the library.
    juce::TextEditor searchBox;
    // Display the list of tracks in the playlist.
    juce::TableListBox tableComponent;
    // Vector that will store the titles of the tracks playlist.
    std::vector<std::string> trackTitles;
    // Font size for the text in playlist.
    juce::Font font  { 14.0f };
    // Play the tracks in the playlist.
    DJAudioPlayer* playerForPlaylist;
    // Control the playback of the tracks in the playlist.
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    // Add tracks to the decks, add tracks to the playlist, and import tracks from a file.
    juce::TextButton addToPlayer1 {"Add to the left deck"};
    juce::TextButton addToPlayer2 {"Add to the right deck"};
    juce::TextButton importButton{"Import Tracks"};

    // Import audio files into the library.
    void importToLibrary();
    // Used to save the library to a file.
    void saveLibrary();
    // Load the library from a file.
    void loadLibrary();
    // Delete a track from the library.
    void deleteFromTracks(int id);
    
    // Get the length of an audio file.
    juce::String getLength(juce::URL audioURL);
    // Convert second to minutes.
    juce::String secondsToMinutes(double seconds);
    
    // Check if the tracks is in the library.
    bool isInTheTracks(juce::String fileNameWithoutExtension);
    // Get\ the index of a track in the library.
    int whereInTheTracks(juce::String searchText);
    // Load a track into a deck.
    void loadInPlayer(DeckGUI* deckGUI);
    // Search the library for tracks.
    void searchLibrary(juce::String searchText);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};