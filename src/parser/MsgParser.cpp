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
// Function to send a message to the client
void MsgParser::sendResponse(int clientSocket, const std::string& message) {
	// Check if the message has been sent before
	if (sentMessages.find(message) == sentMessages.end()) {
		if (send(clientSocket, message.c_str(), message.size(), 0) == -1) {
			std::cout << BOLDRED << "🟡 Failed to send message to the client: " << message << " 🔴" << RESET << std::endl;
		} else {
			// Add the message to the set of sent messages
			sentMessages.insert(message);
		}
	}
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::checkName(int clientSocket, const std::string& clientName, const std::string& clientRealName) {
	if (clientName.empty()) {
		std::cout << BOLDRED << "🟡 user name not found 🔴" << RESET << std::endl;
		std::string errorMsg = "ERROR :No user name given\r\n";
		sendResponse(clientSocket, errorMsg);

	}
//	else if (duplicatedClient(clientName)) {
//		/*
//		 ** TODO: Changing the userName by adding random  numbers to it.
//		 */
//	}
	else {
		std::cout << BOLDGREEN << "🟡 user name and real name are valid 🔴" << RESET << std::endl;
		clientsNicks[clientSocket] = clientName;
		std::cout << BOLDWHITE << "🟡Client user name: [" << clientsNicks[clientSocket] << "] 🔴" << RESET << std::endl;
		std::cout << BOLDWHITE << "🟡Client real name: [" << clientRealName  << "] 🔴" << RESET << std::endl;
		/*
		 ** TODO: Save the client real name to the client class.
		 ** TODO: add the client to the list of clients
		 */
	}
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int MsgParser::checkPass(int clientSocket, const std::string& clientPass, const int& serverPass) {
	if (clientPass.empty())
		DEBUG_MSG(BOLDRED << "Password not found" << RESET)
	else if (std::stoi(clientPass) == serverPass) {
		DEBUG_MSG("Password accepted")
		return 1;
	}
	else {
		DEBUG_MSG(BOLDRED << "Incorrect password" << RESET)
		std::string errorMsg = "ERROR :Invalid password\r\n";
		sendResponse(clientSocket, errorMsg);
	}
	return 0;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int MsgParser::checkNick(int clientSocket, const std::string& clientNick) {
	if (clientNick.empty()) {
		DEBUG_MSG(BOLDRED << "Nickname not found" << RESET)
		std::string errorMsg = "ERROR :No nickname given\r\n";
		sendResponse(clientSocket, errorMsg);
		return 0;
	}
/**
 ** TODO: Fix the bug of the Generating the guest nickname,
 **			even if the nick name accepted.
 **/
	if (clientsNicks.empty() || duplicatedClient(clientNick)) {
		std::string newNick = generateGuestNick();
		DEBUG_MSG("Assigning a Guest nickname: [" << newNick << "]")
		std::string nickMsg = "Assigning a Guest nickname: "+newNick+"\r\n";
		sendResponse(clientSocket, nickMsg);
		clientsNicks[clientSocket] = newNick;
		clientsData[clientSocket].first = newNick;
		return 0;
	}

	clientsNicks[clientSocket] = clientNick;
	clientsData[clientSocket].first = clientNick;
	DEBUG_MSG("Nickname accepted: [" << clientsNicks[clientSocket] << "]")
	return 1;
}


/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::processHandShake(int clientSocket, const std::string& clientMsg, const int& serverPass) {
	std::istringstream iss(clientMsg);
	std::string command;

	while (iss >> command) {
		if (command == "CAP") {
			std::string capLsMessage = "CAP * LS :multi-prefix sasl\r\n";
			sendResponse(clientSocket, capLsMessage);
		} else if (command == "PASS") {
			std::string password;
			iss >> password;
			if (!checkPass(clientSocket, password, serverPass)) {
				return;
			}
		} else if (command == "NICK") {
			std::string clientNick;
			iss >> clientNick;
			if (!checkNick(clientSocket, clientNick)) {
				return;
			}
		} else if (command == "USER") {
			std::string username, realName;
			iss >> username >> realName;
			checkName(clientSocket, username, realName);
		} else if (command == "PING") {
			std::string pingMsg = "PONG :ircserv\r\n";
			sendResponse(clientSocket, pingMsg);
		}
	}
	welcomeMessage(clientSocket);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/