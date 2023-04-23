#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Enums.h"
#include "ConfigHandler.h"
#include "UIHandler.h"
#include "MarksHandler.h"
#include "AlgorithmHandler.h"
#include "FileHandler.h"

void executeCommand(int command, std::string args, std::string ver, std::vector<std::string>& data);

std::string CURRENT_VERSION;
std::vector<std::string> CONFIG_DATA;

using namespace postMachine;

int main()
{

	try {
		CURRENT_VERSION = configHandler::Config::getInstance()->getVer();
		CONFIG_DATA = configHandler::Config::getInstance()->getData();
	} catch (ErrorCodes err) { UIHandler::errorMSG(err); }

    while (true) {

        UIHandler::welcomeMSG();
        
        std::string buffer = "";
        UIHandler::input(buffer);

		try { executeCommand(UIHandler::commandSelector(buffer), buffer, CURRENT_VERSION, CONFIG_DATA); }
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

	if (i >= commands.size()) return;

	while (algCmdSelector(commands[i], cmdDeffinitions) != 5) { // 5 - end of program operator

		std::vector<std::string> args = UIHandler::splitStr(commands[i].substr(commands[i].find(" ") + 1, EOF));

		switch (algCmdSelector(commands[i], cmdDeffinitions))
		{
		case 0:
			carPos++;
			try { i = _atoi64(args[0].data()) - 1; }
			catch (...) { return; }
			break;
		case 1:
			carPos--;
			try { i = _atoi64(args[0].data()) - 1; }
			catch (...) { return; }
			break;
		case 2:
			marksHandler::EndlessBelt::setMark(carPos);
			try { i = _atoi64(args[0].data()) - 1; }
			catch (...) { return; }
			break;
		case 3:
			marksHandler::EndlessBelt::delMark(carPos);
			try { i = _atoi64(args[0].data()) - 1; }
			catch (...) { return; }
			break;
		case 4:
			if (marksHandler::EndlessBelt::find(carPos) != -1) { 
				try { i = _atoi64(args[1].data()) - 1; }
				catch (...) { return; }
			}
			else { 
				try { i = _atoi64(args[0].data()) - 1; }
				catch (...) { return; }
			}
			break;
		case 5:
			break;
		default:
			break;
		}

		if (i >= commands.size()) break;
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

void algSettingsInit(std::vector<std::string>& cfgData) {
	std::string buffer = "";
	std::string lowerBuffer = "";

	std::vector<std::string> cmdDeffinitions;

	cmdDeffinitions = cfgData;

	size_t lineIndex = 1;

	while (lowerBuffer != "/menu") {
		std::cout << lineIndex << ". ";
		UIHandler::input(buffer);
		lowerBuffer = buffer;
		for (size_t i = 0; i < lowerBuffer.size(); i++) lowerBuffer[i] = tolower(lowerBuffer[i]);
		lineIndex++;

		if (lowerBuffer.substr(0, 5) == "/menu") continue;

		if (lowerBuffer.substr(0, 4) == "/del") {
			std::vector<std::string> args;
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			for (size_t i = 0; i < args.size(); i++) {
				algorithmHandler::CommandsList::delCommand(_atoi64(args[i].data())-1);
			}
		}
		else if (lowerBuffer.substr(0, 4) == "/set") {
			std::vector<std::string> args;
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			std::string tempSubstr = args[1].substr(0, args[1].find(" "));
			std::string cmd;
			for (size_t i = 1; i < args.size(); i++) cmd = cmd + args[i] + " ";

			for (size_t i = 0; i < cmdDeffinitions.size(); i++) {
				if (tempSubstr == cmdDeffinitions[i].substr(cmdDeffinitions[i].find(":") + 2, EOF)) {
					algorithmHandler::CommandsList::changeCommand(_atoi64(args[0].data()) - 1, cmd);
				}
			}
		}
		else {

			std::string tempSubstr = buffer.substr(0, buffer.find(" "));

			for (size_t i = 0; i < cmdDeffinitions.size(); i++) {
				if (tempSubstr == cmdDeffinitions[i].substr(cmdDeffinitions[i].find(":") + 2, EOF)) {
					algorithmHandler::CommandsList::addCommand(buffer);
				}
			}

		}

	}
}

void marksSettingsInit() {
	std::string buffer = "";
	std::string lowerBuffer = "";

	while (lowerBuffer != "/menu") {
		UIHandler::input(buffer);
		lowerBuffer = buffer;
		for (size_t i = 0; i < lowerBuffer.size(); i++) lowerBuffer[i] = tolower(lowerBuffer[i]);

		std::vector<std::string> args;

		long long int temp = 0;

		if (buffer.size() <= 5) continue;

		if (lowerBuffer.substr(0, 4) == "/set") {
			args = UIHandler::splitStr(buffer.substr(5, EOF));

			for (size_t i = 0; i < args.size(); i++) {
				temp = _atoi64(args[i].data());
				marksHandler::EndlessBelt::setMark(temp);
			}
		}
		else if (lowerBuffer.substr(0, 4) == "/del") {
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

void executeCommand(int command, std::string args, std::string ver, std::vector<std::string>& data) {

	switch (command)
	{
	case about:
		try { UIHandler::aboutMSG(ver); }
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
		getchar();
		break;

	case menu:
		UIHandler::welcomeMSG();
		break;

	case set_alg:
		try { UIHandler::algMSG(data); }
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
		algSettingsInit(data);
		break;

	case set_marks:
		UIHandler::marksMSG();
		marksSettingsInit();
		break;

	case set_carriage:
		UIHandler::carriageMSG(carriageSettingsInit(args));
		getchar();
		break;

	case show_marks:
		UIHandler::showMarks(marksHandler::EndlessBelt::getPositions());
		getchar();
		break;

	case show_alg:
		UIHandler::showAlg(algorithmHandler::CommandsList::getCommands());
		getchar();
		break;

	case clear:
		if (args.find("all") != -1) {
			marksHandler::EndlessBelt::clearValues();
			algorithmHandler::CommandsList::clearValues();
		}
		else if (args.find("alg") != -1) {
			algorithmHandler::CommandsList::clearValues();
		}
		else if (args.find("marks") != -1) {
			marksHandler::EndlessBelt::clearValues();
		}
		else {
			marksHandler::EndlessBelt::clearValues();
			algorithmHandler::CommandsList::clearValues();
		}
		break;

	case start:
		try {
			startAlg(algorithmHandler::CommandsList::getCommands(), marksHandler::EndlessBelt::getPositions(),
				marksHandler::EndlessBelt::getCarPos(), data);
		}
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
		break;

	case exitC:
		exit(1);
		break;

	case importF:
		marksHandler::EndlessBelt::clearValues();
		algorithmHandler::CommandsList::clearValues();
		try {
			marksHandler::EndlessBelt::setCarriage(fileHandler::importFile(args.substr(args.find(" ") + 1, EOF), ver, algorithmHandler::CommandsList::getCommands(), data, marksHandler::EndlessBelt::getPositions()));
			UIHandler::fileImportMSG();
		}
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
		getchar();
		break;

	case exportF:
		try { 
			fileHandler::saveToFile(args.substr(args.find(" ")+1, EOF), ver, algorithmHandler::CommandsList::getCommands(), marksHandler::EndlessBelt::getPositions(), marksHandler::EndlessBelt::getCarPos());
			UIHandler::fileExportMSG(args.substr(args.find(" ") + 1, EOF));
		}
		catch (ErrorCodes err) { UIHandler::errorMSG(err); }
		getchar();
		break;

	default:
		throw WRONG_COMMAND;
		break;
	}
}
