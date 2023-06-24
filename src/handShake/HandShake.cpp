#include "../../include/HandShake.hpp"
#include "../../include/Server.hpp"
#include "../../include/Client.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
HandShake::HandShake() { }

HandShake::~HandShake() {
	if (!_sentMessages.empty())
		_sentMessages.clear();
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

std::string HandShake::toLowerCase(const std::string& str) {
	std::string lowerCaseStr = str;
	std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(), ::tolower);
	return (lowerCaseStr);
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
			/*---------------------------------------------------------------------------*/

		else if (toLowerCase(command) == "cap" && toLowerCase(_parameter) == "end")
			sendResponse(clientSocket, "CAP * ACK :CAP END\r\n");
		/*---------------------------------------------------------------------------*/

		else if (toLowerCase(command) == "pass") {
			// If the client entered the server's pass correctly then proceed ->
			if (processPassMessage(clientSocket, _parameter, server)) {
				if (toLowerCase(command) == "mode")
					processModeMessage(clientSocket, lineStream, server);
				/*-------------------------------------------------------*/
				else if (toLowerCase(command) == "ping")
					sendResponse(clientSocket, "PONG :ircserv\r\n");
			}
			else
				return (0);
		}

		else {
			std::string passMsg = BOLDYELLOW "WARNING: " BOLDWHITE "please enter server's password first !!!" RESET "\r\n";
			sendResponse(clientSocket, passMsg);
		}
	}

	if (Client::isClientRegistered(clientSocket, server))
		welcomeMessage(clientSocket, server);
	return (1);
}

void HandShake::removeClient(int clientSocket, IRC::Server* server) {
	if (Client::isClientRegistered(clientSocket, server)) {

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
