#ifndef __JUCE_HEADER_6F5BC92BB0597534__
#define __JUCE_HEADER_6F5BC92BB0597534__

#include "../JuceLibraryCode/JuceHeader.h"
#ifdef JUCE_MAC
#include "NSInterop.h"
#endif
#include "CustomGridModel.h"
#include "SearchResult.h"

class AboutComponent  : public juce::Component,
                        public ButtonListener
{
public:
    AboutComponent ();
    ~AboutComponent();
    void paint (Graphics& g);
    void buttonClicked (Button* buttonThatWasClicked);
#ifdef JUCE_MAC
    void metadataNotificationCompleted(OwnedArray<AppSearchResult> &resultArray);
#endif

private:
#ifdef JUCE_MAC
    NSInterop interop;
#endif
    ScopedPointer<Label> label;
    ScopedPointer<TextButton> textButton;
    ScopedPointer<CustomGridModel> grid;
    TableListBox table;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutComponent)
};

#endif   // __JUCE_HEADER_6F5BC92BB0597534__
