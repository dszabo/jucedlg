#include "SearchResult.h"

AppSearchResult::AppSearchResult(const String &id, const String &path, const String &version) :
    appId(id),
    appPath(path),
    appVersion(version)
{
}

AppSearchResult::~AppSearchResult()
{
}

String AppSearchResult::getAppIdentifier()
{
    return appId;
}

String AppSearchResult::getAppPath()
{
    return appPath;
}

String AppSearchResult::getAppVersion()
{
    return appVersion;
}