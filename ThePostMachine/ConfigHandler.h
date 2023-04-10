#pragma once
#include <fstream>
#include <string>
#include <vector>

namespace postMachine {
	namespace configHandler {

		enum ErrorCodes {
			WRONG_PATH_OR_NO_PERMISSION
		};

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
