# include "../../include/Commands.hpp"

using namespace IRC;

Commands::Commands() {}

Commands::~Commands() {}

/*————————————————————————————⟪⟪ SEND Command ⟫⟫———————————————————————————*/
void Commands::handleCommands(int client_socket, const std::string& msg) {
	std::istringstream iss(clientMsg);
	std::string command;

	while (iss >> command) {
		if (command == "JOIN") {
			this->join(client_socket, "JOIN");
		} else if (command == "PART") {
			
//		} else if (command == "PRIVMSG") {
//
//		} else if (command == "NOTICE") {
//
//		} else if (command == "QUIT") {
//
//		} else if (command == "NICK") {
//
//		} else if (command == "USER") {
//
//		} else if (command == "OPER") {
//
//		} else if (command == "MODE") {
//
//		} else if (command == "TOPIC") {
//
//		} else if (command == "KICK") {
//
//		} else if (command == "INVITE") {
//
		} else {
			DEBUG_MSG("Unknown command [" << command << "]");
		}
	}
}

/*————————————————————————————⟪⟪ SEND Command ⟫⟫———————————————————————————*/
void Commands::sendCommand(int client_socket, const std::string& msg) {
	if (send(client_socket, msg.c_str(), msg.length(), 0) < 0) {
		DEBUG_MSG("Error sending [" << msg << "] to client");
		exit(EXIT_FAILURE);
	}
}

/*————————————————————————————————⟪⟪ JOIN ⟫⟫———————————————————————————————*/
void Commands::join(int clientSocket, const std::string& channel) {
	this->sendCommand(clientSocket, "JOIN " + channel);
}

///*————————————————————————————————⟪⟪ PART ⟫⟫———————————————————————————————*/
//void Commands::part(int clientSocket, const std::string& channel) {
//	this->sendCommand(clientSocket, "PART " + channel);
//}

/*———————————————————————————————⟪⟪ PRIVMSG ⟫⟫—————————————————————————————*/
/*———————————————————————————————⟪⟪ NOTICE ⟫⟫——————————————————————————————*/
/*————————————————————————————————⟪⟪ QUIT ⟫⟫———————————————————————————————*/
/*————————————————————————————————⟪⟪ NICK ⟫⟫———————————————————————————————*/
/*————————————————————————————————⟪⟪ USER ⟫⟫———————————————————————————————*/
/*————————————————————————————————⟪⟪ OPER ⟫⟫———————————————————————————————*/
/*————————————————————————————————⟪⟪ MODE ⟫⟫———————————————————————————————*/
/*———————————————————————————————⟪⟪ TOPIC ⟫⟫———————————————————————————————*/
/*————————————————————————————————⟪⟪ KICK ⟫⟫———————————————————————————————*/
/*———————————————————————————————⟪⟪ INVITE ⟫⟫——————————————————————————————*/