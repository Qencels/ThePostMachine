#include "UIHandler.h"

namespace postMachine {
	namespace UIHandler {

		void welcomeMSG() {
			system("cls");
			std::cout << "============================================================\n"
				<< "Welcome to the Post machine emulator.\n"
				<< "============================================================\n"
				<< "Available commands:\n\n"
				<< "1. /about - information about the program.\n"
				<< "2. /menu - return to this point.\n\n"
				<< "3. /set_alg - setting up the algorithm.\n"
				<< "4. /set_marks - setting marks.\n"
				<< "5. /set_carriage (position) - setting carriage.\n\n"
				<< "6. /show_data - shows the data.\n\n"
				<< "7. /clear all/marks/alg - reset values.\n"
				<< "    Clearing the marks also resets the carriage position.\n\n"
				<< "8. /start - run the algorithm.\n\n"
				<< "9. /set_speed (milliseconds) - sets the speed of execution\n"
				<< "    of one algorithm command.\n\n"
				<< "10. /exit - exiting the program.\n\n"
				<< "11. /import (file path) - imports the algorithm from a file.\n"
				<< "12. /export (file path) - exports the algorithm to a file.\n"
				<< "============================================================\n\n";
		}

		void errorMSG(ErrorCodes err) {
			switch (err)
			{
			case WRONG_PATH_OR_NO_PERMISSION:
				std::cout << "Wrong path or no permission!\n";
				break;
			case WRONG_COMMAND:
				std::cout << "The command doesn't exist!\n";
				break;
			case WRONG_ARG:
				std::cout << "Invalid argument!\n";
				break;
			case INCORRECT_FILE_DESIGN:
				std::cout << "Incorrect file design!\n";
				break;
			default:
				std::cout << "Undefined error!\n";
				break;
			}
		}

		void aboutMSG(std::string ver) {
			system("cls");
			std::cout << "========================================================\n"
				<< "Post Machine Emulator by Qencels.\n"
				<< "Current version: " << ver << "\n\n"
				<< "A Post machine, also known as a Post-Turing machine,\n"
				<< "is a theoretical computing device that was introduced\n"
				<< "by Emil Post in the 1930s. It is a simple model of a\n"
				<< "computer that consists of a tape of infinite length\n"
				<< "divided into cells, a read/write head that can move\n"
				<< "left and right along the tape, and a set of instructions\n"
				<< "that tell the machine what to do. The instructions are\n"
				<< "represented as a list of rules that specify how the\n"
				<< "machine should behave when it encounters a particular\n"
				<< "symbol on the tape. The Post machine can perform simple\n"
				<< "arithmetic operations, and it is equivalent in power to\n"
				<< "a Turing machine. It is an important theoretical tool\n"
				<< "for studying the limits of computation and the nature\n"
				<< "of algorithms.\n"
				<< "========================================================\n"
				<< "Press Enter to return to the menu.\n\n";
		}

		void carriageMSG(std::string pos) {
			std::cout << "\nThe position of carriage has been updated.\n"
				<< "Current position: " << pos << "\n"
				<< "Press enter to continue\n";
		}

		void marksMSG() {
			system("cls");
			std::cout << "======================================\n"
				<< "You have moved on to setting up marks.\n\n"
				<< "Use /set (pos 1, pos 2, pos 3...) to\n"
				<< "set marks in these positions.\n\n"
				<< "Use /del (pos 1, pos 2, pos 3...) to\n"
				<< "delete marks in these positions.\n\n"
				<< "Use /menu to return to the menu.\n"
				<< "======================================\n\n";
		}

		void algMSG(std::vector<std::string> commandsDif) {
			system("cls");
			std::cout << "====================================================\n"
				<< "You have moved on to setting up algorithm commands.\n"
				<< "Available commands:\n\n";
			for (size_t i = 0; i < commandsDif.size(); i++) {
				std::cout << i + 1 << ". " << commandsDif[i] << "\n";
			}
			std::cout << "\nUse commands definitions for setting up.\n"
				<< "Use /del (index) to delete command in this position.\n"
				<< "Use /set (index) (command) to change command.\n"
				<< "Use /menu to return to the menu.\n"
				<< "====================================================\n\n";
				
		}
		
