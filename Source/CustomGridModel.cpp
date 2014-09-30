//
//  CustomGridModel.cpp
//  JuceTable
//
//  Created by Daniel Szabo on 30/09/14.
//
//

#include "CustomGridModel.h"

CustomGridModel::CustomGridModel(int rows) : numOfRows(rows)
{
    
    
}

CustomGridModel::CustomGridModel(OwnedArray<SearchResult> &resultArray)
{
    numOfRows = resultArray.size();
    items.addCopiesOf(resultArray);
}

CustomGridModel::~CustomGridModel()
{
    
}

void CustomGridModel::metadataNotificationCompleted(const juce::String &result)
{
    numOfRows = result.length();
}

int CustomGridModel::getNumRows()
{
    return numOfRows;
}

void CustomGridModel::paintCell(juce::Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (Colours::black);
    Font font = 12.0f;
    g.setFont (font);
    
    String text;
    if (columnId == 1)
    {
        text= items[rowNumber]->getBundleIdentifier();
    }

    if (columnId == 2)
    {
        text= items[rowNumber]->getBundlePath();
    }
    
    g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
    g.setColour (Colours::black.withAlpha (0.2f));
    g.fillRect (width - 1, 0, 1, height);
    
}

void CustomGridModel::paintRowBackground(juce::Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.fillAll (Colours::yellow);
    } else {
        g.fillAll (Colours::lightgrey);
    }
}
