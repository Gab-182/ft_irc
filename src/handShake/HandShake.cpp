#include "../../include/HandShake.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
HandShake::HandShake() { }

HandShake::~HandShake() {
	if (!_sentMessages.empty())
		_sentMessages.clear();
}

/*-----------------------------------------⟪⟪⟪⟪⟪⟪ Debugging ⟫⟫⟫⟫⟫⟫----------------------------------------------------*/
void HandShake::debugClientData(int clientSocket, Server* server) {
	if (isClientAuthenticated(clientSocket, server)) {
		std::cout << "-------------------------------------------------------------" << std::endl;
		DEBUG_MSG(BOLDMAGENTA << "Connected client Data: " << std::endl << BOLDBLUE
							  << '\t' << " Socket [" << clientSocket << "]" << std::endl
							  << '\t' << " nickName [" << server->serverClientsMap[clientSocket]->getNickName() << "]"
							  << std::endl
							  << '\t' << " userName [" << server->serverClientsMap[clientSocket]->getUserName() << "]"
							  << std::endl
//			<< '\t' << " realName ["	<< _clientData[clientSocket].realName	<< "]" << std::endl
//			<< '\t' << " hostName ["	<< _clientData[clientSocket].hostName	<< "]" << std::endl
		)
	}
}

/*-----------------------------------------⟪⟪⟪⟪⟪⟪ Helpers ⟫⟫⟫⟫⟫⟫------------------------------------------------------*/
void HandShake::welcomeMessage(int clientSocket, Server* server) {
	std::string welcomeMsg = ":"
								+ server->serverClientsMap[clientSocket]->getNickName()
								+ " 001 :Welcome to the Internet Relay Network\r\n";
	sendResponse(clientSocket, welcomeMsg);
}

void HandShake::sendResponse(int clientSocket, const std::string& message) {
	// Check if the message has been sent before
	if (_sentMessages[clientSocket].find(message) == _sentMessages[clientSocket].end()) {
		if (send(clientSocket, message.c_str(), message.size(), 0) == -1)
			DEBUG_MSG("Failed to send message to the client: " << message)
		else
			_sentMessages[clientSocket].insert(message);
	}
}

/*------------------------------------------⟪⟪⟪⟪⟪⟪ NICK ⟫⟫⟫⟫⟫⟫--------------------------------------------------------*/
std::string HandShake::toLowerCase(const std::string& str) {
	std::string lowerCaseStr = str;
	std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(), ::tolower);
	return (lowerCaseStr);
}

bool HandShake::isDuplicatedNick(const int& clientSocket, const std::string& nickName, Server* server) {
	std::map<int, Client*>::const_iterator it;
	for (it = server->serverClientsMap.begin(); it != server->serverClientsMap.end() ;++it) {
		if (toLowerCase(it->second->getNickName()) == toLowerCase(nickName) && it->first != clientSocket)
			return (true);
	}
	return (false);
}

void HandShake::generateNickName(int clientSocket, Server* server) {
	std::string modifiedNickname = "Guest" + std::to_string(rand() % 1000);
	DEBUG_MSG("Assigning a Guest nickname: [" << modifiedNickname << "]")
	sendResponse(clientSocket, "Assigning a Guest nickname: " + modifiedNickname + "\r\n");

	// Generate new nickname
	server->serverClientsMap[clientSocket]->setNickName(modifiedNickname);
}

bool HandShake::validNickName(int clientSocket, std::string& clientNick, Server* server) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	if (isDuplicatedNick(clientSocket, clientNick, server) || clientNick.empty() || !std::isalpha(clientNick[0])
		|| clientNick.find_first_of(allowedChars) == std::string::npos) {
		DEBUG_MSG(BOLDRED << "Duplicated Nickname" << RESET)
		sendResponse(clientSocket, "ERROR :Duplicated nick name\r\n");
		return (false);
	}

	// Nickname is valid
	return (true);
}

