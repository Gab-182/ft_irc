# include "../../include/Channel.hpp"
# include "../../include/Server.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
/**
 ** TODO: ********************************* IMPORTANT ***************************************
 ** 		- Channel is invite only, and the client is not invited.
 ** 		- Channel requires a key, and the client entered a wrong key.
 ** 		- # Add the correct numeric replies for each case.
 *
 *
 ** TODO: ********************************* IMPORTANT ***************************************
 ** 		- When client successfully joins a channel:
 ** 				- Send the client the channel modes.
 ** 				- Send the client the channel topic.
 ** 				- Send the client the channel members (Names list).
 *
 *
 ** TODO: ********************************* IMPORTANT ***************************************
 ** 		- Create an error class that will be thrown when an error occurs.
 ** 		- The error class will be inherited from std::exception.
 ** 		- The error class will have a constructor that will take a string as a parameter.
 ** 		- The string will be the error message.
 *
 **/
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Channel::Channel() : _name(), _topic(), _key(), _modes(), _members(), _operators(), _banedUsers(), _invites(),
					 _maxUsers(999) { }

Channel::Channel(const std::string& name) : _name(name), _topic(), _key(), _modes(), _members(), _operators(),
															 _banedUsers(), _invites(), _maxUsers(999) { }

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
/*
 * TODO: Split this function into easier to read && smaller functions.
 * */
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
		clientAddError = BOLDRED "ERROR: "
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
	std::cout <<  "IM HERE55"  << std::endl;
	if (it != _members.end()) {
		std::cout <<  "IM HERE56"  << std::endl;
		client->removeChannelFromClientChannelsMap(this->getChannelName());
		_members.erase(it);
		std::cout <<  "IM HERE57"  << std::endl;
	}
	std::cout <<  "IM HERE58"  << std::endl;
	(void)server;
	//this->ifChannelIsEmptyThenDeleteIt(server);
	std::cout <<  "IM HERE59"  << std::endl;
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
/*
 * TODO: Split this function into easier to read && smaller functions.
 * */
