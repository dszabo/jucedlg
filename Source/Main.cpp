#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

class DlgTestApplication  : public JUCEApplication
{
public:
    DlgTestApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        mainWindow = new MainWindow();
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..
        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
    }

    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow()  : DocumentWindow ("MainWindow",
                                        Colours::darkgrey,
                                        DocumentWindow::allButtons)
        {
            setContentOwned (new MainContentComponent(), true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed()
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (DlgTestApplication)
