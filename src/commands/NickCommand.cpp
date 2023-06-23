#include "../../include/commands/NickCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
NickCommand::NickCommand() : ICommands() {
	_command = "NICK";
}

NickCommand::~NickCommand() {}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void NickCommand::executeCommand(ICommands* base,  const int& clientSocket, Server* server, Client& client) {
	(void)clientSocket;
	(void)base;
	(void)server;
	(void )client;

	std::cout << BOLDGREEN << "[NICK] COMMAND HAS BEEN CALLED" << std::endl;

}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
