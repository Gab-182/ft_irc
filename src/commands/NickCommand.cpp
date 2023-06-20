#include "../../include/commands/NickCommand.hpp"
using namespace IRC;

/*-------------------------------------------------------------------------------------------------------------*/
NickCommand::NickCommand() : ICommands() {
	_command = "NICK";
}

NickCommand::~NickCommand() {}

/*-------------------------------------------------------------------------------------------------------------*/
void NickCommand::executeCommand(ICommands* base,  const int& clientSocket, Server* server) {
	(void)clientSocket;
	(void)base;
	(void)server;

	std::cout << BOLDGREEN << "[NICK] COMMAND HAS BEEN CALLED" << std::endl;

}

/*-------------------------------------------------------------------------------------------------------------*/