#include "../../include/commands/NickCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
NickCommand::NickCommand() : ICommands() { }

NickCommand::~NickCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
// "<nick> :Nickname is already in use"
bool NickCommand::isDuplicatedNick(const int& clientSocket, const std::string& nickName, Server* server) {
	std::map<int, Client*>::const_iterator it;
	for (it = server->serverClientsMap.begin(); it != server->serverClientsMap.end() ;++it) {
		if (toLowerCase(it->second->getNickName()) == toLowerCase(nickName) && it->first != clientSocket) {
			std::string nickErrMsg = server->serverClientsMap[clientSocket]->getNickName()
									 + " :"
									 + " " ERR_NICKNAMEINUSE " "
									 + "Nickname is already in use"
									 + "\r\n";
			sendResponse(clientSocket, nickErrMsg);
			return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void NickCommand::generateNickName(int clientSocket, Server* server) {
	std::stringstream ss;

	int randomNumber = std::rand() % 1000;
	ss << "Guest" << randomNumber;
	std::string modifiedNickname = ss.str();

	// Generate new nickname
	std::string setNickMsg = ":" + server->serverClientsMap[clientSocket]->getNickName()
				+ " NICK :" + modifiedNickname + "\r\n";
	server->serverClientsMap[clientSocket]->setNickName(modifiedNickname);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool NickCommand::validNickName(int clientSocket, std::string& clientNick, Server* server) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	if (isDuplicatedNick(clientSocket, clientNick, server) || clientNick.empty() || !std::isalpha(clientNick[0])
		|| clientNick.find_first_of(allowedChars) == std::string::npos) {
		std::string nickErrMsg = server->serverClientsMap[clientSocket]->getNickName()
								 + " :"
								 " " ERR_ERRONEUSNICKNAME " "
								+ "Erroneous Nickname"
								+ "\r\n";
		sendResponse(clientSocket, nickErrMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void NickCommand::processNickCommand(const int& clientSocket, std::string& clientNick, Server* server) {
	std::string fixedNick = clientNick.substr(0, 9);
	std::string nickMsg;

	if (!validNickName(clientSocket, fixedNick, server)) {
		if (server->serverClientsMap[clientSocket]->getNickName().empty())
			generateNickName(clientSocket, server);
	}

	//	Nickname accepted
	else {
		nickMsg = ":" + server->serverClientsMap[clientSocket]->getNickName()
					+ " NICK :" + fixedNick + "\r\n";
		server->serverClientsMap[clientSocket]->setNickName(fixedNick);
	}
	sendResponse(clientSocket, nickMsg);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool NickCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
	// Check if client is authenticated
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
								 BOLDYELLOW "/nick "
								 BOLDWHITE "<nickname> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void NickCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
	(void) client;

	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	std::string clientNick = base->getParameters(command)[0];
	processNickCommand(clientSocket, clientNick, server);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
