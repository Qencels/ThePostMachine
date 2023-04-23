#pragma once
#include "Enums.h"
#include <fstream>
#include <vector>
#include <string>

namespace postMachine {
	namespace fileHandler {

		void saveToFile(std::string filePath, std::string version, std::vector<std::string>& algCommands, std::vector<long long int>& marksPositions, long long int carPos);

		long long int importFile(std::string filePath, std::string version, std::vector<std::string>& algCommands, std::vector<std::string>& algDef, std::vector<long long int>& marksPositions);

	}
}
