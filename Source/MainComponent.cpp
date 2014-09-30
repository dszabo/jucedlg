/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "FloatingToolWindow.h"


//==============================================================================
MainContentComponent::MainContentComponent() : buttonShow(L"Click me")
{
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeelV3);
	buttonShow.setBounds(10, 10, 80, 30);
	buttonShow.addListener(this);
	addAndMakeVisible(buttonShow);

    setSize (500, 400);
}

MainContentComponent::~MainContentComponent() 
{

}

void MainContentComponent::buttonClicked(Button* button)
{

	showToolWindow(aboutComponent);

}

void MainContentComponent::showToolWindow(ScopedPointer<Component>& ownerPointer)
{
	if (ownerPointer != nullptr)
	{
		ownerPointer->toFront(true);
	}
	else
	{
		new FloatingToolWindow("Plugin Installer",
			"",
			new AboutComponent(), ownerPointer,
			600, 300,
			600, 300, 600, 300);
	}
}


void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
