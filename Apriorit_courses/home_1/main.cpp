#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include "filewriters.h"
#include "creators.h"
int main() {
	
	WIN32_FIND_DATA data;
	std::string path;
	std::cin >> path;
	path+="//*"; // so we can extract all obj from this folder
	//local
	const HANDLE hFind = FindFirstFile("D:/a little bit of UNIV/4sem/web//*", &data);
	std::vector<WIN32_FIND_DATA> files;
	try {
		HANDLE hFind = FindFirstFile(path, &data);
		if (hFind == INVALID_HANDLE_VALUE) {
			throw std::invalid_argument("Invalid path");
		}
		do {
			//write in console for check, dry code
			//std::cout << data.cFileName << " " << data.dwReserved1 << " " << data.nFileSizeLow << std::endl;

			files.push_back(data);

			std::unique_ptr<writercreator> creator(new txtwritercreator());
			std::unique_ptr<write> main_file (creator->createnewfilewriter(data));

			creator = std::make_unique<csvwritercreator>();
			main_file.reset(creator->createnewfilewriter(data));

		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	} catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

}

