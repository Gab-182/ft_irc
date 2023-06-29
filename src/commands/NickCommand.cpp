#include "../../include/commands/NickCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
NickCommand::NickCommand() : ICommands() { }

NickCommand::~NickCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool NickCommand::isDuplicatedNick(const int& clientSocket, const std::string& nickName, Server* server) {
	std::map<int, Client*>::const_iterator it;
	for (it = server->serverClientsMap.begin(); it != server->serverClientsMap.end() ;++it) {
		if (toLowerCase(it->second->getNickName()) == toLowerCase(nickName) && it->first != clientSocket) {
			std::string errMsg = BOLDRED + server->serverClientsMap[clientSocket]->getNickName()
								+ " Duplicated Nickname" + RESET + "\r\n";
			sendResponse(clientSocket, errMsg);
			return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void NickCommand::generateNickName(int clientSocket, Server* server) {
	std::string modifiedNickname = "Guest" + std::to_string(rand() % 1000);

	std::string setNickMsg = BOLDGREEN "Assigning a Guest nickname: " + modifiedNickname + RESET + "\r\n";
	sendResponse(clientSocket, setNickMsg);

	// Generate new nickname
	server->serverClientsMap[clientSocket]->setNickName(modifiedNickname);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool NickCommand::validNickName(int clientSocket, std::string& clientNick, Server* server) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	if (isDuplicatedNick(clientSocket, clientNick, server) || clientNick.empty() || !std::isalpha(clientNick[0])
		|| clientNick.find_first_of(allowedChars) == std::string::npos) {
		std::string errMsg = BOLDRED + server->serverClientsMap[clientSocket]->getNickName()
								+ " Erroneous Nickname" + RESET + "\r\n";
		sendResponse(clientSocket, errMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void NickCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
	(void) client;

	if (!base->getParameters(command).empty()) {
		// Check if the client has already entered a correct password before.

		if (Client::isClientAuthenticated(clientSocket, server)) {
			std::string clientNick = base->getParameters(command)[0];

			// Nickname is too long
			if (clientNick.length() > 9) {
				std::string fixedNick = clientNick.substr(0, 9);
				if (validNickName(clientSocket, fixedNick, server))
					server->serverClientsMap[clientSocket]->setNickName(fixedNick);
			} else if (!validNickName(clientSocket, clientNick, server)) {
				if (server->serverClientsMap[clientSocket]->getNickName().empty())
					generateNickName(clientSocket, server);
			}

			//	Nickname accepted
			else
				server->serverClientsMap[clientSocket]->setNickName(clientNick);

			std::string nickMsg = BOLDGREEN "You're now known as "
								  + server->serverClientsMap[clientSocket]->getNickName()
								  + RESET + "\r\n";
			sendResponse(clientSocket, nickMsg);
		}

		// The client is not authenticated correctly.
		else {
			std::string authErrMsg = BOLDRED "Please make sure you entered: "
									 BOLDWHITE "[PassWord] "
									 BOLDRED "correctly!!" RESET "\r\n";
			sendResponse(clientSocket, authErrMsg);
		}
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
