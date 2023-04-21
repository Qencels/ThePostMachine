#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Enums.h"
#include "ConfigHandler.h"
#include "UIHandler.h"
#include "MarksHandler.h"
#include "AlgorithmHandler.h"

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

int algCmdSelector(std::string cmd, std::vector<std::string> cmdDeffinitions) {
	std::string tempSubstr = cmd.substr(0, cmd.find(" "));
	int i = 0;
	for (i; i < cmdDeffinitions.size(); i++) {
		std::string cmdDef = cmdDeffinitions[i].substr(cmdDeffinitions[i].find(":") + 2, EOF);
		if (tempSubstr == cmdDef) return i;
	}
	return i;
}

void startAlg(std::vector<std::string>& commands, std::vector<long long int>& points, long long int carriagePos, std::vector<std::string> cmdDeffinitions) {

	size_t i = 0;
	long long int carPos = carriagePos;

	while (algCmdSelector(commands[i], cmdDeffinitions) != 5) { // 5 - end of program operator

		std::vector<std::string> args = UIHandler::splitStr(commands[i].substr(commands[i].find(" ") + 1, EOF));

		switch (algCmdSelector(commands[i], cmdDeffinitions))
		{
		case 0:
			carPos++;
			i = _atoi64(args[0].data()) -1;
			break;
		case 1:
			carPos--;
			i = _atoi64(args[0].data()) -1;
			break;
		case 2:
			marksHandler::EndlessBelt::setMark(carPos);
			i = _atoi64(args[0].data()) -1;
			break;
		case 3:
			marksHandler::EndlessBelt::delMark(carPos);
			i = _atoi64(args[0].data()) -1;
			break;
		case 4:
			if (marksHandler::EndlessBelt::find(carPos) != -1) { i = _atoi64(args[1].data()) -1; }
			else { i = _atoi64(args[0].data()) -1; }
			break;
		case 5:
			break;
		default:
			break;
		}
	}
}

std::string carriageSettingsInit(std::string args) {
	long long int pos = 0;
	std::string sbstr = "";
	std::string res = "UNDEFINED";

	try { 
		sbstr = args.substr(14, EOF); // get arg from command
		pos = _atoi64(sbstr.data()); 
		marksHandler::EndlessBelt::setCarriage(pos);
		res = std::to_string(pos);
	}
	catch (...) { UIHandler::errorMSG(WRONG_ARG); }
	return res;
}

void algSettingsInit() {
	std::string buffer = "";

	std::vector<std::string> cmdDeffinitions;

	try { cmdDeffinitions = configHandler::Config::getInstance()->getData(); }
	catch (...) { throw WRONG_PATH_OR_NO_PERMISSION; }

	size_t lineIndex = 1;

	while (buffer != "/menu") {
		std::cout << lineIndex << ". ";
		UIHandler::input(buffer);
		lineIndex++;

		if (buffer.substr(0, 5) == "/menu") continue;

		if (buffer.substr(0, 4) != "/del") {
			std::string tempSubstr = buffer.substr(0, buffer.find(" "));

			for (size_t i = 0; i < cmdDeffinitions.size(); i++) {
				if (tempSubstr == cmdDeffinitions[i].substr(cmdDeffinitions[i].find(":") + 2, EOF)) {
					algorithmHandler::CommandsList::addCommand(buffer);
				}
			}
		}
		else {
			std::vector<std::string> args;
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			for (size_t i = 0; i < args.size(); i++) {
				algorithmHandler::CommandsList::delCommand(_atoi64(args[i].data())-1);
			}
		}

	}
}

void marksSettingsInit() {
	std::string buffer = "";

	while (buffer != "/menu") {
		UIHandler::input(buffer);

		std::vector<std::string> args;

		long long int temp = 0;

		if (buffer.size() <= 5) continue;

		if (buffer.substr(0, 4) == "/set") {
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			for (size_t i = 0; i < args.size(); i++) {
				temp = _atoi64(args[i].data());
				marksHandler::EndlessBelt::setMark(temp);
			}
		}
		else if (buffer.substr(0, 4) == "/del") {
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			for (size_t i = 0; i < args.size(); i++) {
				temp = _atoi64(args[i].data());
				marksHandler::EndlessBelt::delMark(temp);
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
		try { UIHandler::algMSG(configHandler::Config::getInstance()->getData()); }
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
		algSettingsInit();
		getchar();
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
		UIHandler::showMarks(marksHandler::EndlessBelt::getPositions());
		getchar();
		break;

	case show_alg:
		UIHandler::showAlg(algorithmHandler::CommandsList::getCommands());
		getchar();
		break;

	case clear:
		marksHandler::EndlessBelt::clearValues();
		algorithmHandler::CommandsList::clearValues();
		break;

	case start:
		try {
			startAlg(algorithmHandler::CommandsList::getCommands(), marksHandler::EndlessBelt::getPositions(),
				marksHandler::EndlessBelt::getCarPos(), configHandler::Config::getInstance()->getData());
		}
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
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
