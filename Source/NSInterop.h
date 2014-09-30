//
//  NSInterop.h
//  DlgTest
//
//  Created by Daniel Szabo on 30/09/14.
//
//

#ifndef __DlgTest__NSInterop__
#define __DlgTest__NSInterop__

#include <string>

class AboutComponent;

class NSInterop
{
public:
    NSInterop();
    ~NSInterop();
    void startMetadataQuery(AboutComponent *nativeClass);
private:
    class Private;
    Private *pimpl;
};

#endif /* defined(__DlgTest__NSInterop__) */
