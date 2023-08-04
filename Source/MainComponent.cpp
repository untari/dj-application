#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    
    phase = 0.0;
    dphase = 0.0001;
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // transportSource.getNextAudioBlock(bufferToFill);
    player1.getNextAudioBlock(bufferToFill);
}

// void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
// {
//     // Your audio-processing code goes here!

//     // For more details, see the help for AudioProcessor::getNextAudioBlock()

//     // Right now we are not producing any data, in which case we need to clear the buffer
//     // (to prevent the output of random noise)

//     // get access to buffer
//     auto* leftChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
//     auto* rightChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    
//     //fill up with samples using for loop
//     for(auto i=0; i < bufferToFill.numSamples; ++i)
//     {
//         //generate random number
//         // double sample = rand.nextDouble() * 0.25;

//         double sample = sin(phase) * 0.1;
//         leftChan[i] = sample;
//         rightChan[i] = sample;

//         // when generate a sample, increase the phase 
//         phase += dphase;

//     }
//     // bufferToFill.clearActiveBufferRegion();
// }

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    double rowH = getHeight()/5;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0,  rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0,  rowH * 3, getWidth(), rowH);
    loadButton.setBounds(0,  rowH * 4, getWidth(), rowH);
}


void MainComponent::buttonClicked (juce::Button* button)
{
    if(button == &playButton)
    {
        std::cout << "button was clicked" << std::endl;
        transportSource.start(); 
    }
    if(button == &stopButton)
    {
        std::cout << "stop was clicked" << std::endl;
        transportSource.stop(); 
    }
    if(button == &loadButton)
    {
        // to open file browser
        juce::FileChooser chooser{"select a file.."};
        if(chooser.browseForFileToOpen())
        {
            loadURL(juce::URL{chooser.getResult()});
        }
    }
}

void MainComponent::sliderValueChanged (juce::Slider *slider)
{
    if(slider == &volSlider)
    {
        transportSource.setGain(slider->getValue());
    }
    if(slider == &speedSlider)
    {
        resampleSource.setResamplingRatio(slider->getValue());
    }
}

void MainComponent::loadURL(juce::URL audioURL)
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