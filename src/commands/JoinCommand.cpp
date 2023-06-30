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

		std::string authErrMsg = ":"
								 ERR_NEEDMOREPARAMS
								 BOLDRED " Please make sure you entered: "
								 BOLDYELLOW "JOIN "
								 BOLDWHITE "<channel_name> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

	if (!Client::isClientRegistered(clientSocket, server)) {
		DEBUG_MSG(BOLDRED << " client not registered yet!! ")

		std::string authErrMsg = ":"
								 ERR_NOTREGISTERED
								 BOLDRED " Please make sure you entered: "
								 BOLDWHITE "[NickName] "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void JoinCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {

	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	std::string channelName = base->getParameters(command)[0];
	if (channelName[0] == '#') {
		channelName = channelName.substr(1); // Remove the '#' character from the channel name.
		/*-----------------------------------------------------------------------------------------*/
		// If the channel doesn't exist:
		// 1. Create a new channel.
		// 2. Add the client to the channel.
		// 3. Send a response to the client.
		/*-----------------------------------------------------------------------------------------*/
		std::map<std::string, Channel *>::iterator itChannel;
		itChannel = server->serverChannelsMap.find(channelName);
		if (itChannel == server->serverChannelsMap.end()) {
			Channel *newChannel;
			newChannel = new Channel(channelName, client);

			server->serverChannelsMap.insert(std::pair<std::string, Channel *>(channelName, newChannel));
			client->addClientToChannel(client, channelName, newChannel);
			// send a response to the client.
			std::string response = BOLDGREEN "Successfully joined channel: " + channelName + RESET "\r\n";
			sendResponse(clientSocket, response);
		}
		/*-----------------------------------------------------------------------------------------*/
		// If the channel already exists:
		// 1. Add the client to the channel.
		// 2. Send a response to the client.
		/*-----------------------------------------------------------------------------------------*/
		else {
			Channel *existingChannel = server->serverChannelsMap[channelName];
			client->addClientToChannel(client, channelName, existingChannel);
			// send a response to the client.
			std::string response = BOLDGREEN "Successfully joined channel: " + channelName + RESET "\r\n";
			sendResponse(clientSocket, response);
		}
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