/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 23 Aug 2023 11:06:30am
    Author:  bichito

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include <vector>
#include "DJAudioPlayer.h"
#include <fstream>
#include "TrackPlaylist.h"
#include "DeckGUI.h"
#include <algorithm>

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _playerForPlaylist,
                                     DeckGUI* _deckGUI1,
                                     DeckGUI* _deckGUI2
                                     ):playerForPlaylist(_playerForPlaylist),
                                    deckGUI1(_deckGUI1),
                                    deckGUI2(_deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(tableComponent);
    addAndMakeVisible(importButton);
    addAndMakeVisible(library);
    addAndMakeVisible(addToPlayer1);
    addAndMakeVisible(addToPlayer2);
    addAndMakeVisible(searchBox);
    
    // Adds a button that will be used to import data from a file.
    importButton.addListener(this);
    // Adds a table that will be used to display data.
    tableComponent.setModel(this);
    // Adds a search box that will be used to filter data.
    searchBox.addListener(this);
    // Adds two buttons that will be used to add a player to the first player & second player.
    addToPlayer1.addListener(this);
    addToPlayer2.addListener(this);
  
    // Sets the text that will be displayed in the search box when it is empty.
    searchBox.setTextToShowWhenEmpty("Search title of the music above and click Enter!",
                                     juce::Colours::white);
    // Sets the event handler that will be called when the user presses the Enter key.
    searchBox.onReturnKey = [this]{searchLibrary (searchBox.getText());};

    // Adds a column to the table header with the name "Tracks" and the column ID 1, width set to 1.
    library.getHeader().addColumn("Tracks", 1, 1);
    // Adds a column to the table header with the name "Length" and the column ID 2, width set to 1.
    library.getHeader().addColumn("Length", 2, 1);
    library.getHeader().addColumn("", 3, 1);
    // Add sets of table.The table will use the current object to get its data.
    library.setModel(this);
    //  Loads the library data into the table's model. 
    loadLibrary();
}

PlaylistComponent::~PlaylistComponent()
{
    // Saves the library data to a file.
    saveLibrary();
}

// The method returns the number of rows in the playlist.
int PlaylistComponent::getNumRows()
{
  return tracks.size();
}

void PlaylistComponent::paintRowBackground (juce::Graphics & g, 
                      int rowNumber, 
                      int width, 
                      int height, 
                      bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::whitesmoke);
    }
    else{
        g.fillAll(juce::Colours::slategrey);
    }
}
void PlaylistComponent::paintCell (juce::Graphics & g, 
                      int rowNumber,
                      int columnId,
                      int width,
                      int height,
                      bool rowIsSelected)
{
  if(rowNumber < getNumRows())
  {
    if(columnId==1)
    {
        g.drawText(tracks[rowNumber].title,
                    2, 0,
                    width-4, height,
                    juce::Justification::centredLeft,
                    true
                    );
    }
    if(columnId ==2)
    {
    g.drawText(tracks[rowNumber].length,
                    2, 0, 
                    width - 4, height,
                    juce::Justification::centred,
                    true);
    }
  }
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    // clear the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    // draw an outline around the component
    g.drawRect (getLocalBounds(), 1);
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    // draw some placeholder text
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    tableComponent.setBounds(0, 0, getWidth(), getHeight());
    importButton.setBounds(0, 0, getWidth(), getHeight() / 10);
    library.setBounds(0, 1 * getHeight() / 10, getWidth(), 13 * getHeight() / 10);
    searchBox.setBounds(0, 13 * getHeight() / 16, getWidth(), 1.5*getHeight() / 16);
    addToPlayer1.setBounds(0, 14 * getHeight() / 16, getWidth() /2 , 2*getHeight() / 16);
    addToPlayer2.setBounds(getWidth() / 2, 14 * getHeight() / 16, getWidth() / 2, 2*getHeight() / 16);
    //set columns library
    library.getHeader().setColumnWidth(1, 12.8 * getWidth() / 20);
    library.getHeader().setColumnWidth(2, 5 * getWidth() / 20);
    library.getHeader().setColumnWidth(3, 2 * getWidth() / 20);
}

