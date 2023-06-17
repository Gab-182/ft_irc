# include "../../include/commands/JoinCommand.hpp"
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
JoinCommand::JoinCommand() {
	_command = "JOIN";
//	registry["join"] = &JoinCommand::executeCommand;
}

JoinCommand::~JoinCommand() {}

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
void JoinCommand::executeCommand(const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels) {
	if (_parameters.empty()) {
		std::cout << BOLDRED << "Empty parameters" << std::endl;
	} else {
		std::cout << BOLDGREEN << "Joining Command with parameter called " << RESET << std::endl;
	}
}

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
void JoinCommand::registerCommands() {
	ICommands::registry["JOIN"] = &JoinCommand::executeCommand;
}

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/