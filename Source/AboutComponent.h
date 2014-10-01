#ifndef __JUCE_HEADER_6F5BC92BB0597534__
#define __JUCE_HEADER_6F5BC92BB0597534__

#include "../JuceLibraryCode/JuceHeader.h"
#include "NSInterop.h"
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
    void metadataNotificationCompleted(OwnedArray<SearchResult> &resultArray);

private:
    ScopedPointer<Label> label;
    ScopedPointer<TextButton> textButton;
    NSInterop interop;
    ScopedPointer<CustomGridModel> grid;
    TableListBox table;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutComponent)
};

#endif   // __JUCE_HEADER_6F5BC92BB0597534__
