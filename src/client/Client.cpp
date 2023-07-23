#include "../../include/Client.hpp"
#include "../../include/Server.hpp"
#include "../../include/Channel.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Client::Client() : _socket(), _userName(), _nickName(),_hostName("IRC"), _isWelcomed(false) { }

Client::Client(int socket) : _socket(socket), _userName(), _nickName(), _hostName("IRC"), _isWelcomed(false) { }

Client::~Client() {
	if (!this->_clientChannelsMap.empty())
		this->_clientChannelsMap.clear();
}

Client::Client(const Client& other) {
	if (this != &other) {
		this->_socket = other._socket;
		this->_userName = other._userName;
		this->_nickName = other._nickName;
		this->_isWelcomed = other._isWelcomed;
		this->_clientChannelsMap = other._clientChannelsMap;
	}
}

Client& Client::operator=(const Client& other) {
	if (this != &other) {
		this->_socket = other._socket;
		this->_userName = other._userName;
		this->_nickName = other._nickName;
		this->_isWelcomed = other._isWelcomed;
		this->_clientChannelsMap = other._clientChannelsMap;
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
bool Client::isClientWelcomed() const { return (this->_isWelcomed); }

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
void Client::removeClientFromAllChannels(const int& clientSocket, Server* server, Client* client) {
	// First: remove the client from all channels he is in.
	std::map<std::string, Channel*>::iterator itChannelMap;
	itChannelMap = _clientChannelsMap.begin();

	if (itChannelMap != _clientChannelsMap.end())
		itChannelMap->second->removeClientFromChannel(client, server);

	// Call the function again, until the client is removed from all channels.
	if (!_clientChannelsMap.empty())
		this->removeClientFromAllChannels(clientSocket, server, client);

}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Client::removeClientFromServer(const int& clientSocket, Server* server, Client* client) {
	// First: remove the client from all channels he is in.
	this->removeClientFromAllChannels(clientSocket, server, client);

	// Second: Make sure that client map of channels are empty now.
	if (!_clientChannelsMap.empty())
		_clientChannelsMap.clear();

	// Third: Remove the client from the server, and delete his object.
	std::map<int, IRC::Client*>::iterator itServerMap;
	itServerMap = server->serverClientsMap.find(clientSocket);
	if (itServerMap != server->serverClientsMap.end()) {
		server->serverClientsMap.erase(itServerMap);
		delete (client);
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
		if (it->second != NULL) {
			// Second, compare the sockets.
			if (it->second->getSocket() == clientSocket)
				return (true);
		}
	}
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Client::isClientRegistered(const int& clientSocket, Server* server) {
	if (server->serverClientsMap[clientSocket] != NULL
		&& Client::isClientAuthenticated(clientSocket, server)
		&& !server->serverClientsMap[clientSocket]->getNickName().empty()
		&& !server->serverClientsMap[clientSocket]->getUserName().empty() )
		return (true);
	return (false);
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