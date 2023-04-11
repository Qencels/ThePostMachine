#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Enums.h"
#include "ConfigHandler.h"
#include "UIHandler.h"
#include "MarksHandler.h"

void executeCommand(int command, std::string args);

using namespace postMachine;

int main()
{

    while (true) {

        UIHandler::welcomeMSG();
        
        std::string buffer = "";
        UIHandler::input(buffer);

		try { executeCommand(UIHandler::commandSelector(buffer), buffer); }
        catch (ErrorCodes err) { UIHandler::errorMSG(err); }

    }

    return 0;
}

long long int carriageSettingsInit(std::string args) {
	long long int pos = 0;
	std::string sbstr;

	sbstr = args.substr(14, EOF); // get arg from command

	try { pos = _atoi64(sbstr.data()); }
	catch (...) { UIHandler::errorMSG(WRONG_ARG); }

	marksHandler::EndlessBelt::getInstance()->setCarriage(pos);
	return pos;
}

void marksSettingsInit() {
	std::string buffer = "";

	while (buffer != "/menu") {
		UIHandler::input(buffer);

		std::vector<std::string> args;

		long long int temp = 0;

		if (buffer.substr(0, 4) == "/set") {
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			for (size_t i = 0; i < args.size(); i++) {
				temp = _atoi64(args[i].data());
				marksHandler::EndlessBelt::getInstance()->setMark(temp);
			}
		}
		else if (buffer.substr(0, 4) == "/del") {
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			for (size_t i = 0; i < args.size(); i++) {
				temp = _atoi64(args[i].data());
				marksHandler::EndlessBelt::getInstance()->delMark(temp);
			}
		}
		else {
			continue;
		}

	}
}

void executeCommand(int command, std::string args) {

	switch (command)
	{
	case about:
		try { UIHandler::aboutMSG(configHandler::Config::getInstance()->getVer()); }
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
		getchar();
		break;

	case menu:
		UIHandler::welcomeMSG();
		break;

	case set_alg:

		break;

	case set_marks:
		UIHandler::marksMSG();
		marksSettingsInit();
		break;

	case set_carriage:
		UIHandler::carriageMSG(carriageSettingsInit(args));
		getchar();
		break;

	case show_points:
		UIHandler::showMarks(marksHandler::EndlessBelt::getInstance()->getPositions());
		getchar();
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

	case importF:

		break;

	case exportF:

		break;

	default:
		throw WRONG_COMMAND;
		break;
	}
}
