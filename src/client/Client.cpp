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

/*====================================================================================================================*/
void Client::setSocket(const int& socket) { _socket = socket; }
void Client::setUserName(const std::string& user) { _userName = user; }
void Client::setNickName(const std::string& nick) { _nickName = nick; }
void Client::welcomeClient(bool welcome) { _isWelcomed = welcome; }

/*====================================================================================================================*/
int Client::getSocket() const { return (this->_socket); }
std::string Client::getUserName() { return (this->_userName); }
std::string Client::getNickName() { return (this->_nickName); }
bool Client::isWelcomed() const { return (this->_isWelcomed); }

/*====================================================================================================================*/
bool Client::isClientInChannel(const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itChannelMap;
	itChannelMap = this->_clientChannelsMap.find(channelName);
	if (itChannelMap != this->_clientChannelsMap.end())
		return (true);
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isOperatorOfChannel(const int& clientSocket, const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	std::vector<Client*>::iterator itOper;

	itMap = this->_clientChannelsMap.find(channelName);
	if (itMap != this->_clientChannelsMap.end()) {
		for (itOper = itMap->second->getOperators().begin(); itOper != itMap->second->getOperators().end(); ++itOper) {
			if ((*itOper)->getSocket() == clientSocket)
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isInvitedToChannel(const int &clientSocket, const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	std::vector<Client*>::iterator itInv;
	itMap = this->_clientChannelsMap.find(channelName);
	if (itMap != this->_clientChannelsMap.end()) {
		for (itInv = itMap->second->getInvites().begin(); itInv != itMap->second->getInvites().end(); ++itInv) {
			if ((*itInv)->getSocket() == clientSocket)
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isBannedFromChannel(const int& clientSocket, const std::string& channelName) {
	std::map<std::string, Channel*>::iterator itMap;
	std::vector<Client*>::iterator itBan;
	itMap = this->_clientChannelsMap.find(channelName);
	if (itMap != this->_clientChannelsMap.end()) {
		for (itBan = itMap->second->getBanedUsers().begin(); itBan != itMap->second->getBanedUsers().end(); ++itBan) {
			if ((*itBan)->getSocket() == clientSocket)
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::addClientToServer(const int& clientSocket, Server* server) {
	std::map<int, IRC::Client*>::iterator itClient;
	itClient = server->serverClientsMap.find(clientSocket);

	if (itClient == server->serverClientsMap.end()) {
		Client* newClient = new IRC::Client(clientSocket);
		server->serverClientsMap.insert(std::pair<int, IRC::Client*>(clientSocket, newClient));
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::addClientToChannel(Client* client, const std::string& channelName, Channel* channel) {
	std::map<std::string, Channel*>::iterator itChannel;
	itChannel = this->_clientChannelsMap.find(channelName);

	if (itChannel == this->_clientChannelsMap.end()) {
		this->_clientChannelsMap.insert(std::pair<std::string, Channel*>(channelName, channel));
		channel->addClientToChannel(client);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
/**
 * TODO: If the client was the last client in the channel, delete the channel from the server.
 * **/
void Client::removeClientFromChannel(Client* client, Channel* channel) {
	std::map<std::string, Channel*>::iterator itChannel;
	itChannel = this->_clientChannelsMap.find(channel->getChannelName());

	if (itChannel != this->_clientChannelsMap.end()) {
		channel->removeClientFromChannel(client);
		this->_clientChannelsMap.erase(itChannel);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::removeClientFromAllChannels(Client* client) {
	std::map<std::string, Channel*>::iterator itChannel;
	for (itChannel = this->_clientChannelsMap.begin(); itChannel != this->_clientChannelsMap.end(); ++itChannel)
		this->removeClientFromChannel(client, itChannel->second);
	this->_clientChannelsMap.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::removeClientFromServer(const int& clientSocket, Server* server, Client* client) {
	this->removeClientFromAllChannels(this);
	std::map<int, IRC::Client*>::iterator itServerMap;
	itServerMap = server->serverClientsMap.find(clientSocket);

	if (itServerMap != server->serverClientsMap.end()) {
		server->serverClientsMap.erase(itServerMap);
		delete client;
	}
}

/*====================================================================================================================*/
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