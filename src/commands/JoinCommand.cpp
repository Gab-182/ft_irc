# include "../../include/commands/JoinCommand.hpp"
#include "../../include/Client.hpp"
# include "../../include/Server.hpp"

using namespace IRC;

/**
 ** TODO: Handle the case when the user tries to join multiple channels at once
 ** TODO: Handle the case when the user tries to join a channel that doesn't exist
 ** TODO: Handle the case when the user tries to join a channel that they're already in
 ** TODO: Handle the case when the user tries to join a channel that they're banned from
 ** TODO: Handle the case when the user tries to join a channel that has a key and they don't provide the key
 ** TODO: Handle the case when the user tries to join a channel that has a key and they provide the wrong key
 ** TODO: Handle the case when the user tries to join a channel that has a key and they provide the right key
 **
 **/
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
JoinCommand::JoinCommand() : ICommands() { }

JoinCommand::~JoinCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool JoinCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
	if (base->isParameterEmpty(command)) {
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string paramErrMsg = ":"
								 ERR_NEEDMOREPARAMS " "
								 BOLDRED ":Please make sure you entered: "
								 BOLDYELLOW "/join "
								 BOLDWHITE "<channel_name> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, paramErrMsg);
		return (false);
	}

	if (!Client::isClientRegistered(clientSocket, server)) {
		DEBUG_MSG(BOLDRED << " client not registered yet!! ")

		std::string regErrMsg = ":"
								 ERR_NOTREGISTERED " "
								 BOLDRED ":Please make sure you entered: "
								 BOLDWHITE "<password> <nickname> <username> "
								 BOLDRED "correctly!!"
								 RESET "\r\n";
		sendResponse(clientSocket, regErrMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void JoinCommand::joinOperatorClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName) {
	Channel *newChannel;
	newChannel = new Channel(channelName);
	server->serverChannelsMap.insert(std::pair<std::string, Channel *>(channelName, newChannel));

	newChannel->addOperatorToChannel(client);
	std::string operMsg = ":"
							RPL_YOUREOPER " "
							BOLDGREEN " Successfully joined channel: ["
							+ channelName
							+ "] as an operator."
							+ RESET "\r\n";
	sendResponse(clientSocket, operMsg);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void JoinCommand::joinMemberClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName) {
	Channel *existingChannel = server->serverChannelsMap[channelName];
	existingChannel->addMemberToChannel(client);

	std::string memberMsg = BOLDGREEN " Successfully joined channel: ["
							+ channelName
							+ "] as a member."
							+ RESET "\r\n";
	sendResponse(clientSocket, memberMsg);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void JoinCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {

	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	std::string channelName = base->getParameters(command)[0];
	if (channelName[0] == '#') {
		channelName = channelName.substr(1); // Remove the '#' character from the channel name.

		/*-----------------------------------------------------------------------------------------*/
		// If the channel name is valid: Check if the channel exists in the server channels map.
		std::map<std::string, Channel *>::iterator itChannel;
		itChannel = server->serverChannelsMap.find(channelName);

		if (itChannel == server->serverChannelsMap.end())
			joinOperatorClient(clientSocket, server, client, channelName);
		else
			this->joinMemberClient(clientSocket, server, client, channelName);
	}
	/*-----------------------------------------------------------------------------------------*/
	// If the channel name is invalid: Send a response to the client.
	/*-----------------------------------------------------------------------------------------*/
	else {
		std::string response =  BOLDRED"Invalid channel name."
								BOLDWHITE "Channel names should start with '#'."
								RESET "\r\n";
		sendResponse(clientSocket, response);
	}

	/*-----------------------------------------------------------------------------------------*/
	// print the client channel map info for debugging.
	client->printClientChannelsMap();
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/