void Channel::banUserFromChannel(Client* operatorClient, Client* clientToBan, IRC::Server* server) {

	// Check if the client who is banning is an operator of the channel.
	if (operatorClient->isOperatorOfChannel(operatorClient, this->getChannelName())) {
		if (clientToBan->isBannedFromChannel(clientToBan, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_USERONCHANNEL
								 BOLDWHITE " " + clientToBan->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :User is already banned from the channel."
								 RESET "\r\n";
			Client::sendResponse(clientToBan->getSocket(), errMsg);
		}
		// Can not ban operators from a channel.
		else if (clientToBan->isOperatorOfChannel(clientToBan, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_CHANOPRIVSNEEDED
								 BOLDWHITE " " + operatorClient->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :You can't ban a channel operator."
								 RESET "\r\n";
			Client::sendResponse(operatorClient->getSocket(), errMsg);
		}

		// If every thing went will, then ban the user from the channel.
		else if (clientToBan->isMemberInChannel(clientToBan, this->getChannelName()))
			this->banMemberFromChannel(clientToBan, server);


	// ERROR: Client is not operator of the channel to ban a user.
	}
	else {
		std::string errMsg = ": "
							 ERR_NOPRIVILEGES
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
/*
 * TODO: Split this function into easier to read && smaller functions.
 * */
void Channel::inviteUserToChannel(Client* operatorClient, Client* clientToInvite) {
	if (this->isChannelInviteOnly() && operatorClient->isOperatorOfChannel(operatorClient, this->getChannelName())) {

		if (this->isChannelFull()) {
			std::string errMsg = ERR_CHANNELISFULL
								 BOLDRED "ERROR: "
								 BOLDWHITE "Can not invite user, channel is full."
								 RESET "\r\n";
			Client::sendResponse(operatorClient->getSocket(), errMsg);
		}

		if (clientToInvite->isMemberInChannel(clientToInvite, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_USERONCHANNEL
								 BOLDWHITE " " + clientToInvite->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :User is already a member of the channel."
								   RESET "\r\n";
			Client::sendResponse(clientToInvite->getSocket(), errMsg);
		}

		else if (clientToInvite->isOperatorOfChannel(clientToInvite, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_USERONCHANNEL
								 BOLDWHITE " " + clientToInvite->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :User is already an operator of the channel."
								  RESET "\r\n";
			Client::sendResponse(clientToInvite->getSocket(), errMsg);
		}
		else if (clientToInvite->isBannedFromChannel(clientToInvite, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_BANNEDFROMCHAN
								 BOLDWHITE " " + clientToInvite->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :User is banned from the channel."
								   RESET "\r\n";
			Client::sendResponse(clientToInvite->getSocket(), errMsg);
		}
		else if (clientToInvite->isInvitedToChannel(clientToInvite, this->getChannelName())) {
			std::string errMsg = ": "
								 ERR_USERONCHANNEL
								 BOLDWHITE " " + clientToInvite->getNickName() + " " + this->getChannelName()
								 + BOLDRED " :User is already invited to the channel."
								   RESET "\r\n";
			Client::sendResponse(clientToInvite->getSocket(), errMsg);
		}
		else {
			clientToInvite->addChannelToClientChannelsMap(this);
			_invites.push_back(clientToInvite->getNickName());
			std::string inviteMsg = ": "
									RPL_INVITING
									BOLDWHITE " " + clientToInvite->getNickName() + " " + this->getChannelName()
									+ BOLDGREEN " :You have been invited to the channel."
									  RESET "\r\n";
			Client::sendResponse(clientToInvite->getSocket(), inviteMsg);
		}
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
void Channel::removeInviteeFromChannel(Client* client, IRC::Server* server) {
	if (client->isOperatorOfChannel(client, this->getChannelName())) {
		std::vector<std::string>::iterator itInvitee;
		for (itInvitee = _invites.begin(); itInvitee != _invites.end(); ++itInvitee) {
			if (*itInvitee == client->getNickName()) {
				_invites.erase(itInvitee);
				return;
			}
		}
	}
	this->ifChannelIsEmptyThenDeleteIt(server);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::removeClientFromChannel(Client* client, IRC::Server* server) {
	if (client->isMemberInChannel(client, this->getChannelName()))
		this->removeMemberFromChannel(client, server);
	else if (client->isOperatorOfChannel(client, this->getChannelName()))
		this->removeOperatorFromChannel(client, server);
	else if (client->isInvitedToChannel(client, this->getChannelName()))
		this->removeInviteeFromChannel(client, server);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Channel::printChannelInfo() {
	std::cout << BOLDMAGENTA << std::endl << "—————————————————————————————————————————————————" << std::endl;
	std::cout << BOLDYELLOW << "Channel name: " << BOLDWHITE << _name << std::endl;
	std::cout << BOLDYELLOW << "Channel topic: " << BOLDWHITE << _topic << std::endl;

	std::cout << BOLDYELLOW << "Channel modes: " << std::endl;
	std::vector<char>::iterator itModes;
	for (itModes = _modes.begin(); itModes != _modes.end(); ++itModes)
		std::cout << BOLDWHITE << *itModes << BOLDYELLOW << " - ";


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
	std::vector<std::string>::iterator itBanned;
	for (itBanned = _banedUsers.begin(); itBanned != _banedUsers.end(); ++itBanned)
		std::cout << BOLDWHITE << *itBanned << BOLDYELLOW << " - ";

	std::cout << std::endl;
	std::cout << "Channel invites: ➤➤ ";
	std::vector<std::string>::iterator itInvite;
	for (itInvite = _invites.begin(); itInvite != _invites.end(); ++itInvite)
		std::cout << BOLDWHITE << *itInvite << BOLDYELLOW << " - ";

	std::cout << BOLDMAGENTA << std::endl << "—————————————————————————————————————————————————" << std::endl;
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