void HandShake::processNickMessage(int clientSocket, std::string& clientNick, Server* server) {
	// Nickname is too long
	if (clientNick.length() > 9) {
		std::string fixedNick = clientNick.substr(0, 9);
		if (validNickName(clientSocket, fixedNick, server))
			server->serverClientsMap[clientSocket]->setNickName(fixedNick);
	}
	else if (!validNickName(clientSocket, clientNick, server))
		generateNickName(clientSocket, server);

	//	Nickname accepted
	else
		server->serverClientsMap[clientSocket]->setNickName(clientNick);

	sendResponse(clientSocket, "NICK "
					+ server->serverClientsMap[clientSocket]->getNickName()
					+ "\r\n");
}

/*------------------------------------------⟪⟪⟪⟪⟪⟪ USER ⟫⟫⟫⟫⟫⟫--------------------------------------------------------*/
void HandShake::generateUserName(int clientSocket, Server* server) {
	std::string modifiedUsername = "Guest" + std::to_string(rand() % 1000);
	DEBUG_MSG("Assigning a Guest username: [" << modifiedUsername << "]")
	sendResponse(clientSocket, "Assigning a Guest nickname: " + modifiedUsername + "\r\n");

	// Setting generated username to the client.
	server->serverClientsMap[clientSocket]->setUserName(modifiedUsername);
}

bool HandShake::validUserName(int clientSocket, const std::string& userName, Server* server) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	// Username too long
	if (userName.length() > 16) {
		std::string fixedUserName = userName.substr(0, 16);
		DEBUG_MSG(BOLDRED << "Username is too long, taking only the first 16 characters." << RESET)
		server->serverClientsMap[clientSocket]->setUserName(fixedUserName);
		return (true);
	}

	// Username contains invalid characters
	else if (userName.find_first_not_of(allowedChars) != std::string::npos) {
		DEBUG_MSG(BOLDRED << "Username contains invalid characters" << RESET)
		sendResponse(clientSocket, "ERROR :Invalid characters in user name\r\n");
		return (false);
	}

	// empty Username
	else if (userName.empty()) {
		DEBUG_MSG(BOLDRED << "Empty Username" << RESET)
		sendResponse(clientSocket, "ERROR :Empty user name\r\n");
		return (false);
	}
	return (true);
}

void HandShake::processUserMessage(int clientSocket, std::string& userName, Server* server) {
	if (!validUserName(clientSocket, userName, server))
		generateUserName(clientSocket, server);
		//	Username accepted
	else
		server->serverClientsMap[clientSocket]->setUserName(userName);

	sendResponse(clientSocket, "UserName " +
								server->serverClientsMap[clientSocket]->getUserName()
								+ "\r\n");
//	_clientData[clientSocket].host = host;
}

/*------------------------------------------⟪⟪⟪⟪⟪⟪ PASS ⟫⟫⟫⟫⟫⟫--------------------------------------------------------*/
bool HandShake::processPassMessage(int clientSocket, const std::string& clientPass, Server* server) {
	if (clientPass.empty()) {
		sendResponse(clientSocket, "ERROR :No password given\r\n");
		return (false);
	}

	else if (std::stoi(clientPass) != server->getServPass()) {
		std::string errMsg = BOLDRED "ERROR :Invalid password" RESET "\r\n";
		sendResponse(clientSocket, errMsg);
		return (false);
	}

	// Password accepted
	sendResponse(clientSocket, BOLDGREEN "Password accepted" RESET "\r\n");
	if (server->serverClientsMap[clientSocket] == nullptr) {
		// Create new client object and setting the socket element.
		server->serverClientsMap[clientSocket] = new Client(clientSocket);
		server->serverClientsMap[clientSocket]->setSocket(clientSocket);
	}
	return (true);
}

/*------------------------------------------⟪⟪⟪⟪⟪⟪ MODE ⟫⟫⟫⟫⟫⟫--------------------------------------------------------*/
void HandShake::processModeMessage(int clientSocket, std::istringstream& lineStream, Server* server) {
	std::string mode, modMsg;
	while (lineStream >> mode) {
		if (mode == "+i") {
			modMsg = "MODE "
					+ server->serverClientsMap[clientSocket]->getNickName()
					+ " +i\r\n";
			sendResponse(clientSocket, modMsg);
			break;
		}
	}
}

