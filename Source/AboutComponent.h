/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_6F5BC92BB0597534__
#define __JUCE_HEADER_6F5BC92BB0597534__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "NSInterop.h"
#include "CustomGridModel.h"
#include "SearchResult.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/

class AppTable : public juce::Component, public TableListBoxModel
{
public:
    AppTable()
    {
        numRows = 3;
        addAndMakeVisible (table);
        table.setModel (this);
        
        // give it a border
        table.setColour (ListBox::outlineColourId, Colours::grey);
        table.setOutlineThickness (1);
        
        table.getHeader().addColumn(L"col1", 1, 30);
        table.getHeader().addColumn(L"col2", 2, 30);
        
    }
    
    // This is overloaded from TableListBoxModel, and must return the total number of rows in our table
    int getNumRows() override
    {
        return numRows;
    }

    // This is overloaded from TableListBoxModel, and should fill in the background of the whole row
    void paintRowBackground (Graphics& g, int /*rowNumber*/, int /*width*/, int /*height*/, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll (Colours::lightblue);
    }

    // This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
    // components.
    void paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool /*rowIsSelected*/) override
    {
        g.setColour (Colours::black);
        //g.setFont (font);
    
        //const XmlElement* rowElement = dataList->getChildElement (rowNumber);
    
        const String text (L"Hello");
        g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
    
        g.setColour (Colours::black.withAlpha (0.2f));
        g.fillRect (width - 1, 0, 1, height);
    }
private:
    TableListBox table;     // the table component itself
    int numRows;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppTable)
};


class AboutComponent  : public juce::Component,
                        public ButtonListener
{
public:
    //==============================================================================
    AboutComponent ();
    ~AboutComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void buttonClicked (Button* buttonThatWasClicked);
    //void metadataNotificationCompleted(const int resultCount);
    void metadataNotificationCompleted(const String &result);
    void metadataNotificationCompleted(OwnedArray<SearchResult> &resultArray);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label;
    ScopedPointer<TextButton> textButton;
    NSInterop interop;
    ScopedPointer<CustomGridModel> grid;
    TableListBox table;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AboutComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_6F5BC92BB0597534__
