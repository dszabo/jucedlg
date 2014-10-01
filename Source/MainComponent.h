#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AboutComponent.h"

class MainContentComponent   : public Component, public ButtonListener
{
public:
    MainContentComponent();
    ~MainContentComponent();
    void paint (Graphics&);
    void resized();
	void buttonClicked(Button* button);
	void showToolWindow(ScopedPointer<Component>& ownerPointer);

private:
	LookAndFeel_V3 lookAndFeelV3;
    TextButton buttonShow;
	ScopedPointer<Component> aboutComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

#endif  // MAINCOMPONENT_H_INCLUDED
