#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include "Enums.h"

namespace postMachine {
	namespace UIHandler {

		void welcomeMSG();
		void errorMSG(ErrorCodes err);
		void aboutMSG(std::string ver);
		void carriageMSG(std::string pos);
		void marksMSG();
		void algMSG(std::vector<std::string> commandsDif);
		void fileExportMSG(std::string filePath);
		void fileImportMSG();

		void showMarks(std::vector<long long int> positions);
		void showAlg(std::vector<std::string> commands);

		void input(std::string& buffer);
		int commandSelector(std::string command);

		std::vector<std::string> splitStr(std::string str);

	}
}