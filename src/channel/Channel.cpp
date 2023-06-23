# include "../../include/Channel.hpp"
using namespace IRC;

/*-----------------------------------------------------------------------------------------------------*/
Channel::Channel() : _name(), _topic(), _key(), _mode(),
					 _users(), _operators(), _banedUsers(), _invites() { }

Channel::Channel(const std::string& name) : _name(name), _topic(), _key(), _mode(),
											_users(), _operators(), _banedUsers(), _invites() { }

Channel::~Channel() {
	if (!_users.empty())
		_users.clear();
	if (!_operators.empty())
		_operators.clear();
	if (!_banedUsers.empty())
		_banedUsers.clear();
	if (!_invites.empty())
		_invites.clear();
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::setName(const std::string& name) { _name = name;}
void Channel::setTopic(const std::string& topic) {_topic = topic;}
void Channel::setKey(const std::string& key) {_key = key;}
void Channel::setMode(const std::string& mode) {_mode = mode;}
std::string Channel::getName() { return (_name); }
std::string Channel::getTopic() { return (_topic); }
std::string Channel::getMode() { return (_mode); }
std::string Channel::getKey() { return (_key); }

/*-----------------------------------------------------------------------------------------------------*/
std::vector<Client*> Channel::getUsers() { return (_users); }
std::vector<Client*> Channel::getOperators() { return (_operators); }
std::vector<Client*> Channel::getBanedUsers() { return (_banedUsers); }
std::vector<Client*> Channel::getInvites() { return (_invites); }

/*-----------------------------------------------------------------------------------------------------*/
void Channel::addUser(const Client& user) {
	Client* newUser = new Client(user);
	this->_users.push_back(newUser);
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::removeUser(Client user) {
	std::vector<Client*>::iterator toDelete;

	for (toDelete = _users.begin(); toDelete != _users.end(); ++toDelete) {
		if ((*toDelete)->getNickName() == user.getNickName()) {
			_users.erase(toDelete);
			break;
		}
	}
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::addOperator(const Client& user) {
	Client* newUser = new Client(user);
	this->_operators.push_back(newUser);
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::removeOperator(Client user) {
	std::vector<Client*>::iterator toDelete;

	for (toDelete = _operators.begin(); toDelete != _operators.end(); ++toDelete) {
		if ((*toDelete)->getNickName() == user.getNickName()) {
			_operators.erase(toDelete);
			break;
		}
	}
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::banUser(const Client& user) {
	Client* newUser = new Client(user);
	this->_banedUsers.push_back(newUser);
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::unbanUser(Client user) {
	std::vector<Client*>::iterator toDelete;

	for (toDelete = _banedUsers.begin(); toDelete != _banedUsers.end(); ++toDelete) {
		if ((*toDelete)->getNickName() == user.getNickName()) {
			_banedUsers.erase(toDelete);
			break;
		}
	}
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::inviteUser(const Client& user) {
	Client* newUser = new Client(user);
	this->_invites.push_back(newUser);
}

/*-----------------------------------------------------------------------------------------------------*/
void Channel::removeInvitee(Client user) {
	std::vector<Client*>::iterator toDelete;

	for (toDelete = _invites.begin(); toDelete != _invites.end(); ++toDelete) {
		if ((*toDelete)->getNickName() == user.getNickName()) {
			_invites.erase(toDelete);
			break;
		}
	}
}

/*-----------------------------------------------------------------------------------------------------*/
