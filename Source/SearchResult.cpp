#include "SearchResult.h"

SearchResult::SearchResult(const String &id, const String &path, const String &version) :
    bundleId(id),
    bundlePath(path),
    bundleVersion(version)
{
}

SearchResult::~SearchResult()
{
}

String SearchResult::getBundleIdentifier()
{
    return bundleId;
}

String SearchResult::getBundlePath()
{
    return bundlePath;
}

String SearchResult::getBundleVersion()
{
    return bundleVersion;
}