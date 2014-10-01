#ifndef __DlgTest__SearchResult__
#define __DlgTest__SearchResult__

#include "../JuceLibraryCode/JuceHeader.h"

class AppSearchResult
{
public:
    AppSearchResult(const String &id, const String &path, const String &version);
    ~AppSearchResult();
    juce::String getAppIdentifier();
    juce::String getAppPath();
    juce::String getAppVersion();
private:
    String appId;
    String appPath;
    String appVersion;
};

#endif