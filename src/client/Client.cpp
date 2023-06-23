#include "../../include/Client.hpp"
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Client::Client() : _socket(), _userName(), _nickName() { }

Client::Client(int socket) : _socket(socket), _userName(), _nickName() { }

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

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/

int Client::getSocket() const { return (this->_socket); }

std::string Client::getUserName() { return (this->_userName); }

std::string Client::getNickName() { return (this->_nickName); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
