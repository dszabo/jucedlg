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
			500, 300,
			400, 200, 500, 300);
	}
}


void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffeeddff));

    g.setFont (Font (16.0f));
    g.setColour (Colours::black);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
