# include "../../include/commands/PartCommand.hpp"
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
PartCommand::PartCommand() : ICommands() { }

PartCommand::~PartCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool PartCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
	if (base->isParameterEmpty(command)) {
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string authErrMsg = ":"
								 ERR_NEEDMOREPARAMS
								 BOLDRED " Please make sure you entered: "
								 BOLDYELLOW "/join "
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
								 BOLDWHITE "<password> <nickname> <username> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PartCommand::partOperatorClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName) {

	(void)client;
	Channel *existingChannel = server->serverChannelsMap[channelName];
	std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " PART :" + channelName + "\r\n";
	sendResponse(clientSocket, response);
	std::string response2 = ":" + server->serverClientsMap[clientSocket]->getNickName() + " PART " + channelName + " :leaving";
	existingChannel->sendToAllClients("PART", server->serverClientsMap[clientSocket]->getNickName(), response2);
	existingChannel->removeOperatorFromChannel(client, server);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PartCommand::partMemberClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName) {

	(void)client;
	Channel *existingChannel = server->serverChannelsMap[channelName];
	std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " PART :" + channelName + "\r\n";
	sendResponse(clientSocket, response);
	std::string response2 = ":" + server->serverClientsMap[clientSocket]->getNickName() + " PART " + channelName + " :leaving " + "\r\n";
	existingChannel->sendToAllClients("PART", server->serverClientsMap[clientSocket]->getNickName(), response2);
	existingChannel->removeClientFromChannel(client, server);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PartCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
    //1. check the client is it normal member or operator
	//2. then we send the command to either part operator client or partMemberClient
	std::string channelName = base->getParameters(command)[0];

	if (channelName[0] == '#') {
		channelName = channelName.substr(1);
	}

		//checks if the map exists or not
		std::map<std::string, Channel*>::iterator channelIterator = server->serverChannelsMap.find(channelName);
		if (channelIterator != server->serverChannelsMap.end()) {
			std::cout << "HELLO HELLO HELLO" << std::endl;
			//checks if the client is in channel or not.
			Channel *existingChannel = server->serverChannelsMap[channelName];
			std::vector<std::string> allClients = existingChannel->getAllClients2(server->serverClientsMap[clientSocket]->getNickName());
			std::string nicknameToSearch = server->serverClientsMap[clientSocket]->getNickName();
			bool found = std::find(allClients.begin(), allClients.end(), nicknameToSearch) != allClients.end();

			if (found){
				//checks if the client is operator or member.
					std::cout << "IM HERE4" << std::endl;
				if (existingChannel->isClientOperator(client)) {
					std::cout << "IM HERE2" << std::endl;
					partOperatorClient(clientSocket, server, client, channelName);

				}
				else if (existingChannel->isClientMember(client)) {
					std::cout << "IM HERE3" << std::endl;
					partMemberClient(clientSocket, server, client, channelName);

				}
			}
			else {
				// Returns a response to the client that there's that the client is not in channel.
				std::cout << "IM HERE" << std::endl;
				std::string response = ": 442 " + nicknameToSearch + " " + channelName + " :You're not on that channel" + "\r\n";
				sendResponse(clientSocket,response);
			}

		} else {
			// Returns a response to the client that there's no such channel.
			std::string nicknameToSearch = server->serverClientsMap[clientSocket]->getNickName();
			std::string response = ": 403 " + nicknameToSearch + " " + channelName + " :No such channel" + "\r\n";
			sendResponse(clientSocket, response);
		}
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/