/*-----------------------------------------⟪⟪⟪⟪⟪⟪ WHOIS ⟫⟫⟫⟫⟫⟫--------------------------------------------------------*/
void HandShake::processWhoisMessage(const int& clientSocket, Server* server) {
	if (isClientAuthenticated(clientSocket, server)) {
		std::string response ="311 "+ server->serverClientsMap[clientSocket]->getNickName()
								+ " " + server->serverClientsMap[clientSocket]->getUserName()
								+ " * :" + server->serverClientsMap[clientSocket]->getUserName()
								+ "\r\n";
		sendResponse(clientSocket, response);
	}
	else
		sendResponse(clientSocket, "401 "
										+ server->serverClientsMap[clientSocket]->getNickName()
										+ " :No such nick/channel\r\n");
}

/*-------------------------------------⟪⟪⟪⟪⟪⟪ Register Client ⟫⟫⟫⟫⟫⟫--------------------------------------------------*/
bool HandShake::isClientRegistered(const int& clientSocket, Server* server) {
	std::map<int, IRC::Client*>::iterator it;
	for (it = server->serverClientsMap.begin(); it != server->serverClientsMap.end(); it++) {
		// First check if the client exist and allocated correctly.
		if (it->second) {
			// Second, compare the sockets.
			if (it->second->getSocket() == clientSocket)
				return (true);
		}
	}
	return (false);
}

bool HandShake::isClientAuthenticated(const int& clientSocket, Server* server) {
	if (server->serverClientsMap[clientSocket] != nullptr
		&& !server->serverClientsMap[clientSocket]->getNickName().empty()
		&& !server->serverClientsMap[clientSocket]->getUserName().empty()) {
		return (true);
	}
	return (false);
}

/*-----------------------------------------⟪⟪⟪⟪⟪⟪ HandShake ⟫⟫⟫⟫⟫⟫----------------------------------------------------*/
int HandShake::processHandShake(int clientSocket, std::string& clientMsg, Server* server) {
	std::string messageLine, command, _parameter;
	std::istringstream messageStream(clientMsg);

	while (std::getline(messageStream, messageLine)) {
		std::istringstream lineStream(messageLine);
		lineStream >> command;
		lineStream >> _parameter;

		/* ⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪⟪ Messages ⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫⟫*/
		if (toLowerCase(command) == "cap" && toLowerCase(_parameter) == "ls")
			sendResponse(clientSocket, "CAP * ACK :302 CAP LS\r\n");

		else if (toLowerCase(command) == "cap" && toLowerCase(_parameter) == "end")
			sendResponse(clientSocket, "CAP * ACK :CAP END\r\n");

		else if (toLowerCase(command) == "pass") {
			if (!processPassMessage(clientSocket, _parameter, server))
				return (0);
		}
		else if (toLowerCase(command) == "nick")
			processNickMessage(clientSocket, _parameter, server);

		else if (toLowerCase(command) == "user")
			processUserMessage(clientSocket, _parameter, server);

		else if (toLowerCase(command) == "mode")
			processModeMessage(clientSocket, lineStream, server);

		else if (toLowerCase(command) == "ping")
			sendResponse(clientSocket, "PONG :ircserv\r\n");
		else if (toLowerCase(command) == "whois")
			processWhoisMessage(clientSocket, server);
	}
	if (isClientAuthenticated(clientSocket, server))
		welcomeMessage(clientSocket, server);
	debugClientData(clientSocket, server);
	return (1);
}

void HandShake::removeClient(int clientSocket, IRC::Server* server) {
	if (isClientAuthenticated(clientSocket, server)) {

		// Delete the client from the serverClientsMap in the server
		std::map<int, Client*>::iterator toDelete;
		toDelete = server->serverClientsMap.find(clientSocket);
		if (toDelete != server->serverClientsMap.end()) {
			// First delete the client object
			delete(toDelete->second);
			// second erase the element from the map
			server->serverClientsMap.erase(toDelete);
		}

		// Delete the client messages from _sentMessages map
		_sentMessages.erase(clientSocket); // ⟫⟫ remove client handShake messages from the map.

		DEBUG_MSG( BOLDRED << "Disconnecting client [" << clientSocket << "]"<< RESET)
		std::string removalMsg = "QUIT :Client disconnected\r\n";
		sendResponse(clientSocket, removalMsg);
	}
	else
		DEBUG_MSG( BOLDRED << "Client [" << clientSocket << "] not found" << RESET)
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
