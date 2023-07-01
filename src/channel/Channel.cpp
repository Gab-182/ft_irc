# include "../../include/Channel.hpp"
using namespace IRC;

/**
 ** TODO: Change the mode from a string to a vector of modes.
 ** 		- Change the getter, setters, and the constructor.
 ** -----------------------------------------------------------------------
 ** TODO: Check if we can add the client first due to:
 ** 		- Channel is invite only, and the client is not invited.
 ** 		- Channel requires a key, and the client entered a wrong key.
 ** 		- # Add the correct numeric replies for each case.
 ** -----------------------------------------------------------------------
 **
 **/
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Channel::Channel() : _name(), _topic(), _key(), _mode(), _members(), _operators(), _banedUsers(), _invites(),
					 _maxUsers(999) { }

Channel::Channel(const std::string& name) : _topic(), _key(), _mode(), _members(), _operators(),
															 _banedUsers(), _invites(), _maxUsers(999) {
	_name = name;
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
std::string Channel::getChannelName() { return (_name); }
std::string Channel::getTopic() { return (_topic); }
std::string Channel::getMode() { return (_mode); }
std::string Channel::getKey() { return (_key); }
size_t Channel::getMaxUsers() const { return (_maxUsers); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::vector<Client*> Channel::getNormalClients() { return (_members); }
std::vector<Client*> Channel::getOperators() { return (_operators); }
std::vector<Client*> Channel::getBanedUsers() { return (_banedUsers); }
std::vector<Client*> Channel::getInvites() { return (_invites); }
size_t Channel::getChannelUsersNumber() const {
	return (_members.size() + _operators.size() + _banedUsers.size() + _invites.size());
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Channel::isChannelFull() const {
	if (_maxUsers == 0)
		return (false);
	return (getChannelUsersNumber() >= _maxUsers);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Channel::isValidToAddToChannel(Client* client) {
	std::string numericReply;
	std::string clientAddError;
	std::string errMsg;

	/*
	 * TODO: Check if the client key matches the channel key.
	 * TODO: Split the function into smaller ones so:
	 * 		- one to check if the channel is full.
	 * 		- one to check if the client is an operator.
	 * 		- one to check if the client is banned.
	 * 		- one to check if the client is already a member.
	 * 		- one to check if the channel is invite only and the client is invited.
	 * 		- one to check if the client key matches the channel key.
	 * 		- each function will return a boolean.
	 * 			- if true, then add the client to the channel.
	 * 			- if false, then send the correct numeric reply according to the case.
	 * */
	if (this->isChannelFull()) {
		numericReply = ERR_CHANNELISFULL;
		clientAddError = BOLDRED "ERROR: "
						 BOLDWHITE "Channel is full."
						 RESET "\r\n";
		return (false);
	}
	if (client->isOperatorOfChannel(client, this->getChannelName())) {
		numericReply = ERR_USERONCHANNEL;
		clientAddError = BOLDRED "ERROR: "
						 BOLDWHITE "User is already an operator of the channel."
						 RESET "\r\n";
		return (false);
	}
	if (client->isBannedFromChannel(client, this->getChannelName())) {
		numericReply = ERR_BANNEDFROMCHAN;
		clientAddError = BOLDRED "ERROR: "
						 BOLDWHITE "User is banned from the channel."
						 RESET "\r\n";
		return (false);
	}
	if (client->isInvitedToChannel(client, this->getChannelName())) {
		numericReply = ERR_INVITEONLYCHAN;
		clientAddError = BOLDRED "ERROR: "
						 BOLDWHITE "User is not invited to the channel."
						 RESET "\r\n";
		return (false);
	}
	if (client->isMemberInChannel(client, this->getChannelName())) {
		numericReply = ERR_USERONCHANNEL;
		clientAddError = BOLDRED "ERROR: "
						 BOLDWHITE "User is already a member of the channel."
						 RESET "\r\n";
		return (false);
	}


	errMsg = ": " + numericReply + " " + client->getNickName() + " " + this->getChannelName() + clientAddError;
	Client::sendResponse(client->getSocket(), errMsg);

	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::addMemberToChannel(Client* client) {
	if (this->isValidToAddToChannel(client)) {
		client->addChannelToClientChannelsMap(this);
		_members.push_back(client);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeMemberFromChannel(Client* client) {
	std::vector<Client *>::iterator itClient;
	itClient = std::find(_members.begin(), _members.end(), client);
	if (itClient != _members.end())
		_members.erase(itClient);

	std::vector<Client *>::iterator itOperator;
	itOperator = std::find(_operators.begin(), _operators.end(), client);
	if (itOperator != _operators.end())
		_operators.erase(itOperator);

	std::vector<Client *>::iterator itInvite;
	itInvite = std::find(_invites.begin(), _invites.end(), client);
	if (itInvite != _invites.end())
		_invites.erase(itInvite);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::addOperatorToChannel(Client* user) {
	// Remove the user from the users vector, if present.
	std::vector<Client *>::iterator itNormal;
	itNormal = std::find(_members.begin(), _members.end(), user);
	if (itNormal != _members.end())
		_members.erase(itNormal);

	// Remove the user from the banedUsers vector, if present.
	std::vector<Client *>::iterator itBanned;
	itBanned = std::find(_banedUsers.begin(), _banedUsers.end(), user);
	if (itBanned != _banedUsers.end())
		_banedUsers.erase(itBanned);

	// Remove the user from the invites vector, if present.
	std::vector<Client *>::iterator itInvite;
	itInvite = std::find(_invites.begin(), _invites.end(), user);
	if (itInvite != _invites.end())
		_invites.erase(itInvite);

	// Add the user to the operators vector, if not already in.
	std::vector<Client *>::iterator itOperator;
	itOperator = std::find(_operators.begin(), _operators.end(), user);
	if (itOperator == _operators.end())
		_operators.push_back(user);

}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeChannelOperator(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_operators.begin(), _operators.end(), user);
	if (it != _operators.end())
		_operators.erase(it);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::banUserFromChannel(Client* user) {
	// Remove the user from the users vector, if present.
	std::vector<Client *>::iterator itNormal;
	itNormal = std::find(_members.begin(), _members.end(), user);
	if (itNormal != _members.end())
		_members.erase(itNormal);

	// Add the user to the banedUsers vector, if not already in.
	std::vector<Client *>::iterator itBanned;
	itBanned = std::find(_banedUsers.begin(), _banedUsers.end(), user);
	if (itBanned == _banedUsers.end())
		_banedUsers.push_back(user);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::unbanUserFromChannel(Client* user) {
	std::vector<Client *>::iterator itUnBaned;
	itUnBaned = std::find(_banedUsers.begin(), _banedUsers.end(), user);
	if (itUnBaned != _banedUsers.end())
		_banedUsers.erase(itUnBaned);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::inviteUserToChannel(Client* user) {
	// Check if the user is already in normal members vector the channel.
	std::vector<Client *>::iterator itNormal;
	itNormal = std::find(_members.begin(), _members.end(), user);
	if (itNormal != _members.end())
		return;

	// Check if the user is already in operators vector the channel.
	std::vector<Client *>::iterator itOperator;
	itOperator = std::find(_operators.begin(), _operators.end(), user);
	if (itOperator != _operators.end())
		return;

	// Check if the user is banned from the channel.
	std::vector<Client *>::iterator itBanned;
	itBanned = std::find(_banedUsers.begin(), _banedUsers.end(), user);
	if (itBanned != _banedUsers.end())
		return;

	// if not add the user to the invites vector, if not already in.
	std::vector<Client *>::iterator it;
	it = std::find(_invites.begin(), _invites.end(), user);
	if (it == _invites.end())
		_invites.push_back(user);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeInviteeFromChannel(Client* user) {
	std::vector<Client *>::iterator it;
	it = std::find(_invites.begin(), _invites.end(), user);
	if (it != _invites.end())
		_invites.erase(it);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::printChannelInfo() {
	std::cout << BOLDMAGENTA << std::endl << "—————————————————————————————————————————————————" << std::endl;
	std::cout << BOLDYELLOW << "Channel name: " << BOLDWHITE << _name << std::endl;
	std::cout << BOLDYELLOW << "Channel topic: " << BOLDWHITE << _topic << std::endl;
	std::cout << BOLDYELLOW << "Channel mode: " << BOLDWHITE << _mode << std::endl;
	std::cout << BOLDYELLOW << "Channel key: " << BOLDWHITE << _key << std::endl;
	std::cout << BOLDYELLOW << "Channel max users: " << BOLDWHITE << _maxUsers << std::endl;

	std::cout << std::endl;
	std::cout << BOLDYELLOW << "Channel normal members: ➤➤ ";
	std::vector<Client *>::iterator itNormal;
	for (itNormal = _members.begin(); itNormal != _members.end(); ++itNormal)
		std::cout << BOLDWHITE << (*itNormal)->getNickName() << BOLDYELLOW << " - ";

	std::cout << std::endl;
	std::cout << "Channel operators: ➤➤ ";
	std::vector<Client *>::iterator itOperator;
	for (itOperator = _operators.begin(); itOperator != _operators.end(); ++itOperator)
		std::cout << BOLDWHITE << (*itOperator)->getNickName() << BOLDYELLOW << " - ";

	std::cout << std::endl;
	std::cout << "Channel baned users: ➤➤ ";
	std::vector<Client *>::iterator itBanned;
	for (itBanned = _banedUsers.begin(); itBanned != _banedUsers.end(); ++itBanned)
		std::cout << BOLDWHITE << (*itBanned)->getNickName() << BOLDYELLOW << " - ";

	std::cout << std::endl;
	std::cout << "Channel invites: ➤➤ ";
	std::vector<Client *>::iterator itInvite;
	for (itInvite = _invites.begin(); itInvite != _invites.end(); ++itInvite)
		std::cout << BOLDWHITE << (*itInvite)->getNickName() << BOLDYELLOW << " - ";

	std::cout << BOLDMAGENTA << std::endl << "—————————————————————————————————————————————————" << std::endl;
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