juce::Component* PlaylistComponent::refreshComponentForCell (
                                    int rowNumber,
                                    int columnId,
                                    bool isRowSelected,
                                    juce::Component *existingComponentToUpdate)
{
    // Checks if the column ID is 3.
    if(columnId ==3)
    {
        // if yes, creates a new text button with the label "Delete".
        if(existingComponentToUpdate == nullptr)
        {
            // Text button is stored in the variable btn.
            juce::TextButton*btn = new juce::TextButton{"Delete"};
            // Creates a unique ID for the text button based on the row number.
            // The rowNumber is passsed to the string function which converts it to string.
            // Then the string stored in the variable id.
            juce::String id{std::to_string(rowNumber)};
            // Sets the text button's ID to the value of the variable id.
            btn->setComponentID(id);
            // Adds the text button's as a listener to the current object.
            btn->juce::Button::addListener(this);
            // Sets the text button's colour.
            btn->setColour(juce::TextButton::buttonColourId, juce::Colours::slateblue);
            // Assigns the text button to the variable of existingComponentToUpdate.
            existingComponentToUpdate = btn;
        }
    }
    // If not return existingComponentToUpdate.
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if(button ==& importButton)
    {
        std::cout << "Load button and clicked " << std::endl;
        // Import tracks into library.
        importToLibrary();
        // Updates the library content. Then index the tracks so can be searched.
        library.updateContent();
    }
    else if (button == & addToPlayer1)
    {
        std::cout <<"Add to player 1 clicked" << std::endl;
        loadInPlayer(deckGUI1);
        
    }
    else if(button == & addToPlayer2)
    {
        std::cout << "add to player 2 clicked" << std::endl;
        loadInPlayer(deckGUI2);
    }
    else {
        int id = std::stoi(button->getComponentID().toStdString());
        DBG(tracks[id].title + " track removed from library ");
        deleteFromTracks(id);
        library.updateContent();
    }
}

// This function allows the user to import audio files into the playlist.
void PlaylistComponent::importToLibrary()
{
    std::cout << "PlaylistComponent::importToLibrary called" << std::endl;

    //initialize file chooser
    juce::FileChooser chooser{ "Select files" };
    if (chooser.browseForMultipleFilesToOpen())
    {
        // If the user has selected one or more audio files, the code will be executed.
        for (const juce::File& file : chooser.getResults())
        {
            // Gets the file name without the extension. 
            juce::String fileNameWithoutExtension{ file.getFileNameWithoutExtension() };
            // Checks if the audio file is already in the playlist.
            if (!isInTheTracks(fileNameWithoutExtension)) 
            {
                // creates a new TrackPlaylist object for the audio file.
                TrackPlaylist newTrack{ file };
                // Gets the URL of the audio file.
                juce::URL audioURL{ file };
                // Gets length of the audio. The duration of the audio file in seconds.
                newTrack.length = getLength(audioURL) ;
                // Adds the playlist of TrackPlaylist objects.
                tracks.push_back(newTrack);
                // Check if the file has been loaded.
                std::cout << "loaded file: " << newTrack.title << std::endl;
            }
            // display info message
            else 
            {
                // Alert message to show if the file already loaded.
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
                    "Load information:",
                    fileNameWithoutExtension + " already loaded",
                    "OK",
                    nullptr
                );
            }
        }
    }
}

// Takes a juce::URL object as input and returns the length of the audio file in minutes.
juce::String PlaylistComponent::getLength(juce::URL audioURL)
{
    // Loads the audio file.
    playerForPlaylist->loadURL(audioURL);
    // Gets the length of the audio file in seconds.
    double seconds{playerForPlaylist->getLengthInSeconds()};
    //  Converts the length from seconds to minutes.
    juce::String minutes{secondsToMinutes(seconds)} ;
    return minutes;
}

// Takes a double value as input and returns a juce::String object.
juce::String PlaylistComponent::secondsToMinutes(double seconds)
{
    // Rounds the number of seconds.
    int secondsRounded{ int (std::round(seconds))} ;
    //  The minutes are stored in the min variable
    juce::String min{ std::to_string(secondsRounded /60 )};
    // The seconds are stored in the sec variable. 
    juce::String sec{std::to_string(secondsRounded %60)};
    // If its length is less than 2, is padded.
    if(sec.length() < 2)
    {
        sec = sec.paddedLeft('0', 2);
    }

    return juce::String{ min + ":" + sec } ;
}

