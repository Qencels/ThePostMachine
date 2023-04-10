#include <iostream>
#include "Enums.h"
#include "ConfigHandler.h"
#include "UIHandler.h"

void executeCommand(int command);

int main()
{
    using namespace postMachine;

    while (true) {

        UIHandler::welcomeMSG();
        
        std::string buffer = "";
        UIHandler::input(buffer);

		try { executeCommand(UIHandler::commandSelector(buffer)); }
        catch (ErrorCodes err) { UIHandler::errorMSG(err); }

    }

    return 0;
}

void executeCommand(int command) {

	using namespace postMachine;

	switch (command)
	{
	case about:
		try { UIHandler::aboutMSG(configHandler::Config::getInstance()->getVer(), configHandler::Config::getInstance()->getData()); }
		catch(ErrorCodes err) { UIHandler::errorMSG(err); }
		break;

	case menu:

		break;

	case set_alg:

		break;

	case set_marks:

		break;

	case set_carriage:

		break;

	case show_points:

		break;

	case show_alg:

		break;

	case clear:

		break;

	case start:

		break;

	case exitC:
		exit(1);
		break;

	default:
		throw WRONG_COMMAND;
		break;
	}
}
