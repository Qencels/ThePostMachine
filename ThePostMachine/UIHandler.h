#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Enums.h"

namespace postMachine {
	namespace UIHandler {

		void welcomeMSG();
		void errorMSG(ErrorCodes err);
		void aboutMSG(std::string ver);
		void carriageMSG(long long int pos);
		void marksMSG();

		void showMarks(std::vector<long long int> positions);

		void input(std::string& buffer);
		int commandSelector(std::string& command);

		std::vector<std::string> splitStr(std::string str);

	}
}