#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Client::Client() : _socket(), _userName("user"), _nickName("user"), _realName("unknown"), _hostName(), _isWelcomed(false) { }

Client::Client(int socket) : _socket(socket), _userName("user"), _nickName("user"), _realName("unknown"), _hostName(), _isWelcomed(false) { }

Client::~Client() { }

Client::Client(const Client& other) {
	if (this != &other) {
		this->_socket = other._socket;
		this->_userName = other._userName;
		this->_nickName = other._nickName;
	}
}

Client& Client::operator=(const Client& other) {
	if (this != &other) {
		this->_socket = other._socket;
		this->_userName = other._userName;
		this->_nickName = other._nickName;
	}
	return (*this);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::setSocket(const int& socket) { _socket = socket; }
void Client::setUserName(const std::string& user) { _userName = user; }
void Client::setNickName(const std::string& nick) { _nickName = nick; }
void Client::setRealName(const std::string& realName) { _realName = realName; }
void Client::setHostName(const std::string& host) { _hostName = host; }
void Client::welcomeClient(bool welcome) { _isWelcomed = welcome; }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
int Client::getSocket() const { return (this->_socket); }
std::string Client::getUserName() { return (this->_userName); }
std::string Client::getNickName() { return (this->_nickName); }
std::string Client::getRealName() { return (this->_realName); }
std::string Client::getHostName() { return (this->_hostName); }
bool Client::isWelcomed() const { return (this->_isWelcomed); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::sendResponse(int clientSocket, const std::string& message) {
	if (send(clientSocket, message.c_str(), message.size(), 0) == -1)
		DEBUG_MSG("Failed to send message to the client: " << message)
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isClientAuthenticated(const int& clientSocket, Server* server) {
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

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isClientRegistered(const int& clientSocket, Server* server) {
	if (server->serverClientsMap[clientSocket] != nullptr
		&& !server->serverClientsMap[clientSocket]->getNickName().empty()
		&& !server->serverClientsMap[clientSocket]->getUserName().empty()
		&& !server->serverClientsMap[clientSocket]->getRealName().empty()
		&& !server->serverClientsMap[clientSocket]->getHostName().empty())
		return (true);
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::removeClient(int clientSocket, IRC::Server* server) {
	if (Client::isClientAuthenticated(clientSocket, server)) {

		// Delete the client from the serverClientsMap in the server
		std::map<int, Client*>::iterator toDelete;
		toDelete = server->serverClientsMap.find(clientSocket);
		if (toDelete != server->serverClientsMap.end()) {
			// First delete the client object
			delete(toDelete->second);
			// second erase the element from the map
			server->serverClientsMap.erase(toDelete);
		}
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/