#include "../../include/HandShake.hpp"
using namespace IRC;

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
HandShake::HandShake() { }

HandShake::~HandShake() { }

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
void HandShake::welcomeMessage(int clientSocket) {
	std::string welcomeMsg = ":" + _clientData[clientSocket].nickName + " 001 :Welcome to the Internet Relay Network\r\n";
	sendResponse(clientSocket, welcomeMsg);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
void HandShake::sendResponse(int clientSocket, const std::string& message) {
	// Check if the message has been sent before
	if (sentMessages[clientSocket].find(message) == sentMessages[clientSocket].end()) {
		if (send(clientSocket, message.c_str(), message.size(), 0) == -1)
			DEBUG_MSG("Failed to send message to the client: " << message)
		else
			sentMessages[clientSocket].insert(message);
	}
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
int HandShake::checkPass(int clientSocket, const std::string& clientPass, const int& serverPass) {
	if (clientPass.empty()) {
		DEBUG_MSG(BOLDRED << "Password not found" << RESET)
		sendResponse(clientSocket, "ERROR :No password given\r\n");
		return (0);
	} else if (std::stoi(clientPass) != serverPass) {
		DEBUG_MSG(BOLDRED << "Invalid password" << RESET)
		sendResponse(clientSocket, "ERROR :Invalid password\r\n");
		return (0);
	}

	// Password accepted
	DEBUG_MSG(BOLDGREEN << "Password accepted" << RESET)
	return (1);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
void HandShake::generateNickName(int clientSocket) {
	std::string modifiedNickname = "Guest" + std::to_string(rand() % 1000);
	DEBUG_MSG("Assigning a Guest nickname: [" << modifiedNickname << "]")
	sendResponse(clientSocket, "Assigning a Guest nickname: " + modifiedNickname + "\r\n");
	_clientData[clientSocket].nickName = modifiedNickname;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
bool HandShake::validNick(int clientSocket, std::string& clientNick) {
	if (clientNick.length() > 9) {
		// Nickname too long
		DEBUG_MSG(BOLDRED << "Nickname is too long, taking only the first 9 characters." << RESET)
		_clientData[clientSocket].nickName = clientNick.substr(0, 9); // Take only the first 9 letters
		return (true);
	}

	else if (!std::isalpha(clientNick[0])) {
		// Nickname doesn't start with a letter
		DEBUG_MSG(BOLDRED << "Nickname must start with a letter" << RESET)
		sendResponse(clientSocket, "ERROR :Nickname must start with a letter\r\n");
		return (false);
	}

	//!!! TODO: Check if nickname is already taken (Duplicate nicknames).
	return (true);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
void HandShake::checkNick(int clientSocket, std::string& clientNick) {
	if (!validNick(clientSocket, clientNick))
		generateNickName(clientSocket);

	//	Nickname accepted
	sendResponse(clientSocket, "NICK " + clientNick + "\r\n");
	_clientData[clientSocket].nickName = clientNick;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
void HandShake::checkName(int clientSocket, const std::string& userName) {
	std::string modifiedUsername = userName;

	if (userName.empty())
		sendResponse(clientSocket, "ERROR :No user name given\r\n");
	// Check if the username duplicated.
	modifiedUsername = userName + std::to_string(rand() % 1000);

	_clientData[clientSocket].userName = modifiedUsername;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
void HandShake::handleMode(int clientSocket, std::istringstream& lineStream) {
	std::string mode, modMsg;
	while (lineStream >> mode) {
		if (mode == "+i") {
			modMsg = "MODE " + _clientData[clientSocket].nickName + " +i\r\n";
			sendResponse(clientSocket, modMsg);
			break;
		}
	}
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
int HandShake::processHandShake(int clientSocket, std::string& clientMsg, const int& serverPass) {
	std::string messageLine, command, option;
	std::istringstream messageStream(clientMsg);

	while (std::getline(messageStream, messageLine)) {
		std::istringstream lineStream(messageLine);
		lineStream >> command;
		lineStream >> option;
	/* ❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎︎❄❄︎❄︎❄︎❄︎︎❄︎❄︎❄︎ CAP LS ❄︎❄︎❄︎❄︎❄❄︎❄︎❄❄❄︎❄︎︎❄︎︎❄︎︎❄︎❄︎❄︎❄︎❄︎❄︎*/
		if (command == "CAP" && option == "LS")
			sendResponse(clientSocket, "CAP * ACK :302 CAP LS\r\n");

	/* ❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎︎❄❄︎❄︎❄︎❄︎︎❄︎❄︎❄︎ CAP END ❄︎❄︎❄︎❄︎❄❄︎❄︎❄❄❄︎❄︎︎❄︎︎❄︎︎❄︎❄︎❄︎❄︎❄︎❄︎*/
		else if (command == "CAP" && option == "END")
			sendResponse(clientSocket, "CAP * ACK :CAP END\r\n");

	/* ❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎︎❄❄︎❄︎❄︎❄︎︎❄︎❄︎❄︎ PASS ❄︎❄︎❄︎❄︎❄❄︎❄︎❄❄❄︎❄︎︎❄︎︎❄︎︎❄︎❄︎❄︎❄︎❄︎❄︎*/
		else if (command == "PASS") {
			if (!checkPass(clientSocket, option, serverPass))
				return (0);
		}

	/* ❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎︎❄❄︎❄︎❄︎❄︎︎❄︎❄︎❄︎ NICK ❄︎❄︎❄︎❄︎❄❄︎❄︎❄❄❄︎❄︎︎❄︎︎❄︎︎❄︎❄︎❄︎❄︎❄︎❄︎*/
		else if (command == "NICK")
			checkNick(clientSocket, option);

	/* ❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎︎❄❄︎❄︎❄︎❄︎︎❄︎❄︎❄︎ USER ❄︎❄︎❄︎❄︎❄❄︎❄︎❄❄❄︎❄︎︎❄︎︎❄︎︎❄︎❄︎❄︎❄︎❄︎❄︎*/
		else if (command == "USER") {
			std::string userName, host, realName;
			lineStream >> userName >> host;
			std::getline(lineStream, realName);
			checkName(clientSocket, userName);
			_clientData[clientSocket].realName = realName.substr(2); // Remove leading space after ':'
			_clientData[clientSocket].host = host;
		}

	/* ❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎︎❄❄︎❄︎❄︎❄︎❄︎︎❄︎❄︎❄︎ MODE ❄︎❄︎❄︎❄︎❄❄︎❄︎❄︎❄❄❄︎❄︎︎❄︎︎❄︎︎❄︎❄︎❄︎❄︎❄︎❄︎*/
		else if (command == "MODE") // MODE +i
			handleMode(clientSocket, lineStream);

		else if (command == "PING")
			sendResponse(clientSocket, "PONG :ircserv\r\n");
	}
	welcomeMessage(clientSocket);
	DEBUG_MSG( BOLDMAGENTA << "Connected client Data: " << std::endl << BOLDBLUE
				<< "  Socket ["		<< clientSocket << "]" << std::endl
				<< "  Nick name ["	<< _clientData[clientSocket].nickName	<< "]" << std::endl
				<< "  User name ["	<< _clientData[clientSocket].userName	<< "]" << std::endl
				<< "  Real name ["	<< _clientData[clientSocket].realName	<< "]" << std::endl
				<< "  Host ["	<< _clientData[clientSocket].host			<< "]" << std::endl)
	return (1);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄︎❄*/
