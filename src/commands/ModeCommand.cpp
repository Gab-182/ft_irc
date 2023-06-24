#include "../../include/commands/ModeCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*
 * TODO: Handle all the modes that are available in the subject of the project.
 **		-> [i] : Set/remove Invite-only channel
 **		-> [t] : Set/remove the restrictions of the TOPIC command to channel operators
 **		-> [k] : Set/remove the channel key (password)
 **		-> [o] : Give/take channel operator privilege
 **/
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ModeCommand::ModeCommand() : ICommands() { }

ModeCommand::~ModeCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ModeCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client) {
	(void) client;

	if (!base->getParameters().empty()) {
		// Check if the client has already entered a correct password before.

		if (Client::isClientAuthenticated(clientSocket, server)) {
			if (base->getParameters().back() == "+i") {
				std::string modMsg = "MODE "
									 + server->serverClientsMap[clientSocket]->getNickName()
									 + " +i\r\n";
				sendResponse(clientSocket, modMsg);
			}
		}

		// The client is not authenticated correctly.
		else {
			std::string authErrMsg = BOLDRED "Please make sure you entered: "
									 BOLDWHITE "[PassWord] "
									 BOLDRED "correctly!!" RESET "\r\n";
			sendResponse(clientSocket, authErrMsg);
		}
	}
	// Cleaning the parameters vector before adding new ones to it.
	base->getParameters().clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/