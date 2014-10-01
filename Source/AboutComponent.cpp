#include "AboutComponent.h"

AboutComponent::AboutComponent ()
{
    addAndMakeVisible (textButton = new TextButton ("Install to selected"));
    textButton->setBounds(10, 230, 120, 20);
    textButton->addListener (this);

    interop.startMetadataQuery(this);
    setSize (400, 200);

}

AboutComponent::~AboutComponent()
{
    label = nullptr;
    textButton = nullptr;
}

void AboutComponent::metadataNotificationCompleted(OwnedArray<SearchResult> &resultArray)
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

}

void AboutComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void AboutComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == textButton)
    {
        if (table.getSelectedRow() >= 0) {
            String appPath = ((CustomGridModel *)table.getModel())->items[table.getSelectedRow()]->getBundlePath();
            File f(appPath);
            File parentDir = f.getParentDirectory();
            File targetFile = File(parentDir.getFullPathName() + L"/Plug-ins/MockTextFile.txt");
            
            File currentAppPath = File::getSpecialLocation(File::currentApplicationFile);
            File sourceFileToCopy = File(currentAppPath.getFullPathName() + L"/Contents/Resources/MockTextFile.txt");
            interop.nsLog(sourceFileToCopy.getFullPathName());
            
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

