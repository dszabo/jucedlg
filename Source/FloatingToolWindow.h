#ifndef FLOATINGTOOLWINDOW_H_INCLUDED
#define FLOATINGTOOLWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class FloatingToolWindow : public DialogWindow
{
public:
	FloatingToolWindow(const String& title,
		const String& windowPosPropertyName,
		Component* content,
		ScopedPointer<Component>& ownerPointer,
		int defaultW, int defaultH,
		int minW, int minH,
		int maxW, int maxH)
		: DialogWindow(title, Colours::darkgrey, true, true),
		windowPosProperty(windowPosPropertyName),
		owner(ownerPointer)
	{
		setContentOwned(content, false);
		centreAroundComponent(Component::getCurrentlyFocusedComponent(), defaultW, defaultH);
		setVisible(true);
		owner = this;
	}

	~FloatingToolWindow()
	{
		
	}

	void closeButtonPressed() override
	{
		owner = nullptr;
	}

private:
	String windowPosProperty;
	ScopedPointer<Component>& owner;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FloatingToolWindow)
};
#endif