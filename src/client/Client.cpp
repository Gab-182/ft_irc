#include "../../include/Client.hpp"
#include "../../include/Server.hpp"
#include "../../include/Channel.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Client::Client() : _socket(), _userName(), _nickName(), _isWelcomed(false) { }

Client::Client(int socket) : _socket(socket), _userName(), _nickName(), _isWelcomed(false) { }

Client::~Client() { }

Client::Client(const Client& other) {
	if (this != &other) {
		this->_socket = other._socket;
		this->_userName = other._userName;
		this->_nickName = other._nickName;
		this->_isWelcomed = other._isWelcomed;
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

bool Client::operator==(const Client& other) const {
	if (this->_socket == other._socket
		&& this->_userName == other._userName
		&& this->_nickName == other._nickName)
		return (true);
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::setSocket(const int& socket) { _socket = socket; }
void Client::setUserName(const std::string& user) { _userName = user; }
void Client::setNickName(const std::string& nick) { _nickName = nick; }
void Client::welcomeClient(bool welcome) { _isWelcomed = welcome; }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
int Client::getSocket() const { return (this->_socket); }
std::string Client::getUserName() { return (this->_userName); }
std::string Client::getNickName() { return (this->_nickName); }
bool Client::isWelcomed() const { return (this->_isWelcomed); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isMemberInChannel(Client* client, const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	std::vector<Client*>::iterator itMember;

	itMap = this->_clientChannelsMap.find(channelName);
	if (itMap != this->_clientChannelsMap.end()) {
		for (itMember = itMap->second->getNormalClients().begin(); itMember != itMap->second->getNormalClients().end(); ++itMember) {
			if (*itMember == client)
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isOperatorOfChannel(Client* client, const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	std::vector<Client*>::iterator itOper;

	itMap = this->_clientChannelsMap.find(channelName);
	if (itMap != this->_clientChannelsMap.end()) {
		for (itOper = itMap->second->getOperators().begin(); itOper != itMap->second->getOperators().end(); ++itOper) {
			if (*itOper == client)
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isInvitedToChannel(Client* client, const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	std::vector<std::string>::iterator itInv;
	itMap = this->_clientChannelsMap.find(channelName);
	if (itMap != this->_clientChannelsMap.end()) {
		for (itInv = itMap->second->getInvites().begin(); itInv != itMap->second->getInvites().end(); ++itInv) {
			if (*itInv == client->getNickName())
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isBannedFromChannel(Client* client, const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	std::vector<std::string>::iterator itBan;
	itMap = this->_clientChannelsMap.find(channelName);
	if (itMap != this->_clientChannelsMap.end()) {
		for (itBan = itMap->second->getBanedUsers().begin(); itBan != itMap->second->getBanedUsers().end(); ++itBan) {
			if (*itBan == client->getNickName())
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::addChannelToClientChannelsMap(IRC::Channel *channel) {
	std::map<std::string, Channel*>::iterator itMap;
	itMap = this->_clientChannelsMap.find(channel->getChannelName());

	if (itMap == this->_clientChannelsMap.end())
		this->_clientChannelsMap.insert(std::pair<std::string, Channel*>(channel->getChannelName(), channel));
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::removeChannelFromClientChannelsMap(const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	itMap = this->_clientChannelsMap.find(channelName);

	if (itMap != this->_clientChannelsMap.end())
		this->_clientChannelsMap.erase(itMap);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::removeClientFromServer(const int& clientSocket, Server* server, Client* client) {
	std::map<std::string, Channel*>::iterator itChannelMap;
	for (itChannelMap = _clientChannelsMap.begin(); itChannelMap != _clientChannelsMap.end(); ++itChannelMap) {
		itChannelMap->second->removeClientFromChannel(client, server);
	}
	_clientChannelsMap.clear();

	std::map<int, IRC::Client*>::iterator itServerMap;
	itServerMap = server->serverClientsMap.find(clientSocket);
	if (itServerMap != server->serverClientsMap.end()) {
		server->serverClientsMap.erase(itServerMap);
		delete client;
	}
}

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
		&& !server->serverClientsMap[clientSocket]->getUserName().empty() )
		return (true);
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
/*
 * TODO: Work it around to be able to replace it with the removeClientFromServer() function.
 * */
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
void Client::printClientChannelsMap() {
	std::map<std::string, Channel*>::iterator it;
	for (it = this->_clientChannelsMap.begin(); it != this->_clientChannelsMap.end(); ++it) {
		std::cout << BOLDYELLOW << "Channel" << std::endl;
		it->second->printChannelInfo();
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/