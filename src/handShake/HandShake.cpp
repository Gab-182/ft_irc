#include "../../include/HandShake.hpp"
using namespace IRC;

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
HandShake::HandShake() { }

HandShake::~HandShake() { }

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
bool HandShake::duplicatedUser(const std::string& name) {
	std::map<int, std::string>::const_iterator it;
	for (it = clientsNicks.begin(); it != clientsNicks.end(); ++it) {
		if (it->second == name)
			return (true);  // Duplicated nickname or username found
	}
	return (false);  // Duplicated name not found
}

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
		return 0;
	} else if (std::stoi(clientPass) != serverPass) {
		DEBUG_MSG(BOLDRED << "Invalid password" << RESET)
		std::string errorMsg = "ERROR :Invalid password\r\n";
		sendResponse(clientSocket, errorMsg);
		return 0;
	}

	// Password accepted
	DEBUG_MSG(BOLDGREEN << "Password accepted" << RESET)
	return 1;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::generateNickName() {
	std::string modifiedNickname = Guest + std::to_string(rand() % 1000);
	DEBUG_MSG("Assigning a Guest nickname: [" << modifiedNickname << "]")
	std::string nickMsg = "Assigning a Guest nickname: " + modifiedNickname + "\r\n";
	sendResponse(clientSocket, nickMsg);
	clientsNicks[clientSocket] = modifiedNickname;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
bool HandShake::validNick(const std::string& clientNick) {
	if (clientNick.length() > 9) {
		// Nickname too long
		DEBUG_MSG(BOLDRED << "Nickname is too long" << RESET)
		std::string errorMsg = "ERROR :Nickname is too long\r\n";
		sendResponse(clientSocket, errorMsg);
		return (false);
	}

	else if (!std::isalpha(clientNick[0])) {
		// Nickname doesn't start with a letter
		DEBUG_MSG(BOLDRED << "Nickname must start with a letter" << RESET)
		std::string errorMsg = "ERROR :Nickname must start with a letter\r\n";
		sendResponse(clientSocket, errorMsg);
		return (false);
	}
	else if (duplicatedUser(clientNick) && clientsNicks.find(clientSocket) != clientsNicks.end())
		return (false);
	return (true);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::checkNick(int clientSocket, const std::string& clientNick) {
	if (!validNick(clientNick))
		generateNickName();

	// Nickname accepted
	clientsNicks[clientSocket] = clientNick;
	clientsData[clientSocket].first = clientNick;
	std::string nickMsg = "NICK " + clientNick + "\r\n";
	sendResponse(clientSocket, nickMsg);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void HandShake::checkName(int clientSocket, const std::string& clientName, const std::string& realname, const std::string& ip) {
	std::string modifiedUsername = clientName;

	if (clientName.empty())
		sendResponse(clientSocket, "ERROR :No user name given\r\n");
	else if (duplicatedUser(clientsData[clientSocket].second))
		modifiedUsername = clientName + std::to_string(rand() % 1000);
	clientsData[clientSocket].second = modifiedUsername;
	DEBUG_MSG("Client " << clientSocket << std::endl
						<< "User name: " << clientsData[clientSocket].second << std::endl
						<< "Real name: " << realname << std::endl
						<< "HOST: " << ip <<  std::endl)
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
			if (!checkNick(clientSocket, clientNick)) {
				return (0);
			}
		} else if (command == "USER") {
			std::string username, realName, ip, separator, realNameWithSpaces;
			iss >> username >> realName >> ip >> separator;
			std::getline(iss, realNameWithSpaces);
			std::string clientName = realName + " " + realNameWithSpaces.substr(1);
			checkName(clientSocket, username, clientName, ip);
		} else if (command == "MODE") // MODE +i
			handleMode(clientSocket, iss);
		else if (command == "PING")
			sendResponse(clientSocket, "PONG :ircserv\r\n");
	}
	welcomeMessage(clientSocket);
	return (1);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/