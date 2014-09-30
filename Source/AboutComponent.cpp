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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "AboutComponent.h"



//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AboutComponent::AboutComponent ()  
{
    //interop = new NSInterop();
    //addAndMakeVisible (label = new Label ("new label",
    //                                      TRANS("label text")));
    //label->setFont (Font (15.00f, Font::plain));
    //label->setJustificationType (Justification::centredLeft);
    //label->setEditable (false, false, false);
    //label->setColour (TextEditor::textColourId, Colours::black);
    //label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButton = new TextButton ("Install to selected"));
    textButton->setBounds(10, 230, 120, 20);
    textButton->addListener (this);

    //[UserPreSize]
    //[/UserPreSize]

    interop.startMetadataQuery(this);
    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AboutComponent::~AboutComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    textButton = nullptr;
    //delete interop;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}


void AboutComponent::metadataNotificationCompleted(OwnedArray<SearchResult> &resultArray)
{
    grid = new CustomGridModel(resultArray);
    
    table.setModel(grid);
    table.getHeader().addColumn(L"Bundle Identifier", 1, 120);
    table.getHeader().addColumn(L"Bundle Path", 2, 330);
    table.getHeader().addColumn(L"Version", 3, 70);
    // give it a border
    table.setColour (ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness (1);
    table.setBounds(10, 10, 550, 200);
    addAndMakeVisible(table);

}


//==============================================================================
void AboutComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AboutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        
        //interop.nsLog(String(table.getSelectedRow()));
        if (table.getSelectedRow() >= 0) {
            interop.nsLog(((CustomGridModel *)table.getModel())->items[table.getSelectedRow()]->getBundlePath());
        }
        //[/UserButtonCode_textButton]
        
        
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AboutComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="200">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="27b70091760d3887" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="label text" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="5d42b34db405b86a" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="240 160 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
