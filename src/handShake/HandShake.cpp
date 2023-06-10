#include "../../include/HandShake.hpp"
using namespace IRC;

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
HandShake::HandShake() { }

HandShake::~HandShake() { }

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::welcomeMessage(int clientSocket) {
	std::string welcomeMsg = "001 :Welcome to the Internet Relay Network \r\n";
//	std::string welcomeMsg = ":" + clientsNicks[clientSocket] + " 001 " + clientsNicks[clientSocket] + " :Welcome to the Internet Relay Network\r\n";
	sendResponse(clientSocket, welcomeMsg);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::sendResponse(int clientSocket, const std::string& message) {
	// Check if the message has been sent before
//	if (sentMessages[clientSocket].find(message) == sentMessages[clientSocket].end()) {
		if (send(clientSocket, message.c_str(), message.size(), 0) == -1)
			DEBUG_MSG("Failed to send message to the client: " << message)
//		else
//			sentMessages[clientSocket].insert(message);
//	}
}


/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int HandShake::checkPass(int clientSocket, const std::string& clientPass, const int& serverPass) {
	if (clientPass.empty()) {
		DEBUG_MSG(BOLDRED << "Password not found" << RESET)
		std::string errorMsg = "ERROR :No password given\r\n";
		sendResponse(clientSocket, errorMsg);
		return (0);
	} else if (std::stoi(clientPass) != serverPass) {
		DEBUG_MSG(BOLDRED << "Invalid password" << RESET)
		std::string errorMsg = "ERROR :Invalid password\r\n";
		sendResponse(clientSocket, errorMsg);
		return (0);
	}

	// Password accepted
	DEBUG_MSG(BOLDGREEN << "Password accepted" << RESET)
	// If the client access the server successfully, save its socket.
	_clientData.clientSocket = clientSocket;
	return (1);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::generateNickName(int clientSocket) {
	std::string modifiedNickname = "Guest" + std::to_string(rand() % 1000);
	DEBUG_MSG("Assigning a Guest nickname: [" << modifiedNickname << "]")
	std::string nickMsg = "Assigning a Guest nickname: " + modifiedNickname + "\r\n";
	sendResponse(clientSocket, nickMsg);

	_clientData.nickName = modifiedNickname;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
bool HandShake::validNick(int clientSocket, std::string& clientNick) {
	if (clientNick.length() > 9) {
		// Nickname too long
		DEBUG_MSG(BOLDRED << "Nickname is too long, taking only the first 9 characters." << RESET)
		clientNick = clientNick.substr(0, 9); // Take only the first 9 letters
		return (true);
	}

	else if (!std::isalpha(clientNick[0])) {
		// Nickname doesn't start with a letter
		DEBUG_MSG(BOLDRED << "Nickname must start with a letter" << RESET)
		std::string errorMsg = "ERROR :Nickname must start with a letter\r\n";
		sendResponse(clientSocket, errorMsg);
		return (false);
	}

	else if (_clientData.nickName == clientNick)
		return (false);
	return (true);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::checkNick(int clientSocket, std::string& clientNick) {
	if (!validNick(clientSocket, clientNick))
		generateNickName(clientSocket);

	std::string nickMsg = "NICK " + clientNick + "\r\n";
	sendResponse(clientSocket, nickMsg);

//	Nickname accepted
	_clientData.nickName = clientNick;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::checkName(int clientSocket, const std::string& userName) {
	std::string modifiedUsername = userName;

	if (userName.empty())
		sendResponse(clientSocket, "ERROR :No user name given\r\n");
	else if (_clientData.userName == userName)
		modifiedUsername = userName + std::to_string(rand() % 1000);

	_clientData.userName = modifiedUsername;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::handleMode(int clientSocket, std::istringstream& iss) {
	std::string mode;
	while (iss >> mode) {
		if (mode == "+i") {
			sendResponse(clientSocket, "MODE set to +i\r\n");
			break;
		}
	}
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int HandShake::processHandShake(int clientSocket, const std::string& clientMsg, const int& serverPass) {
	std::istringstream iss(clientMsg);
	std::string command;

	while (iss >> command) {
		if (command == "CAP" && iss.peek() == 'L') // CAP LS
			sendResponse(clientSocket, "CAP * ACK :302 CAP LS\r\n");
		else if (command == "PASS") {
			std::string password;
			iss >> password;
			if (!checkPass(clientSocket, password, serverPass)) {
				DEBUG_MSG(BOLDRED << "Password not accepted")
				return (0);
			}
		} else if (command == "NICK") {
			std::string clientNick;
			iss >> clientNick;
			checkNick(clientSocket, clientNick);
		} else if (command == "USER") {
			std::string userNick, userName, host, realName;
			if (iss >> userNick >> userName >> host) {
				std::getline(iss, realName, ':');
				checkName(clientSocket, userName);
				_clientData.realName = realName.substr(1); // Remove leading space after ':'
				_clientData.ip = host;
			} else
				sendResponse(clientSocket, "ERROR :No user name given\r\n");
		} else if (command == "MODE") // MODE +i
			handleMode(clientSocket, iss);
		else if (command == "PING")
			sendResponse(clientSocket, "PONG :ircserv\r\n");
	}
	welcomeMessage(clientSocket);
	DEBUG_MSG("Socket ["<< _clientData.clientSocket << "]" << std::endl
				<< " User name [" << _clientData.userName << "]" << std::endl
				<< " Nick name [" << _clientData.nickName << "]" << std::endl
				<< " Real name [" << _clientData.realName << "]" << std::endl )
	return (1);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/