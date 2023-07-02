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
		std::string errMsg = ": ERROR: "
							 BOLDRED + server->serverClientsMap[clientSocket]->getUserName()
							 + BOLDWHITE " Erroneous Username"
							 + RESET + "\r\n";
		sendResponse(clientSocket, errMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void UserCommand::processUserName(const int& clientSocket ,std::string& userName, Server* server) {
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

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool UserCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
	// Client is not authenticated yet
	if (!Client::isClientAuthenticated(clientSocket, server)) {
		DEBUG_MSG(BOLDRED << " client not authenticated yet!! ")

		std::string authErrMsg = ": "
								 ERR_PASSWDMISMATCH
								 BOLDRED " Please make sure you entered: "
								 BOLDWHITE "[PassWord] "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

	// Check if parameters are empty
	if (base->isParameterEmpty(command)) {
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string authErrMsg = ":"
								 ERR_NEEDMOREPARAMS
								 BOLDRED " Please make sure you entered: "
								 BOLDYELLOW "/user "
								 BOLDWHITE "<username> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void UserCommand::executeCommand(ICommands* base,  const int& clientSocket, Server* server, Client* client, const std::string& command) {
	(void) client;

	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	std::string userName = base->getParameters(command)[0];
	processUserName(clientSocket, userName, server);

	// Welcome client
	if (client->isClientRegistered(clientSocket, server)) {
		std::map<int, Client*>::iterator itClient;
		itClient = server->serverClientsMap.find(clientSocket);
		if (itClient != server->serverClientsMap.end()) {
			if (!itClient->second->isClientWelcomed()) {
				ICommands::welcomeMessage(clientSocket, server);
				itClient->second->welcomeClient(true);
			}
		}
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
