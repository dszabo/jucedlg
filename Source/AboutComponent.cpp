#include "AboutComponent.h"

#ifdef JUCE_MSVC
#include "RegSearcher.h"
#include <tchar.h>
#include <Shlwapi.h>
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
	RegSearcher regSearcher;
	grid = new CustomGridModel(regSearcher.getSearchResults());

	table.setModel(grid);
	table.getHeader().addColumn(L"App path", 1, 120);
	table.getHeader().addColumn(L"Plugin Path", 2, 330);
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
#ifdef JUCE_MSVC
			String targetFile = ((CustomGridModel *)table.getModel())->items[table.getSelectedRow()]->getAppPath();

			TCHAR buf[MAX_PATH];
			if (targetFile.length() + _tcslen(_T("MockTextFile.txt")) >= MAX_PATH)
			{
				// path is too long
				AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, _T("Copy plugin"), _T("Path is too long!"));
				return;
			}
			if (NULL != PathCombine(buf, targetFile.toWideCharPointer(), _T("MockTextFile.txt")))
			{
				String targetFileToCopy(buf);
				File sourceDir = File::getSpecialLocation(File::SpecialLocationType::currentExecutableFile).getParentDirectory();
				String sourceFile(sourceDir.getFullPathName());
				sourceFile << _T("\\MockTextFile.txt");
				File sourceFileToCopy(sourceFile);

				if (sourceFileToCopy.copyFileTo(targetFileToCopy))
				{
					AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, _T("Copy plugin"), _T("Plugin copied to Photoshop plugin folder successfully"));
				}
				else
				{
					AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, _T("Copy plugin"), _T("Plugin copy to Photoshop plugin folder has failed"));
				}
			}



#endif

#ifdef JUCE_MAC
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
#endif
        }
    }
}

