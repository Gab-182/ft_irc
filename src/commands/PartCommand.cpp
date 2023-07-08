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
    Channel* channel = server->serverChannelsMap[channelName];
    
    // Remove the client from the channel's operator vector.
    channel->removeOperatorFromChannel(client,server);
    
    // Check if the client is also a member of the channel.
    if (1 == 1) {
        // If the client is a member, remove them from the channel's member vector.
        channel->removeMemberFromChannel(client,server);
        
        // Send a PART message to the client indicating their departure from the channel.
        std::string response = ":" + client->getNickName() + " PART #" + channelName + "\r\n";
        sendResponse(clientSocket, response);
    }
    
    // Send a response to the client confirming their departure from the channel.
    std::string response2 = "You have left the channel #" + channelName + "\r\n";
    sendResponse(clientSocket, response2);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PartCommand::partMemberClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName) {
    Channel* channel = server->serverChannelsMap[channelName];
    
    // Remove the client from the channel's member vector.
    channel->removeMemberFromChannel(client,server);
    
    // Send a PART message to the client indicating their departure from the channel.
    std::string response = ":" + client->getNickName() + " PART #" + channelName + "\r\n";
    sendResponse(clientSocket, response);
    
    // Send a response to the client confirming their departure from the channel.
    std::string response2 = "You have left the channel #" + channelName + "\r\n";
    sendResponse(clientSocket, response2);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void PartCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
    if (!noErrorsExist(base, clientSocket, server, command))
        return;
    
    std::string channelName = base->getParameters(command)[0];
    
    if (channelName[0] == '#') {
        channelName = channelName.substr(1); // Remove the '#' character from the channel name.
        
        // If the channel name is valid, check if the channel exists in the server channels map.
        std::map<std::string, Channel*>::iterator itChannel = server->serverChannelsMap.find(channelName);
        
        if (itChannel == server->serverChannelsMap.end()) {
            // Channel does not exist
            std::string response = BOLDRED "The channel #" + channelName + " does not exist.\r\n";
            sendResponse(clientSocket, response);
        } else {
            // Channel exists
            //Channel* channel = itChannel->second;
            
            if (1 == 1) {
                // Client is an operator of the channel
                partOperatorClient(clientSocket, server, client, channelName);
            } else if (2 == 2) {
                // Client is a member of the channel
                partMemberClient(clientSocket, server, client, channelName);
            } else {
                // Client is not in the channel
                std::string response = BOLDRED "You are not a member of the channel #" + channelName + ".\r\n";
                sendResponse(clientSocket, response);
            }
        }
    } else {
        // Invalid channel name
        std::string response = BOLDRED "Invalid channel name. Channel names should start with '#'.\r\n";
        sendResponse(clientSocket, response);
    }
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/