#include "../../include/commands/PingCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
PingCommand::PingCommand() : ICommands() { }

PingCommand::~PingCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PingCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	(void) server;
	(void) client;

	if (!base->getParameters(command).empty()) {
		std::string uniqueToken = base->getParameters(command)[0];

		std::string pongMsg = "PONG :" + uniqueToken + "\r\n";
		sendResponse(clientSocket, pongMsg);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/