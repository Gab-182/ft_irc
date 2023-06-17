#include "../../include/commands/NickCommand.hpp"
using namespace IRC;

/*-------------------------------------------------------------------------------------------------------------*/
NickCommand::NickCommand() {}

NickCommand::~NickCommand() {}

/*-------------------------------------------------------------------------------------------------------------*/
void NickCommand::executeCommand(const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels) {
	if (_parameters.empty()) {
		std::cout << BOLDRED << "Empty parameters" << std::endl;
	} else {
		std::cout << BOLDGREEN << "Nick Command with parameter called " << RESET << std::endl;
	}
}

/*-------------------------------------------------------------------------------------------------------------*/