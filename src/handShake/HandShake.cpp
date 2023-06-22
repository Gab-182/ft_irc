#include "../../include/HandShake.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*-------------------------------------------------------------------------------------------------------------*/
HandShake::HandShake() { }
/*.............................................................................................................*/
HandShake::~HandShake() {
	if (!_clientData.empty())
		_clientData.clear();
	if (!_sentMessages.empty())
		_sentMessages.clear();
}

/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------⟪⟪⟪⟪⟪⟪ Debugging ⟫⟫⟫⟫⟫⟫---------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
void HandShake::debugClientData(int clientSocket) {
	std::cout << "-------------------------------------------------------------" << std::endl;
	DEBUG_MSG( BOLDMAGENTA  << "Connected client Data: " << std::endl << BOLDBLUE
			<< '\t' << " Socket ["		<< clientSocket << "]" << std::endl
			<< '\t' << " nickName ["	<< _clientData[clientSocket].nickName	<< "]" << std::endl
			<< '\t' << " userName ["	<< _clientData[clientSocket].userName	<< "]" << std::endl
//			<< '\t' << " realName ["	<< _clientData[clientSocket].realName	<< "]" << std::endl
//			<< '\t' << " hostName ["	<< _clientData[clientSocket].hostName	<< "]" << std::endl
			)
}

/*-------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------⟪⟪⟪⟪⟪⟪ Helpers ⟫⟫⟫⟫⟫⟫----------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
void HandShake::welcomeMessage(int clientSocket) {
	std::string welcomeMsg = ":" + _clientData[clientSocket].nickName + " 001 :Welcome to the Internet Relay Network\r\n";
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

/*-------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------⟪⟪⟪⟪⟪⟪ NICK ⟫⟫⟫⟫⟫⟫------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
std::string HandShake::toLowerCase(const std::string& str) {
	std::string lowerCaseStr = str;
	std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(), ::tolower);
	return (lowerCaseStr);
}

/**
 ** TODO: isDuplicateNick() is not working properly, it keep false even if the nick is duplicated
 **/
bool HandShake::isDuplicatedNick(const int& clientSocket, const std::string& nickName) {
	std::map<int, ClientData>::const_iterator it;
	for (it = _clientData.begin(); it != _clientData.end(); ++it) {
		if (toLowerCase(it->second.nickName) == toLowerCase(nickName) && it->first != clientSocket)
			return (true);
	}
	return (false);
}

void HandShake::generateNickName(int clientSocket) {
	std::string modifiedNickname = "Guest" + std::to_string(rand() % 1000);
	DEBUG_MSG("Assigning a Guest nickname: [" << modifiedNickname << "]")
	sendResponse(clientSocket, "Assigning a Guest nickname: " + modifiedNickname + "\r\n");
	_clientData[clientSocket].nickName = modifiedNickname;
}

bool HandShake::validNickName(int clientSocket, std::string& clientNick) {
	std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";

	if (isDuplicatedNick(clientSocket, clientNick) || clientNick.empty() || !std::isalpha(clientNick[0]) 
		|| clientNick.find_first_of(allowedChars) == std::string::npos) {
		DEBUG_MSG(BOLDRED << "Duplicated Nickname" << RESET)
		sendResponse(clientSocket, "ERROR :Duplicated nick name\r\n");
		return (false);
	}

	// Nickname is valid
	return (true);
}

void HandShake::processNickMessage(int clientSocket, std::string& clientNick) {
	// Nickname is too long
	if (clientNick.length() > 9)
		_clientData[clientSocket].nickName = clientNick.substr(0, 9); // Take only the first 9 letters

	else if (!validNickName(clientSocket, clientNick))
		generateNickName(clientSocket);

		//	Nickname accepted
	else
		_clientData[clientSocket].nickName = clientNick;
	sendResponse(clientSocket, "NICK " + _clientData[clientSocket].nickName + "\r\n");
}

