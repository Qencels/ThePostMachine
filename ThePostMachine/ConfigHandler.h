#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Enums.h"

namespace postMachine {
	namespace configHandler {

		class Config {

			private:

				static Config* p_instance;

				bool isFileExist();
				void createDefaultConfig();
				void loadConfig();

				Config();
				Config(const Config& obj);

				//data
				static const std::string CONFIG_PATH;
				static const std::string CURRENT_VER;
				static std::vector<std::string> data;
	
			public:

				static Config* getInstance();

				std::vector<std::string>& getData();
				std::string getVer();

		};

	}
}
