//
//  NSInterop.cpp
//  DlgTest
//
//  Created by Daniel Szabo on 30/09/14.
//
//

#include "NSInterop.h"
#import <Cocoa/Cocoa.h>

#include "AboutComponent.h"

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
    
    [[NSNotificationCenter defaultCenter] addObserverForName:@"NSMetadataQueryDidFinishGatheringNotification" object:nil queue:nil usingBlock:^(NSNotification *note) {
            int count = [pimpl->query resultCount];
     nativeClass->metadataNotificationCompleted(count);
     }];
    
}
