//
//  CustomGridModel.h
//  JuceTable
//
//  Created by Daniel Szabo on 30/09/14.
//
//

#ifndef __JuceTable__CustomGridModel__
#define __JuceTable__CustomGridModel__

#include "NSInterop.h"
#include "SearchResult.h"
#include "../JuceLibraryCode/JuceHeader.h"


class CustomGridModel :
public TableListBoxModel
{
public:
    int getNumRows();
    CustomGridModel(int rows);
    CustomGridModel(OwnedArray<SearchResult> &resultArray);
    ~CustomGridModel();
    void paintRowBackground (Graphics& g,
                             int rowNumber,
                             int width, int height,
                             bool rowIsSelected);
    
    void paintCell (Graphics& g,
                    int rowNumber,
                    int columnId,
                    int width, int height,
                    bool rowIsSelected) ;
    
    void metadataNotificationCompleted(const String &result);
    
    OwnedArray<SearchResult> items;

    
    
private:
    int numOfRows;
    
    
};

#endif /* defined(__JuceTable__CustomGridModel__) */
