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
	   std::string oprName = server->serverClientsMap[clientSocket]->getNickName();
	    std::string kickCommand = "";

       



		 // Check if existingChannel is a valid pointer
		if (existingChannel) {
			if (!targetUser.empty()) {
				int soso = existingChannel->getTargetClientFD(targetUser);
					
				// Your remaining code that uses soso...
				if (soso != -1){
					Client* soso1 = server->serverClientsMap[soso];
        			existingChannel->removeClientFromChannel(soso1, server);

	   if (!reason.empty()){
		   std::string kickCommand = ": KICK #" + channelName + " " + targetUser + " :" + reason + "\r\n";
		   					sendResponse(soso, kickCommand);

		
	   }else {
		   std::string kickCommand = ": KICK #" + channelName + " " + targetUser + " :" + oprName + "\r\n";
		   					sendResponse(soso, kickCommand);

	   }
       
					//std::string kickCommand = ": KICK #" + channelName + " " + targetUser + " :" + oprName + "\r\n";
				}
			} else {
				std::cout << "Error: targetUser is empty!" << std::endl;
			}
		} else {
			std::cout << "Error: existingChannel is null!" << std::endl;
		}
		
		// }
		
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void KickCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
   //1. check the client is it normal member or operator
	//2. then we send the command to either part operator client or partMemberClient
	std::string channelName = base->getParameters(command)[0];
	std::string targetUser = base->getParameters(command)[1];
	std::string reason = "";
	if (!base->getParameters(command)[2].empty()){
		std::string reason = base->getParameters(command)[2];
	}else {
		std::string reason = "";
	}
	

	if (channelName[0] == '#') {
		channelName = channelName.substr(1);
	}

			//checks if the client is in channel or not.

			std::map<std::string, Channel*>::iterator channelIterator = server->serverChannelsMap.find(channelName);
			if (channelIterator != server->serverChannelsMap.end()) {

						Channel *existingChannel = server->serverChannelsMap[channelName];
						std::vector<std::string> allClients = existingChannel->getAllClients2(server->serverClientsMap[clientSocket]->getNickName());
						bool found = std::find(allClients.begin(), allClients.end(), targetUser) != allClients.end();

				if (existingChannel->isClientOperator(client)) {
					
					if (found) {
						KickMemberClient(clientSocket, server, channelName, targetUser, reason);
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