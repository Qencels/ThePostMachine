#include "ConfigHandler.h"

namespace postMachine {
    namespace configHandler {

        //default data
        const std::string Config::CONFIG_PATH = "config.txt";
        const std::string Config::CURRENT_VER = "0001-A";

        std::vector<std::string> Config::data = {"Right shift: >", "Left shift: <", "Set mark: V", 
            "Delete mark: X", "Fork: ?", "End of program: !"};
        //

        bool Config::isFileExist() {

            std::ifstream config;
            config.open(CONFIG_PATH);

            if (!config.is_open()) return false;
            config.close();

            return true;

        }

        void Config::createDefaultConfig() {

            std::ofstream config;
            config.open(CONFIG_PATH);

            if (!config.is_open()) throw WRONG_PATH_OR_NO_PERMISSION; 

            config << "Current version: " << CURRENT_VER << "\n\n";
            for (size_t i = 0; i < data.size(); i++) {
                config << data[i] << "\n";
            }

            config.close();

        }

        void Config::loadConfig() {
            std::ifstream config;
            config.open(CONFIG_PATH);

            if (!config.is_open()) throw WRONG_PATH_OR_NO_PERMISSION;

            std::string buffer;
            size_t linePos = 1;
            while (!config.eof()) {

                getline(config, buffer);

                if ((int)linePos - (int)data.size() <= 2) {
                    if (linePos >= 3) { //data
                        data[linePos - 3] = buffer;
                    }
                }

                linePos++;

            }

            config.close();

        }

        Config::Config() {

            if (!isFileExist()) {
                try { createDefaultConfig(); }
                catch (ErrorCodes& error) { throw error; }
            }
            else {
                try { loadConfig(); }
                catch (ErrorCodes& error) { throw error; }
            }

        }

        Config::Config(const Config& obj) {}

        //getInstance
        Config* Config::p_instance;

        Config* Config::getInstance()
        {
            if (p_instance == nullptr) {
                p_instance = new Config();
                return p_instance;
            }
            else {
                return p_instance;
            }
        }

        std::vector<std::string>& Config::getData() {
            return data;
        }

        std::string Config::getVer() {
            return CURRENT_VER;
        }

    }
}