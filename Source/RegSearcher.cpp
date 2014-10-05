
#include "RegSearcher.h"
#include <tchar.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

RegSearcher::RegSearcher()
{
	this->lookupApps();
}

RegSearcher::~RegSearcher()
{
}

void RegSearcher::lookupApps()
{
	HKEY hTestKey;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		_T("SOFTWARE\\Adobe\\Photoshop"),
		0,
		KEY_READ,
		&hTestKey) == ERROR_SUCCESS
		)
	{
		this->queryKey(hTestKey);
	}

	RegCloseKey(hTestKey);
}

OwnedArray<AppSearchResult>& RegSearcher::getSearchResults()
{
	return this->searchResultArray;
}

void RegSearcher::queryKey(HKEY hKey)
{
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 
	ScopedPointer<TCHAR> buffer;

	DWORD i, retCode;

	//TCHAR  achValue[MAX_VALUE_NAME];
	//DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

	// Enumerate the subkeys, until RegEnumKeyEx fails.
#define PSDREGPATH "HKEY_LOCAL_MACHINE\\SOFTWARE\\Adobe\\Photoshop"

	if (cSubKeys)
	{
		for (i = 0; i<cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				String psdVersion(_T(PSDREGPATH));
				String appPathKey(_T(PSDREGPATH));
				psdVersion << _T("\\") << achKey;
				appPathKey << _T("\\") << achKey;
				String pluginPath = WindowsRegistry::getValue(psdVersion << "\\" << _T("PluginPath"));
				String appPath = WindowsRegistry::getValue(appPathKey << "\\" << _T("ApplicationPath"));

				searchResultArray.add(
					new AppSearchResult(appPath, pluginPath, achKey)
					);
			}
		}
	}
}

