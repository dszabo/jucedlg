#include "AboutComponent.h"

#ifdef JUCE_MSVC
#include <Windows.h>
#endif

AboutComponent::AboutComponent ()
{
    addAndMakeVisible (textButton = new TextButton ("Install to selected"));
    textButton->setBounds(10, 230, 120, 20);
    textButton->addListener (this);
    textButton->setEnabled(false);
#ifdef JUCE_MAC
    interop.startMetadataQuery(this);
#endif

#ifdef JUCE_MSVC
	fillTableWindows();
#endif
    setSize (400, 200);

}

AboutComponent::~AboutComponent()
{
    label = nullptr;
    textButton = nullptr;
}

#ifdef JUCE_MSVC
void AboutComponent::fillTableWindows()
{

	#define MAX_KEY_LENGTH 255
	#define MAX_VALUE_NAME 16383

	HKEY hTEstKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Adobe\\Photoshop"), 0, KEY_READ, &hTEstKey) == ERROR_SUCCESS) {
		TCHAR    achKey[MAX_KEY_LENGTH];			// buffer for subkey name
		DWORD    cbName;							// size of name string 
		TCHAR    achClass[MAX_PATH] = TEXT("");		// buffer for class name 
		DWORD    cchClassName = MAX_PATH;			// size of class string 
		DWORD    cSubKeys = 0;						// number of subkeys 
		DWORD    cbMaxSubKey;						// longest subkey size 
		DWORD    cchMaxClass;						// longest class string 
		DWORD    cValues;							// number of values for key 
		DWORD    cchMaxValue;						// longest value name 
		DWORD    cbMaxValueData;					// longest value data 
		DWORD    cbSecurityDescriptor;				// size of security descriptor 
		FILETIME ftLastWriteTime;					// last write time 

		DWORD i, retCode;

		TCHAR  achValue[MAX_VALUE_NAME];
		DWORD cchValue = MAX_VALUE_NAME;

		retCode = RegQueryInfoKey(
			hTEstKey,                // key handle 
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

		if (cSubKeys) {
			for (auto i = 0; i < cSubKeys; i++) {
				cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(hTEstKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
				if (retCode == ERROR_SUCCESS)
				{
					OutputDebugString(achKey);
				}

			}
		}

	}

	RegCloseKey(hTEstKey);
	
}
#endif

#ifdef JUCE_MAC
void AboutComponent::metadataNotificationCompleted(OwnedArray<AppSearchResult> &resultArray)
{
    grid = new CustomGridModel(resultArray);
    
    table.setModel(grid);
    table.getHeader().addColumn(L"Bundle Identifier", 1, 120);
    table.getHeader().addColumn(L"Bundle Path", 2, 330);
    table.getHeader().addColumn(L"Version", 3, 70);
    // give it a border
    table.setColour (ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness (1);
    table.setBounds(10, 10, 550, 200);
    addAndMakeVisible(table);
    
    if (table.getNumRows() > 0) {
        textButton->setEnabled(true);
    }
}
#endif

void AboutComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void AboutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == textButton)
    {
        if (table.getSelectedRow() >= 0) {
            String appPath = ((CustomGridModel *)table.getModel())->items[table.getSelectedRow()]->getAppPath();
            File f(appPath);
            File parentDir = f.getParentDirectory();
            File targetFile = File(parentDir.getFullPathName() + L"/Plug-ins/MockTextFile.txt");
            
            File currentAppPath = File::getSpecialLocation(File::currentApplicationFile);
            File sourceFileToCopy = File(currentAppPath.getFullPathName() + L"/Contents/Resources/MockTextFile.txt");
            //interop.nsLog(sourceFileToCopy.getFullPathName());
            
            if (sourceFileToCopy.copyFileTo(targetFile))
            {
                AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, L"Copy plugin", L"Plugin copied to Photoshop plugin folder successfully");
            }
            else
            {
                AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, L"Copy plugin", L"Plugin copy to Photoshop plugin folder has failed");
            }
        }
    }
}

