#include "UIHandler.h"

namespace postMachine {
	namespace UIHandler {

		void showConfig(std::vector<std::string> data, std::string ver) {
			std::cout << "=======================\n";
			std::cout << "Current version: " << ver << "\n\n";
			for (size_t i = 0; i < data.size(); i++) {
				std::cout << data[i] << std::endl;
			}
			std::cout << "=======================\n";
		}

	}
}