/*-------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------⟪⟪⟪⟪⟪⟪ USER ⟫⟫⟫⟫⟫⟫------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
void HandShake::generateUserName(int clientSocket) {
	std::string modifiedUsername = "Guest" + std::to_string(rand() % 1000);
	DEBUG_MSG("Assigning a Guest username: [" << modifiedUsername << "]")
	sendResponse(clientSocket, "Assigning a Guest nickname: " + modifiedUsername + "\r\n");
	_clientData[clientSocket].nickName = modifiedUsername;
}

bool HandShake::validUserName(int clientSocket, const std::string& userName) {
	// Username too long
	if (userName.length() > 16) {
		DEBUG_MSG(BOLDRED << "Username is too long, taking only the first 16 characters." << RESET)
		_clientData[clientSocket].userName = userName.substr(0, 16); // Take only the first 9 letters
		return (true);
	}

		// Username contains invalid characters
	else if (userName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_") != std::string::npos) {
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

void HandShake::processUserMessage(int clientSocket, std::string& userName) {
	if (!validUserName(clientSocket, userName))
		generateUserName(clientSocket);
		//	Username accepted
	else
		_clientData[clientSocket].userName = userName;
	sendResponse(clientSocket, "UserName " + userName + "\r\n");
//	_clientData[clientSocket].host = host;
}

/*-------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------⟪⟪⟪⟪⟪⟪ PASS ⟫⟫⟫⟫⟫⟫------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
bool HandShake::processPassMessage(int clientSocket, const std::string& clientPass, const int& serverPass) {
	if (clientPass.empty()) {
		DEBUG_MSG(BOLDRED << "Password not found" << RESET)
		sendResponse(clientSocket, "ERROR :No password given\r\n");
		return (false);
	}

	else if (std::stoi(clientPass) != serverPass) {
		DEBUG_MSG(BOLDRED << "Invalid password" << RESET)
		sendResponse(clientSocket, "ERROR :Invalid password\r\n");
		return (false);
	}

	// Password accepted
	DEBUG_MSG(BOLDGREEN << "Password accepted" << RESET)
	return (true);
}

/*-------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------⟪⟪⟪⟪⟪⟪ MODE ⟫⟫⟫⟫⟫⟫------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
void HandShake::processModeMessage(int clientSocket, std::istringstream& lineStream) {
	std::string mode, modMsg;
	while (lineStream >> mode) {
		if (mode == "+i") {
			modMsg = "MODE " + _clientData[clientSocket].nickName + " +i\r\n";
			sendResponse(clientSocket, modMsg);
			break;
		}
	}
}

/*-------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------⟪⟪⟪⟪⟪⟪ WHOIS ⟫⟫⟫⟫⟫⟫------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
void HandShake::processWhoisMessage(const int& clientSocket) {
	if (isClientAuthenticated(clientSocket)) {
		std::string response ="311 "+ _clientData[clientSocket].nickName
								+ " " + _clientData[clientSocket].userName
								+ " * :" + _clientData[clientSocket].userName + "\r\n";
		sendResponse(clientSocket, response);
	}
	else
		sendResponse(clientSocket, "401 " + _clientData[clientSocket].nickName + " :No such nick/channel\r\n");
}

/*-------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------⟪⟪⟪⟪⟪⟪ Register Client ⟫⟫⟫⟫⟫⟫------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
bool HandShake::isClientRegistered(const int& clientSocket, Server* server) {
	std::map<int, IRC::Client*>::iterator it;
	for (it = server->serverClientsMap.begin(); it != server->serverClientsMap.end(); it++) {
		if (it->second->getSocket() == clientSocket)
			return (true);
	}
	return (false);
}

bool HandShake::isClientAuthenticated(const int& clientSocket) {
	if (!_clientData[clientSocket].nickName.empty() &&
		!_clientData[clientSocket].userName.empty()) {
		return (true);
	}
	return (false);
}

void HandShake::registerClient(const int& clientSocket, Server* server) {
	if (isClientAuthenticated(clientSocket) && !isClientRegistered(clientSocket, server)) {
		Client* client = new Client();
		client->setNickName(_clientData[clientSocket].nickName);
		client->setUserName(_clientData[clientSocket].userName);
		client->setSocket(clientSocket);
		client->setIsRegistered(true);

		server->serverClientsMap[clientSocket] = client;
		delete client;
		DEBUG_MSG(BOLDGREEN << "Client Registered !!")
	}
}

/*-------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------⟪⟪⟪⟪⟪⟪ HandShake ⟫⟫⟫⟫⟫⟫---------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------*/
int HandShake::processHandShake(int clientSocket, std::string& clientMsg, const int& serverPass) {
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
			if (!processPassMessage(clientSocket, _parameter, serverPass))
				return (0);
		}

		else if (toLowerCase(command) == "nick")
			processNickMessage(clientSocket, _parameter);

		else if (toLowerCase(command) == "user")
			processUserMessage(clientSocket, _parameter);

		else if (toLowerCase(command) == "mode")
			processModeMessage(clientSocket, lineStream);

		else if (toLowerCase(command) == "ping")
			sendResponse(clientSocket, "PONG :ircserv\r\n");
		else if (toLowerCase(command) == "whois")
			processWhoisMessage(clientSocket);
	}
	if (isClientAuthenticated(clientSocket))
		welcomeMessage(clientSocket);
	debugClientData(clientSocket);
	return (1);
}

void HandShake::removeClient(int clientSocket, IRC::Server* server) {
	if (isClientAuthenticated(clientSocket)) {
		_clientData.erase(clientSocket); // ⟫⟫ remove client data from the  map
		_sentMessages.erase(clientSocket); // ⟫⟫ remove client handShake messages from the map.
		std::map<int, IRC::Client*>::iterator it;
		for (it = server->serverClientsMap.begin(); it != server->serverClientsMap.end(); it++) {
			if (it->second->getSocket() == clientSocket) {
				it->second->~Client(); // ⟫⟫ delete client object.
				server->serverClientsMap.erase(it->first); // ⟫⟫ remove client from the clients map.
				break;
			}
		}

		DEBUG_MSG( BOLDRED << "Disconnecting client [" << clientSocket << "]"<< RESET)
		std::string removalMsg = "QUIT :Client disconnected\r\n";
		sendResponse(clientSocket, removalMsg);
	}
	else
		DEBUG_MSG( BOLDRED << "Client [" << clientSocket << "] not found" << RESET)
}

/*-------------------------------------------------------------------------------------------------------------*/