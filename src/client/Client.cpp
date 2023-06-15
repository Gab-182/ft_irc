#include "../../include/Client.hpp"
using namespace IRC;

/*-------------------------------------------------------------------------------------------------------------*/
Client::Client() : _socket(), _userName(), _realName(), _nickName(), _isRegistered() { }

Client::~Client() { }

/*-------------------------------------------------------------------------------------------------------------*/

void Client::setHost(const std::string& host) { _host = host; }

void Client::setSocket(const int& socket) { _socket = socket; }

void Client::setUserName(const std::string& user) { _userName = user; }

void Client::setNickName(const std::string& nick) { _nickName = nick; }

void Client::setRealName(const std::string& realName) { _realName = realName; }

void Client::setIsRegistered(bool isRegistered) { _isRegistered = isRegistered; }
/*-------------------------------------------------------------------------------------------------------------*/

int Client::getSocket() const { return (this->_socket); }

std::string Client::getHost() { return (this->_host); }

std::string Client::getRealName() { return (this->_realName); }

std::string Client::getUserName() { return (this->_userName); }

std::string Client::getNickName() { return (this->_nickName); }

bool Client::getIsRegistered() const { return (this->_isRegistered); }
/*-------------------------------------------------------------------------------------------------------------*/
