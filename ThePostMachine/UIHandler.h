#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Enums.h"

namespace postMachine {
	namespace UIHandler {

		void showConfig(std::vector<std::string> data, std::string ver);
		void welcomeMSG();
		void errorMSG(ErrorCodes err);
		void aboutMSG(std::string ver, std::vector<std::string>& definitions);

		void input(std::string& buffer);
		int commandSelector(std::string& command);

	}
}