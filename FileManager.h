#pragma once
#include <string>




class FileManager
{
private:
	wchar_t const* lTheOpenFileName;
	wchar_t const* lFilterPatterns[3] = { L"*.xls", L"*.xlsx", L"*.csv" }; //add more later

public:
	~FileManager();
	FileManager();
	std::string openFileBrowser();


};

