//
//  NSInterop.cpp
//  DlgTest
//
//  Created by Daniel Szabo on 30/09/14.
//
//

#import <Cocoa/Cocoa.h>
#include "NSInterop.h"
#include "AboutComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"


static juce::String nsStringToJuce(NSString* s)
{
    return CharPointer_UTF8([s UTF8String]);
}

class NSInterop::Private
{
public:
    NSMetadataQuery *query;
};

NSInterop::NSInterop()
{
    pimpl = new Private();
    pimpl->query = [[NSMetadataQuery alloc] init];
}

NSInterop::~NSInterop()
{
    pimpl->query = nil;
}

void NSInterop::startMetadataQuery(AboutComponent* nativeClass)
{
    [pimpl->query setSearchScopes:@[@"/Applications"]];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"kMDItemKind == 'Application'"];
    
    [pimpl->query setPredicate: predicate];
    [pimpl->query startQuery];
    
    __block id misi;
    misi = [[NSNotificationCenter defaultCenter] addObserverForName:@"NSMetadataQueryDidFinishGatheringNotification" object:nil queue:nil usingBlock:^(NSNotification *note) {
            // do something with the result
            //int count = [pimpl->query resultCount];
            [pimpl->query stopQuery];
            [[NSNotificationCenter defaultCenter] removeObserver:misi];
        
            //nativeClass->metadataNotificationCompleted(count);

            NSString *res =
            [[pimpl->query resultAtIndex:0] valueForAttribute:(NSString *)kMDItemCFBundleIdentifier];
                const juce::String str = nsStringToJuce(res);
            nativeClass->metadataNotificationCompleted(str);
     }];
    
}
