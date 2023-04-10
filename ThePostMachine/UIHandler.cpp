#include "UIHandler.h"

namespace postMachine {
	namespace UIHandler {

		void showConfig(std::vector<std::string> data, std::string ver) {
			std::cout << "=======================\n";
			std::cout << "Current version: " << ver << "\n\n";
			for (size_t i = 0; i < data.size(); i++) {
				std::cout << data[i] << std::endl;
			}
			std::cout << "=======================\n\n";
		}

		void welcomeMSG() {
			system("cls");
			std::cout << "==========================================\n";
			std::cout << "Welcome to the Post machine emulator.\n";
			std::cout << "==========================================\n";
			std::cout << "Available commands:\n\n";
			std::cout << "1. /about - information about the program.\n";
			std::cout << "2. /menu - return to this point.\n\n";
			std::cout << "3. /set_alg - setting up the algorithm.\n";
			std::cout << "4. /set_marks - setting marks.\n";
			std::cout << "5. /set_carriage - setting carriage.\n\n";
			std::cout << "6. /show_points - shows the set values.\n";
			std::cout << "7. /show_alg - shows the set commands.\n\n";
			std::cout << "8. /clear - reset all values.\n";
			std::cout << "9. /start - run the algorithm.\n";
			std::cout << "10. /exit - exiting the program.\n";
			std::cout << "==========================================\n\n";
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
			default:
				std::cout << "Undefined error!\n";
				break;
			}
		}

		void aboutMSG(std::string ver, std::vector<std::string>& definitions) {
			system("cls");
			std::cout << "==========================================\n";
			std::cout << "Post Machine Emulator by Qencels.\n\n";
			std::cout << "Current version: " << ver << "\n";
			for (size_t i = 0; i < definitions.size(); i++) {
				std::cout << definitions[i] << "\n";
			}
			std::cout << "==========================================\n";
			std::cout << "Press any key to return to the menu.\n\n";
			getchar();
			welcomeMSG();
		}

		void input(std::string& buffer) {
			std::getline(std::cin, buffer);
		}

		int commandSelector(std::string& command) {
			if (command == "/about") return about;
			if (command == "/menu") return menu;
			if (command == "/set_alg") return set_alg;
			if (command == "/set_marks") return set_marks;
			if (command == "/set_carriage") return set_carriage;
			if (command == "/show_points") return show_points;
			if (command == "/show_alg") return show_alg;
			if (command == "/clear") return clear;
			if (command == "/start") return start;
			if (command == "/exit") return exitC;
			return -1;
		}

	}
}