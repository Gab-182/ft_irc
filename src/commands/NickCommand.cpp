#include "../../include/commands/NickCommand.hpp"
using namespace IRC;

/*-------------------------------------------------------------------------------------------------------------*/
NickCommand::NickCommand() : ICommands() {
	_command = "NICK";
}

NickCommand::~NickCommand() {}

/*-------------------------------------------------------------------------------------------------------------*/
void NickCommand::executeCommand() {
	if (_parameters.empty()) {
		std::cout << BOLDRED << "Empty parameters" << std::endl;
	} else {
		std::cout << BOLDGREEN << "Nick Command with parameter called " << RESET << std::endl;
	}
}

/*-------------------------------------------------------------------------------------------------------------*/