# include "../../include/Channel.hpp"
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Channel::Channel() : _name(), _topic(), _key(), _mode(), _members(), _operators(), _banedUsers(), _invites(),
					 _maxUsers() { }

Channel::Channel(const std::string& name, Client* creator) : _name(name), _topic(), _key(), _mode(), _members(),
															 _operators(), _banedUsers(), _invites(), _maxUsers() {
	// Adding creator to channel's operators
	this->_operators.push_back(creator);
}

Channel::~Channel() {
	if (!_members.empty())
		_members.clear();
	if (!_operators.empty())
		_operators.clear();
	if (!_banedUsers.empty())
		_banedUsers.clear();
	if (!_invites.empty())
		_invites.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::setName(const std::string& name) { _name = name;}
void Channel::setTopic(const std::string& topic) {_topic = topic;}
void Channel::setKey(const std::string& key) {_key = key;}
void Channel::setMode(const std::string& mode) {_mode = mode;}
void Channel::setMaxUsers(const size_t& maxUsers) {_maxUsers = maxUsers;}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::string Channel::getName() { return (_name); }
std::string Channel::getTopic() { return (_topic); }
std::string Channel::getMode() { return (_mode); }
std::string Channel::getKey() { return (_key); }
size_t Channel::getMaxUsers() const { return (_maxUsers); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::vector<Client*> Channel::getUsers() { return (_members); }
std::vector<Client*> Channel::getOperators() { return (_operators); }
std::vector<Client*> Channel::getBanedUsers() { return (_banedUsers); }
std::vector<Client*> Channel::getInvites() { return (_invites); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::addUser(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_members.begin(), _members.end(), user);
	if (it == _members.end())
		_members.push_back(user);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeUser(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_members.begin(), _members.end(), user);
	if (it != _members.end())
		_members.erase(it);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::addOperator(Client* user) {
	// Remove the user from the users vector, if present.
	std::vector<Client *>::iterator itu;
	itu = std::find(_members.begin(), _members.end(), user);
	if (itu != _members.end())
		_members.erase(itu);

	// Remove the user from the banedUsers vector, if present.
	std::vector<Client *>::iterator itb;
	itb = std::find(_banedUsers.begin(), _banedUsers.end(), user);
	if (itb != _banedUsers.end())
		_banedUsers.erase(itb);

	// Remove the user from the invites vector, if present.
	std::vector<Client *>::iterator iti;
	iti = std::find(_invites.begin(), _invites.end(), user);
	if (iti != _invites.end())
		_invites.erase(iti);

	// Add the user to the operators vector, if not already in.
	std::vector<Client *>::iterator ito;
	ito = std::find(_operators.begin(), _operators.end(), user);
	if (ito == _operators.end())
		_operators.push_back(user);

}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeOperator(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_operators.begin(), _operators.end(), user);
	if (it != _operators.end())
		_operators.erase(it);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::banUser(Client* user) {
	// Remove the user from the users vector, if present.
	std::vector<Client *>::iterator it;
	it = std::find(_members.begin(), _members.end(), user);
	if (it != _members.end())
		_members.erase(it);

	// Add the user to the banedUsers vector, if not already in.
	std::vector<Client *>::iterator itb;
	itb = std::find(_banedUsers.begin(), _banedUsers.end(), user);
	if (itb == _banedUsers.end())
		_banedUsers.push_back(user);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::unbanUser(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_banedUsers.begin(), _banedUsers.end(), user);
	if (it != _banedUsers.end())
		_banedUsers.erase(it);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::inviteUser(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_invites.begin(), _invites.end(), user);
	if (it == _invites.end())
		_invites.push_back(user);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeInvitee(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_invites.begin(), _invites.end(), user);
	if (it != _invites.end())
		_invites.erase(it);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
