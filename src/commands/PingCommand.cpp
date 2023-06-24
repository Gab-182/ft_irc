#include "../../include/commands/PingCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
PingCommand::PingCommand() : ICommands() { }

PingCommand::~PingCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PingCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client) {
	(void) server;
	(void) client;

	if (!base->getParameters().empty()) {
		std::string uniqueToken = base->getParameters()[0];

		std::string pongMsg = "PONG :" + uniqueToken + "\r\n";
		sendResponse(clientSocket, pongMsg);
	}

	// Cleaning the parameters vector before adding new ones to it.
	base->getParameters().clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/