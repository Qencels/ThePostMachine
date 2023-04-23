#include "AlgorithmHandler.h"

namespace postMachine {
	namespace algorithmHandler {

		CommandsList* CommandsList::p_instance = nullptr;
		std::vector<std::string> CommandsList::commands;

		CommandsList::CommandsList() {}
		CommandsList::CommandsList(const CommandsList& obj) {}

		CommandsList* CommandsList::getInstance() {
			if (p_instance == nullptr) {
				p_instance = new CommandsList();
				return p_instance;
			}
			else {
				return p_instance;
			}
		}

		void CommandsList::addCommand(std::string command) {
			commands.push_back(command);
		}

		void CommandsList::delCommand(size_t index) {
			if (!commands.empty()) {
				if (index < commands.size()) {
					if (commands.size() != 1) {
						for (size_t i = index + 1; i < commands.size(); i++) {
							commands[i - 1] = commands[i];
						}
						commands.pop_back();
					} 
					else { commands.pop_back(); }
				}
				else { throw WRONG_ARG; }
			}
			else { return; }
		}

		std::vector<std::string>& CommandsList::getCommands() { return commands; }

		void CommandsList::clearValues() {
			commands.clear();
		}

		void CommandsList::changeCommand(size_t index, std::string command) {
			if (index < commands.size() && !commands.empty()) {
				commands[index] = command;
			}
		}

	}
}