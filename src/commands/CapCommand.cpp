#include "../../include/commands/CapCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
CapCommand::CapCommand() : ICommands() { }

CapCommand::~CapCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void CapCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client) {
	(void) server;
	(void) client;

	if (!base->getParameters().empty()) {
		std::string capType = base->getParameters()[0];

		if (toLowerCase(capType) == "ls")
			sendResponse(clientSocket, "CAP * ACK :302 CAP LS\r\n");

		else if (toLowerCase(capType) == "end")
			sendResponse(clientSocket, "CAP * ACK :CAP END\r\n");
	}

	// Cleaning the parameters vector before adding new ones to it.
	base->getParameters().clear();
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/