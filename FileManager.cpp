#include "FileManager.h"
#include <iostream>
#include "External CodeAndLibraries/tinyfiledialogs/tinyfiledialogs.h"
FileManager::~FileManager()
{

}
FileManager::FileManager()
{
    lTheOpenFileName = NULL;
}

//Opens the file browser, and gets/returns the path of the file chosen
std::string FileManager::openFileBrowser()
{
    //Sets the lTheOpenFileName to the selected file
    lTheOpenFileName = tinyfd_openFileDialogW(
        L"Open CSV file",               //aTitle
        L"",							  //aDefaultPathAndFile
        3,								  //aNumOfFilterPatterns
        lFilterPatterns,				  //aFilterPatterns
        NULL,							  //aSingleFilterDescription
        0);								  //allow multiple selects
    if (!lTheOpenFileName)
    {
        tinyfd_messageBoxW(
            L"Error",
            L"Open file name is NULL",
            L"ok",
            L"error",
            1);
        return "Error: Open file name is NULL";
    }
    else
    {
        std::wstring ws(lTheOpenFileName);
        std::string filePath(ws.begin(), ws.end());
        std::cout << "File path string:" << filePath << std::endl;
        std::cout << "First in file path str: " << filePath.front();
        std::cout << "Last in file path str: " << filePath.back();
        return filePath;
    }
    

}



