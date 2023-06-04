#include "../../include/MsgParser.hpp"
using namespace IRC;

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
MsgParser::MsgParser() { }

MsgParser::~MsgParser() { }

MsgParser::MsgParser(const MsgParser &other) {
	if (this != &other)
		*this = other;
}

//MsgParser& MsgParser::operator=(const MsgParser &other) {
//	if (this != &other) {
//		*this = other;
//	}
//	return (*this);
//}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
std::string MsgParser::generateGuestNick() {
	static int guestCount = 1;
	std::string guestNick = "Guest-" + std::to_string(guestCount++);
	return guestNick;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
bool MsgParser::duplicatedClient(const std::string& name) {
	std::map<int, std::string>::const_iterator it;
	for (it = clientsNicks.begin(); it != clientsNicks.end(); ++it) {
		if (it->second == name)
			return (true);  // Duplicated nickname or username found
	}
	return (false);  // Duplicated name not found
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::welcomeMessage(int clientSocket) {
	std::string welcomeMsg = ":" + clientsNicks[clientSocket] + " 001 " + clientsNicks[clientSocket] + " :Welcome to the Internet Relay Network\r\n";
	sendResponse(clientSocket, welcomeMsg);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::sendResponse(int clientSocket, const std::string& message) {
	// Check if the message has been sent before
	if (sentMessages.find(message) == sentMessages.end()) {
		if (send(clientSocket, message.c_str(), message.size(), 0) == -1)
			DEBUG_MSG("Failed to send message to the client: " << message)
		else
			// Add the message to the set of sent messages
			sentMessages.insert(message);
	}
}


/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int MsgParser::checkPass(int clientSocket, const std::string& clientPass, const int& serverPass) {
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
int MsgParser::checkNick(int clientSocket, const std::string& clientNick) {
	if (clientNick.empty()) {
		DEBUG_MSG(BOLDRED << "Nickname not found" << RESET)
		std::string errorMsg = "ERROR :No nickname given\r\n";
		sendResponse(clientSocket, errorMsg);
		return 0;
	/**
	 ** @gab-182
	 ** TODO: When the nick is duplicated,
	 ** 	check if the nick inside the map have the same socket as the new one,
	 **		Cause that mean -> the same client is trying to send nick command again.
	 **/
	} else if (duplicatedClient(clientNick) && clientsNicks.find(clientSocket) == clientsNicks.end()) {
		std::string modifiedNickname;
		modifiedNickname = clientNick + std::to_string(rand() % 1000);
		DEBUG_MSG("Assigning a Guest nickname: [" << modifiedNickname << "]")
		std::string nickMsg = "Assigning a Guest nickname: "+modifiedNickname+"\r\n";
		sendResponse(clientSocket, nickMsg);
		clientsNicks[clientSocket] = modifiedNickname;
		clientsData[clientSocket].first = modifiedNickname;
	}

	clientsNicks[clientSocket] = clientNick;
	clientsData[clientSocket].first = clientNick;
	std::string nickMsg = "NICK " + clientNick + "\r\n";
	sendResponse(clientSocket, nickMsg);
	// DEBUG_MSG("Nickname accepted: [" << clientsNicks[clientSocket] << "]")
	return 1;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::checkName(int clientSocket, const std::string& clientName, const std::string& realname, const std::string& ip) {
	std::string modifiedUsername = clientName;

	if (clientName.empty())
		sendResponse(clientSocket, "ERROR :No user name given\r\n");
	else if (duplicatedClient(clientsData[clientSocket].second))
		modifiedUsername = clientName + std::to_string(rand() % 1000);
	clientsData[clientSocket].second = modifiedUsername;
	DEBUG_MSG("Client " << clientSocket << std::endl
						<< "User name: " << clientsData[clientSocket].second << std::endl
						<< "Real name: " << realname << std::endl
						<< "HOST: " << ip <<  std::endl)
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::processHandShake(int clientSocket, const std::string& clientMsg, const int& serverPass) {
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
				return;
			}
		} else if (command == "NICK") {
			std::string clientNick;
			iss >> clientNick;
			if (!checkNick(clientSocket, clientNick)) {
				return;
			}
		} else if (command == "USER") {
			std::string username, realName, ip, separator, realNameWithSpaces;
			iss >> username >> realName >> ip >> separator;
			std::getline(iss, realNameWithSpaces);
			std::string clientName = realName + " " + realNameWithSpaces.substr(1);
			checkName(clientSocket, username, clientName, ip);
		} else if (command == "CAP" && iss.peek() == 'E') { // CAP END
			std::string endMsg;
			std::getline(iss, endMsg);
			break;
		} else if (command == "MODE") { // MODE +i
			std::string mode, target;
			iss >> target >> mode;
			if (target == clientsNicks[clientSocket] && mode == "+i")
				sendResponse(clientSocket, "MODE " + target + " +i\r\n");
		} else if (command == "PING") {
			std::string pingMsg = "PONG :ircserv\r\n";
			sendResponse(clientSocket, pingMsg);
		}
	}
	welcomeMessage(clientSocket);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/