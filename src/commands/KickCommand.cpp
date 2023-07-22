# include "../../include/commands/KickCommand.hpp"
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
KickCommand::KickCommand() : ICommands() { }

KickCommand::~KickCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool KickCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
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
void KickCommand::KickMemberClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName) {

	(void)client;
	Channel *existingChannel = server->serverChannelsMap[channelName];
	std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " PART :" + channelName + "\r\n";
	sendResponse(clientSocket, response);
	std::string response2 = ":" + server->serverClientsMap[clientSocket]->getNickName() + " PART " + channelName + " :leaving " + "\r\n";
	existingChannel->sendToAllClients("PART", server->serverClientsMap[clientSocket]->getNickName(), response2);
	existingChannel->removeClientFromChannel(client, server);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void KickCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
    //1. check the client is it normal member or operator
	//2. then we send the command to either part operator client or partMemberClient
	std::string channelName = base->getParameters(command)[0];
	std::string userName = base->getParameters(command)[1];

	if (channelName[0] == '#') {
		channelName = channelName.substr(1);
	}

			//checks if the client is in channel or not.

			Channel *existingChannel = server->serverChannelsMap[channelName];
			std::cout << "CHANNEL NAME: " << channelName << std::endl;
			std::cout << "USER NAME: " << userName << std::endl;
			std::vector<std::string> allClients = existingChannel->getAllClients2(server->serverClientsMap[clientSocket]->getNickName());
			//std::string nicknameToSearch = server->serverClientsMap[clientSocket]->getNickName();
			bool found = std::find(allClients.begin(), allClients.end(), userName) != allClients.end();

	if (existingChannel->isClientOperator(client)) {
		
		if (found) {
			std::cout << "test" << std::endl;
		} else {
			std::cout << "NOT FOUND" << std::endl;
		}

		} else {

			std::cout << "SORRY YOU ARE NOT AN OPERATOR" << std::endl;

		}

}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/