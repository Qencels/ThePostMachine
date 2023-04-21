#pragma once
#include "Enums.h"
#include <vector>
#include <string>

namespace postMachine {
	namespace algorithmHandler {

		class CommandsList {
			private:

				static CommandsList* p_instance;
				static std::vector<std::string> commands;

				CommandsList();
				CommandsList(const CommandsList& obj);

			public:

				static CommandsList* getInstance();

				static void addCommand(std::string command);
				static void delCommand(size_t index);

				static std::vector<std::string>& getCommands();

				static void clearValues();
		};

	}
}
