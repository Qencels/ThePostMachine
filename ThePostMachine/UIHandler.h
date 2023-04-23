#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include "Enums.h"
#include <windows.h>

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

		void showMarks(const std::vector<long long int>& positions);
		void showAlg(const std::vector<std::string>& commands);
		void showRes(const std::vector<long long int>& positions, const std::vector<std::string>& commands);

		void visualization(const std::vector<long long int>& positions, const long long int carPos, long long int speed);

		void input(std::string& buffer);
		int commandSelector(std::string command);

		std::vector<std::string> splitStr(std::string str);

	}
}