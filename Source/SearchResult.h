#ifndef __DlgTest__SearchResult__
#define __DlgTest__SearchResult__

#include "../JuceLibraryCode/JuceHeader.h"

class SearchResult
{
public:
    SearchResult(const String &id, const String &path, const String &version);
    ~SearchResult();
    juce::String getBundleIdentifier();
    juce::String getBundlePath();
    juce::String getBundleVersion();
private:
    String bundleId;
    String bundlePath;
    String bundleVersion;
};

#endif