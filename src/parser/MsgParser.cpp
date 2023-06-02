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
int MsgParser::passCheck(int clientSocket, const std::string& clientPass, const int& serverPass) {
	if (clientPass.empty())
		std::cout << "Password not found" << std::endl;

	else if (std::stoi(clientPass) == serverPass) {
		std::cout << "Password accepted" << std::endl;
		return 1;
	}
	else {
		std::cout << "Incorrect password" << std::endl;
		std::string errorMsg = "ERROR :Invalid password\r\n";
		if (send(clientSocket, errorMsg.c_str(), errorMsg.size(), 0) == -1)
			std::cout << "Failed to send error message" << std::endl;
	}
	return 0;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::parseNick(int clientSocket, const std::string& clientNick) {
	if (clientNick.empty()) {
		std::cout << "Nickname not found" << std::endl;
		std::string errorMsg = "ERROR :No nickname given\r\n";
		if (send(clientSocket, errorMsg.c_str(), errorMsg.size(), 0) == -1) {
			std::cout << "Failed to send error message" << std::endl;
		}
	}
//	else if (clientsNicks.empty()) {
//		clientsNicks.push_back(clientNick);
//		std::cout << "Nickname accepted" << std::endl;
//	}
//	else if (std::find(clientsNicks.begin(), clientsNicks.end(), clientNick) != clientsNicks.end()) {
//		std::cout << "Nickname already taken" << std::endl;
//
//		std::string errorMsg = "ERROR :Invalid nickname\r\n";
//		if (send(clientSocket, errorMsg.c_str(), errorMsg.size(), 0) == -1) {
//			std::cout << "Failed to send error message" << std::endl;
//		}
//	}
	else {
		clientsNicks.insert(std::make_pair(clientSocket, clientNick));
		std::cout << "Nickname ["<< clientsNicks[clientSocket] << "] accepted" << std::endl;
	}
}


/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void MsgParser::processClientMessage(int clientSocket, const std::string& clientMsg, const int& serverPass) {
	std::stringstream ss(clientMsg);
	std::string command;
	
	ss >> command;  // Extract the first word (command) from the string stream
	if (clientMsg.find("PASS") && clientMsg.find("NICK") && clientMsg.find("USER")) {
		while (ss >> command) {
			if (command == "PASS") {
				std::string password;
				ss >> password;
				std::cout << "PASS: " << password << std::endl;
				if (!passCheck(clientSocket, password, serverPass))
					return ;
			}
			else if (command == "NICK") {
				std::string clientNick;
				ss >> clientNick;
				std::cout << clientNick << std::endl;
				parseNick(clientSocket, clientNick);
			}
//					else if (command == "USER") {
//						std::string username, realName;
//						ss >> username >> realName;
//						saveName(clientSocket, username, realName);
//					}
		}
		std::cout << "client: "<< clientSocket << " -> " << "nick: " << clientsNicks[clientSocket] << std::endl;
//		std::string msg = "CAP * LS :multi-prefix sasl\r\n";
//		std::string welcomeClient = ":"+clientsNicks[clientSocket]+" 001 "+clientsNicks[clientSocket]+" :Welcome to the Internet Relay Network " + "\r\n";
//
//		// Send the [CAP && welcome] messages to the client
//		if(send(clientSocket,msg.c_str(),msg.size(),0) == -1)
//			std::cout<< "error occurred while sending CAP LS\n";
//		if(send(clientSocket,welcomeClient.c_str(),welcomeClient.size(),0) == -1)
//			std::cout<< "error occurred while sending welcome msg\n";
	}
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/