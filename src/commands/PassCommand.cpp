#include "../../include/commands/PassCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
PassCommand::PassCommand() : ICommands() { }

PassCommand::~PassCommand() { }

void PassCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client, const std::string& command) {
	(void) client;

	if (!base->getParameters(command).empty()) {
		// Check if the client has already entered a correct password before.

		if (!Client::isClientAuthenticated(clientSocket, server)) {
			std::string clientPass = base->getParameters(command)[0];
			if (clientPass.empty())
				sendResponse(clientSocket, BOLDRED "ERROR :No password given" RESET "\r\n");

			else if (std::stoi(clientPass) != server->getServPass()) {
				std::string errMsg = BOLDRED "ERROR :Invalid password" RESET "\r\n";
				sendResponse(clientSocket, errMsg);
			}

			// Password accepted
			sendResponse(clientSocket, BOLDGREEN "Password accepted" RESET "\r\n");

			if (server->serverClientsMap[clientSocket] == nullptr) {
				// Create new client object and setting the socket element.
				server->serverClientsMap[clientSocket] = new Client(clientSocket);
				server->serverClientsMap[clientSocket]->setSocket(clientSocket);
			}
		}
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
