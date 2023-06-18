#include "../../include/commands/NickCommand.hpp"
using namespace IRC;

/*-------------------------------------------------------------------------------------------------------------*/
NickCommand::NickCommand() : ICommands() {
	_command = "NICK";
}

NickCommand::~NickCommand() {}

/*-------------------------------------------------------------------------------------------------------------*/
void NickCommand::executeCommand(ICommands* base,  const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels) {
	(void)clientSocket;
	(void)clients;
	(void)channels;
	(void)base;

	std::cout << BOLDGREEN << "[NICK] COMMAND HAS BEEN CALLED" << std::endl;

}

/*-------------------------------------------------------------------------------------------------------------*/