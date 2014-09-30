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


static NSString* juceStringToNS (const String& s)
{
    return [NSString stringWithUTF8String: s.toUTF8()];
}

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

void NSInterop::nsLog(const juce::String &message)
{
    NSLog(@"%@", juceStringToNS(message));
}

void NSInterop::startMetadataQuery(AboutComponent* nativeClass)
{
    [pimpl->query setSearchScopes:@[@"/Applications"]];
    
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"kMDItemKind == 'Application'"];
    
    /*
    NSPredicate *predicate = [NSPredicate
                                    predicateWithFormat:@"(kMDItemCFBundleIdentifier contains[cd] %@) AND (kMDItemKind == 'Application') AND (kMDItemExecutableArchitectures == 'x86_64')",
                                    @"photoshop"];
     */

    
    [pimpl->query setPredicate: predicate];
    [pimpl->query startQuery];
    
    __block id misi;
    misi = [[NSNotificationCenter defaultCenter] addObserverForName:@"NSMetadataQueryDidFinishGatheringNotification" object:nil queue:nil usingBlock:^(NSNotification *note) {
            [pimpl->query stopQuery];
            [[NSNotificationCenter defaultCenter] removeObserver:misi];
        
        
            OwnedArray<SearchResult> arr;
        
            NSUInteger i=0;
            for (i=0; i < [pimpl->query resultCount]; i++) {
                NSMetadataItem *theResult = [pimpl->query resultAtIndex:i];
                String bundleId = nsStringToJuce([theResult valueForAttribute:(NSString *)kMDItemCFBundleIdentifier]);
                String bundlePath = nsStringToJuce([theResult valueForAttribute:(NSString *)kMDItemPath]);
                //NSBundle *bundle = [NSBundle bundleWithPath:bundlePath];
                arr.add(new SearchResult(bundleId, bundlePath));
            }
        
            nativeClass->metadataNotificationCompleted(arr);
     }];
    
}
