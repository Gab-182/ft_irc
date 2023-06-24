#include "../../include/commands/UserCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
UserCommand::UserCommand() : ICommands() { }

UserCommand::~UserCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void UserCommand::generateUserName(int clientSocket, Server* server) {
	std::string modifiedUsername = "Guest" + std::to_string(rand() % 1000);

	std::string setUserMsg = BOLDGREEN "Assigning a Guest Username: " + modifiedUsername + RESET + "\r\n";
	sendResponse(clientSocket, setUserMsg);

	// Generate new username
	server->serverClientsMap[clientSocket]->setUserName(modifiedUsername);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool UserCommand::validUserName(int clientSocket, std::string& userName, Server* server) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	if (userName.empty() || !std::isalpha(userName[0])
		|| userName.find_first_of(allowedChars) == std::string::npos) {
		std::string errMsg = BOLDRED + server->serverClientsMap[clientSocket]->getUserName()
							 + " Erroneous Username" + RESET + "\r\n";
		sendResponse(clientSocket, errMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void UserCommand::executeCommand(ICommands* base,  const int& clientSocket, Server* server, Client& client) {
	(void) client;

	if (!base->getParameters().empty()) {
		std::string userName = base->getParameters()[0];

		// Username is too long
		if (userName.length() > 16) {
			std::string fixedUser = userName.substr(0, 16);
			if (validUserName(clientSocket, fixedUser, server))
				server->serverClientsMap[clientSocket]->setUserName(fixedUser);
		}
		else if (!validUserName(clientSocket, userName, server)) {
			if (server->serverClientsMap[clientSocket]->getUserName().empty())
				generateUserName(clientSocket, server);
		}

			//	userName accepted
		else
			server->serverClientsMap[clientSocket]->setUserName(userName);

		std::string userMsg = BOLDGREEN "You're username now is "
							  + server->serverClientsMap[clientSocket]->getUserName()
							  + RESET + "\r\n";
		sendResponse(clientSocket, userMsg);
	}

	// Cleaning the parameters vector before adding new ones to it.
	base->getParameters().clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
