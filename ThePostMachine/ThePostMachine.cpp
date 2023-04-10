#include <iostream>
#include "ConfigHandler.h"
#include "UIHandler.h"

int main()
{
    using namespace postMachine;
    UIHandler::showConfig(configHandler::Config::getInstance()->getData(),
        configHandler::Config::getInstance()->getVer());

    return 0;
}