// Function to check if the file name already in the playlist.
bool PlaylistComponent::isInTheTracks(juce::String fileNameWithoutExtension)
{
    // Search the tracks list for the file name.
    return(std::find(tracks.begin(),tracks.end(),
                     fileNameWithoutExtension) != tracks.end());
}

//  The function saves the playlist to a CSV file.
void PlaylistComponent::saveLibrary()
{
    std::ofstream myLibrary("My-library.csv");
    // Loops through the tracks list.
    for(TrackPlaylist& trackList: tracks)
    {
        // Gets the file name, the length and writes it into myLibrary oject.
        myLibrary <<trackList.file.getFullPathName()<< "," <<trackList.length<< "\n";
    }
}

// The function loads the playlist from a CSV file.
void PlaylistComponent::loadLibrary()
{
    // Creates an input file stream object.
    std::ifstream myLibrary("My-library.csv");
    // Create an objects.
    std::string filePath;
    std::string length;
    
    // If the myLibrary object is open do.
    if( myLibrary.is_open())
    {
        // Gets the file path from the myLibrary object.
        while(getline(myLibrary, filePath, ',')) {
            // Creates an object from the file path.
            juce::File file{ filePath };
            // Creates a TrackPlaylist object from the juce::File object.
            TrackPlaylist newTrack{ file };
            // Gets length of the track from myLibrary.
            getline(myLibrary, length);
            newTrack.length = length;
            // Adds the TrackPlaylist object to the tracks list.
            tracks.push_back(newTrack);
        }
    }
    // Close the library object.
    myLibrary.close();
}

// The function that deletes a track from the tracks list.
void PlaylistComponent::deleteFromTracks(int id)
{
    // Remove the track from the list.
    tracks.erase(tracks.begin() + id);
}

// Function to search the tracks playlist.
int PlaylistComponent::whereInTheTracks(juce::String searchText)
{
    // Find the first track in the tracks list whose title contains the search text.
    auto it= find_if(tracks.begin(), tracks.end(),
                    [&searchText](const TrackPlaylist& obj) {return obj.title.contains(searchText);});
    // Defines the i variable and initializes it to -1.
    int i=-1;
    //  Iterate to the first track that matches the predicate function. 
    if( it != tracks.end())
    {
        // Use the distance() function to calculate the distance between the beginning of the list and the it variable.
        i = std::distance(tracks.begin(), it);
    }
    return  i;
}

//  Function is responsible for adding a selected track to deck represented by the deckGUI object.
void PlaylistComponent::loadInPlayer(DeckGUI* deckGUI)
{
    // Retrieves the selected row index from library object and store it in the variable.
    int selectedRow{ library.getSelectedRow() };
    // If selectedRow not equal to -1, means that a row in the playlist has been selected.
    if ( selectedRow != -1)
    {
        DBG("Adding: " <<tracks[selectedRow].title<<" to player ");
        // Call te loadFile on the deckGUI object, passing the URL of the selected tracks as an argrument.
        deckGUI->loadFile(tracks[selectedRow].URL);
    }
    // If selectedRow equal to -1, means no track selected. Display the alert window.
    else
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
                                        "Add to decks",
                                        "Please selecte a track to add to decks ",
                                        "Ok",
                                        nullptr);
    }
}

// The function prints a message to the debug console that the library is being searched for the track with the title searchText.
void PlaylistComponent::searchLibrary(juce::String searchText){
    DBG("search library for the track :" <<searchText);
    //  Checks if the search text is empty. If not empty, do.
    if ( searchText !="")
    {
        // Calls the whereInTheTracks() method to find the row number of the track with the title searchText in the tracks array.
        int rowNumber = whereInTheTracks(searchText);
        library.selectRow(rowNumber);
    }
    else
    {
        // Deselect all rows in the library.
        library.deselectAllRows();
    }
}