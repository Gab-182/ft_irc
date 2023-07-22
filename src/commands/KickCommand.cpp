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
void KickCommand::KickMemberClient(const int& clientSocket, Server* server, const std::string& channelName, const std::string& targetUser, const std::string& reason) {

	Channel* existingChannel = server->serverChannelsMap[channelName];
        // Build the KICK command with the target user and optional reason.
       std::string kickCommand = "KICK " + channelName + " " + targetUser + " :" + reason + "\r\n";
        // if (!reason.empty()) {
        //     kickCommand += " :" + reason;
        // }
        // kickCommand += "\r\n";

        // Send the KICK command to the IRC server.
        sendResponse(clientSocket, kickCommand);
		//channelname and user for kicked user


        // Optionally, you can also remove the client from the channel in your implementation.
		int soso = existingChannel->getTargetClientFD(targetUser);
		Client* soso1 = server->serverClientsMap[soso];

        existingChannel->removeClientFromChannel(soso1, server);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void KickCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
   //1. check the client is it normal member or operator
	//2. then we send the command to either part operator client or partMemberClient
	std::string channelName = base->getParameters(command)[0];
	std::string targetUser = base->getParameters(command)[1];

	if (channelName[0] == '#') {
		channelName = channelName.substr(1);
	}

			//checks if the client is in channel or not.

			std::map<std::string, Channel*>::iterator channelIterator = server->serverChannelsMap.find(channelName);
			if (channelIterator != server->serverChannelsMap.end()) {

						Channel *existingChannel = server->serverChannelsMap[channelName];
						std::cout << "CHANNEL NAME: " << channelName << std::endl;
						std::cout << "USER NAME: " << targetUser << std::endl;
						std::vector<std::string> allClients = existingChannel->getAllClients2(server->serverClientsMap[clientSocket]->getNickName());
						std::cout << "3sdasd: " << "h" << std::endl;
						bool found = std::find(allClients.begin(), allClients.end(), targetUser) != allClients.end();
						std::cout << "SEG2 " <<  std::endl;

				if (existingChannel->isClientOperator(client)) {
					
					if (found) {
						KickMemberClient(clientSocket, server, channelName, targetUser, "h");
						std::cout << "test" << std::endl;
					} else {
						std::cout << "NOT FOUND" << std::endl;
					}

					} else {

					// The client doesn't have permission to use /kick.
					std::string response = ": 482 " + server->serverClientsMap[clientSocket]->getNickName() + " " + channelName + " :You're not a channel operator\r\n";
					sendResponse(clientSocket, response);

					}

			}

	

}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/