#include "FileHandler.h"

namespace postMachine {
	namespace fileHandler {

		void saveToFile(std::string filePath, std::string version, std::vector<std::string>& algCommands, std::vector<long long int>& marksPositions, long long int carPos) {

			std::ofstream output;
			output.open(filePath);

			if (!output.is_open()) throw WRONG_PATH_OR_NO_PERMISSION;

			output << "Version: " << version << "\n\nAlgorithm commands:\n";

			size_t i = 0;
			for (i; i < algCommands.size(); i++) {
				output << algCommands[i] << "\n";
			}
			output << "\nCarriage position: " << carPos << "\n\nInstalled marks:\n";

			i = 0;
			for (i; i < marksPositions.size(); i++) {
				output << marksPositions[i] << " ";
			}
			output << "\n";

			output.close();

		}

		long long int importFile(std::string filePath, std::string version, std::vector<std::string>& algCommands, std::vector<long long int>& marksPositions) {

			long long int res = 0;

			std::ifstream input;
			input.open(filePath);

			if (!input.is_open()) throw WRONG_PATH_OR_NO_PERMISSION;

			std::string tempStr;
			std::getline(input, tempStr);

			if (tempStr.substr(9, EOF) != version) throw INCORRECT_FILE_DESIGN;

			while (tempStr != "Algorithm commands:" && input.good()) {
				std::getline(input, tempStr);
			}

			while (input.good()) {
				std::getline(input, tempStr);
				if (tempStr == "") break;
				algCommands.push_back(tempStr);
			}

			while (tempStr.substr(0,18) != "Carriage position:" && input.good()) {
				std::getline(input, tempStr);
			}

			try { res = _atoi64(tempStr.substr(19, EOF).data()); }
			catch (...) { throw INCORRECT_FILE_DESIGN; }

			while (tempStr != "Installed marks:" && input.good()) {
				std::getline(input, tempStr);
			}

			while (input.good()) {
				std::getline(input, tempStr);
				if (tempStr == "") break;
				
				long long int pos = 0;

				std::string arg = "";
				for (size_t i = 0; i < tempStr.size(); i++) {
					if (tempStr[i] != ' ') { arg += tempStr[i]; }
					else {

						try { pos = _atoi64(arg.data()); }
						catch (...) { throw INCORRECT_FILE_DESIGN; }

						marksPositions.push_back(pos);

						arg = ""; 
					}
				}

				if (std::to_string(pos) != arg && arg.size() > 0) {

					try { pos = _atoi64(arg.data()); }
					catch (...) { throw INCORRECT_FILE_DESIGN; }

					marksPositions.push_back(pos);

				}

			}

			input.close();

			return res;

		}

	}
}
