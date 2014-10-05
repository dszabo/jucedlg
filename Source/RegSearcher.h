#ifndef _JUCECONS1_REGSEARCHER
#define _JUCECONS1_REGSEARCHER
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Source/SearchResult.h"
#include <Windows.h>

class RegSearcher
{
public:
	RegSearcher();
	~RegSearcher();

	OwnedArray<AppSearchResult>& getSearchResults();
private:
	OwnedArray<AppSearchResult> searchResultArray;
	void lookupApps();
	void queryKey(HKEY key);
};

#endif