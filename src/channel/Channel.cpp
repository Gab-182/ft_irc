# include "../../include/Channel.hpp"
# include "../../include/Server.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
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
Channel::Channel() : _name(), _topic(), _key(), _modes(), _members(), _operators(), _banedUsers(), _invites(),
					 _maxUsers(999) { }

Channel::Channel(const std::string& name) : _topic(), _key(), _modes(), _members(), _operators(),
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
	if (!_modes.empty())
		_modes.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::setName(const std::string& name) { _name = name;}
void Channel::setTopic(const std::string& topic) {_topic = topic;}
void Channel::setKey(const std::string& key) {_key = key;}
void Channel::setMaxUsers(const size_t& maxUsers) {_maxUsers = maxUsers;}
void Channel::addMode(const char& mode) {_modes.push_back(mode);}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::string Channel::getChannelName() { return (_name); }
std::string Channel::getTopic() { return (_topic); }
std::vector<char> Channel::getModes() { return (_modes); }
std::string Channel::getKey() { return (_key); }
size_t Channel::getMaxUsers() const { return (_maxUsers); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::vector<Client*> Channel::getNormalClients() { return (_members); }
std::vector<Client*> Channel::getOperators() { return (_operators); }
std::vector<std::string> Channel::getBanedUsers() { return (_banedUsers); }
std::vector<std::string> Channel::getInvites() { return (_invites); }
size_t Channel::getChannelUsersNumber() const {
	// We also count the invited users,
	// because we want to make sure there is a space for them if they joined
	return (_members.size() + _operators.size() + _invites.size());
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
/*
 * TODO: Check if this function is working properly.
 * */
void Channel::ifChannelIsEmptyThenDeleteIt(IRC::Server* server) {
	// If the number of users inside the channel is 0, then delete the channel.
	if (getChannelUsersNumber() == 0) {
		std::map<std::string, Channel*>::iterator it;
		it = server->serverChannelsMap.find(this->getChannelName());
		// Delete the channel from the server's channels map.
		if (it != server->serverChannelsMap.end())
			server->serverChannelsMap.erase(it);

		// After erasing the channel from the server's channels map, delete the channel object itself.
		delete (this);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Channel::isChannelFull() const {
	if (_maxUsers == 0)
		return (false);
	return (getChannelUsersNumber() >= _maxUsers);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Channel::isChannelInviteOnly() const {
	std::vector<char>::const_iterator it;
	it = std::find(_modes.begin(), _modes.end(), 'i');
	if (it != _modes.end())
		return (true);
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Channel::isChannelProtected() const {
	std::vector<char>::const_iterator it;
	it = std::find(_modes.begin(), _modes.end(), 'k');
	if (it != _modes.end())
		return (true);
	return (false);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool Channel::isValidToAddToChannel(Client* client) {
	std::string numericReply;
	std::string clientAddError;
	std::string errMsg;

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
	if (this->isChannelInviteOnly() && !client->isInvitedToChannel(client, this->getChannelName())) {
		numericReply = ERR_INVITEONLYCHAN;
		clientAddError = BOLDRED "ERROR: "q
						 BOLDWHITE "User is not invited to the channel."
						 RESET "\r\n";
		return (false);
	}
	// TODO: Add the isKeyMatchesChannelKey() function and uncomment the following lines

//	if (this->isChannelProtected() && !client->isKeyMatchesChannelKey(client, this->getChannelName())) {
//		numericReply = ERR_BADCHANNELKEY;
//		clientAddError = BOLDRED "ERROR: "
//						 BOLDWHITE "User key does not match the channel key."
//						 RESET "\r\n";
//		return (false);
//	}
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
void Channel::removeMemberFromChannel(Client* client, IRC::Server* server) {
	std::vector<Client *>::iterator it;
	it = std::find(_members.begin(), _members.end(), client);

	if (it != _members.end()) {
		client->removeChannelFromClientChannelsMap(this->getChannelName());
		_members.erase(it);
	}
	this->ifChannelIsEmptyThenDeleteIt(server);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::addOperatorToChannel(Client* client) {
	if (this->isValidToAddToChannel(client)) {
		client->addChannelToClientChannelsMap(this);
		_operators.push_back(client);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeOperatorFromChannel(Client* client, IRC::Server* server) {
	std::vector<Client *>::iterator it;
	it = std::find(_operators.begin(), _operators.end(), client);

	if (it != _operators.end()) {
		client->removeChannelFromClientChannelsMap(this->getChannelName());
		_operators.erase(it);
	}
	this->ifChannelIsEmptyThenDeleteIt(server);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::banMemberFromChannel(Client* client, IRC::Server* server) {
	if (client->isMemberInChannel(client, this->getChannelName())) {
		this->removeMemberFromChannel(client, server);
		_banedUsers.push_back(client->getNickName());
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::banUserFromChannel(Client* operatorClient, Client* clientToBan, IRC::Server* server) {
	if (operatorClient->isOperatorOfChannel(operatorClient, this->getChannelName())) {
		if (clientToBan->isBannedFromChannel(clientToBan, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_USERONCHANNEL
								 BOLDWHITE " " + clientToBan->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :User is already banned from the channel."
								 RESET "\r\n";
			Client::sendResponse(clientToBan->getSocket(), errMsg);
		}

		else if (clientToBan->isOperatorOfChannel(clientToBan, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_CHANOPRIVSNEEDED
								 BOLDWHITE " " + operatorClient->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :You can't ban a channel operator."
								 RESET "\r\n";
			Client::sendResponse(operatorClient->getSocket(), errMsg);
		}

		else if (clientToBan->isMemberInChannel(clientToBan, this->getChannelName()))
			this->banMemberFromChannel(clientToBan, server);


	// ERROR: Client is not operator of the channel to ban a user.
	}
	else {
		std::string errMsg = ": "
							 ERR_CHANOPRIVSNEEDED
							 BOLDWHITE " " + operatorClient->getNickName() + " " + this->getChannelName()
							 + BOLDRED " :You're not channel operator."
							 RESET "\r\n";
		Client::sendResponse(operatorClient->getSocket(), errMsg);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::unbanUserFromChannel(Client* client) {
	std::vector<std::string>::iterator itUnBaned;
	for (itUnBaned = _banedUsers.begin(); itUnBaned != _banedUsers.end(); itUnBaned++) {
		if (*itUnBaned == client->getNickName()) {
			_banedUsers.erase(itUnBaned);
			return;
		}
	}
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
