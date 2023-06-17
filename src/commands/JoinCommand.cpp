# include "../../include/commands/JoinCommand.hpp"
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
JoinCommand::JoinCommand() : ICommands() {
	_command = "JOIN";
}

JoinCommand::~JoinCommand() {}

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
void JoinCommand::executeCommand() {
	if (_parameters.empty()) {
		std::cout << BOLDRED << "Empty parameters" << std::endl;
	} else {
		std::cout << BOLDGREEN << "Joining Command with parameter called " << RESET << std::endl;
	}
}

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/