		void fileExportMSG(std::string filePath) {
			std::cout << "The export was successful.\n"
				<< "File path: " << filePath << "\n"
				<< "Press enter to continue\n";
		}

		void fileImportMSG() {
			std::cout << "The import was successful.\n"
				<< "Press enter to continue\n";
		}

		std::string formatingInput(std::string str) {
			
			std::string res = "";
			std::string tempStr = "";

			for (size_t i = 0; i < str.size(); i++) {
				if (str[i] == '\t') str[i] = ' ';
				if (str[i] != ' ') {
					tempStr.push_back(str[i]);
				}
				else if (tempStr.size() > 0) {
					res = res + tempStr + " ";
					tempStr = "";
				}
			}
			res = res + tempStr;

			return res;
		}

		void input(std::string& buffer) {
			std::string tempStr;
			std::getline(std::cin, tempStr);
			buffer = formatingInput(tempStr);
		}

		int commandSelector(std::string command) {
			for (size_t i = 0; i < command.size(); i++) command[i] = tolower(command[i]);
			if (command == "/about") return about;
			if (command == "/menu") return menu;
			if (command == "/set_alg") return set_alg;
			if (command == "/set_marks") return set_marks;
			if (command.substr(0,13) == "/set_carriage") return set_carriage;
			if (command == "/show_data") return show_data;
			if (command.substr(0,6) == "/clear") return clear;
			if (command == "/start") return start;
			if (command.substr(0, 10) == "/set_speed") return set_speed;
			if (command == "/exit") return exitC;
			if (command.substr(0,7) == "/import") return importF;
			if (command.substr(0,7) == "/export") return exportF;
			return -1;
		}

		std::vector<std::string> splitStr(std::string str) {
			std::vector<std::string> res;
			std::string tempStr = "";

			for (size_t i = 0; i < str.size(); i++) {
				if (str[i] != ' ') {
					tempStr.push_back(str[i]);
				}
				else {
					res.push_back(tempStr);
					tempStr = "";
				}
			}
			if (res.empty()) res.push_back(tempStr);
			if (res.back() != tempStr && tempStr != "") res.push_back(tempStr);

			return res;
		}

		void showMarks(const std::vector<long long int>& positions) {
			for (size_t i = 0; i < positions.size(); i++){
				std::cout << positions[i] << " ";
			}
			std::cout << "\n";
		}

		void showAlg(const std::vector<std::string>& commands) {
			for (size_t i = 0; i < commands.size(); i++) {
				std::cout << i + 1 << ". " << commands[i] << "\n";
			}
		}

		void showRes(const std::vector<long long int>& positions, const std::vector<std::string>& commands) {
			std::cout << "Installed marks: ";
			showMarks(positions);
			std::cout << "\nAlgorithm:\n";
			showAlg(commands);
			std::cout << "\nPress enter to continue.\n";
		}

		void visualization(const std::vector<long long int>& positions, const long long int carPos, long long int speed) {
			system("cls");
			size_t maxLen = 1;
			std::string line;

			for (size_t i = 0; i < positions.size(); i++) {
				size_t temp = std::to_string(positions[i]).size();
				if (maxLen < temp) maxLen = temp;
			}

			for (size_t i = 0; i < 21; i++) {
				for (size_t j = 0; j < maxLen + 3; j++) {
					if (i + carPos - 10 == carPos && j == (maxLen + 3) / 2) { line.push_back('V'); }
					else { line.push_back('-'); }
				}
			}
			std::cout << line << "-\n";

			for (long long int i = carPos - 10; i <= carPos + 10; i++) {

				bool isFinded = false;

				for (size_t k = 0; k < positions.size(); k++) {
					if (positions[k] == i) {
						std::cout << "| ";
						std::cout.width(maxLen);
						std::cout << i;
						std::cout << " ";
						isFinded = true;
						break;
					}
				}
				if (!isFinded) {
					std::cout << "| ";
					std::cout.width(maxLen);
					std::cout << " ";
					std::cout << " ";
				}
			}
			std::cout << "|\n";

			std::cout << line << "-\n\nCarriage position: " << carPos << "\n";

			Sleep(speed);

		}

	}
}