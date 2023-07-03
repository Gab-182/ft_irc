#include "../../include/commands/PassCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
PassCommand::PassCommand() : ICommands() { }

PassCommand::~PassCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PassCommand::setClientPass(const std::string& pass) { clientPass = pass; }

std::string PassCommand::getClientPass() const { return (clientPass); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool PassCommand::noErrorsExist(ICommands* base, const int& clientSocket, Server* server, const std::string& command) const {

	if (base->isParameterEmpty(command)) {
		std::string errMsg = ":"
							 ERR_NEEDMOREPARAMS
							 BOLDRED " ERROR :"
							 BOLDWHITE "No password given"
							 RESET "\r\n";
		sendResponse(clientSocket, errMsg);
		return (false);
	}

	if (Client::isClientAuthenticated(clientSocket, server)) {
		std::string errMsg = ":"
							 BOLDRED "ERROR :"
							 BOLDWHITE "Already authenticated"
							 RESET "\r\n";
		sendResponse(clientSocket, errMsg);
		return (false);
	}

	if (getClientPass() != server->getServPass()) {
		std::string errMsg = ":"
							 ERR_PASSWDMISMATCH
							 BOLDRED " ERROR :"
							 BOLDWHITE "Invalid password"
							 RESET "\r\n";
		sendResponse(clientSocket, errMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PassCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	(void) client;
	setClientPass(base->getParameters(command)[0]);
	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	// Password accepted
	if (server->serverClientsMap[clientSocket] == NULL) {
		// Create new client object and setting the socket element.
		server->serverClientsMap[clientSocket] = new Client(clientSocket);
		server->serverClientsMap[clientSocket]->setSocket(clientSocket);
	}

	sendResponse(clientSocket, BOLDGREEN "Password accepted" RESET "\r\n");
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
