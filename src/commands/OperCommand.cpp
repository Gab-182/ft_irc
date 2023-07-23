#include "../../include/commands/OperCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

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
OperCommand::OperCommand() : ICommands() {}

OperCommand::~OperCommand() {}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool OperCommand::noErrorsExist(ICommands *base, const int &clientSocket, IRC::Server *server, const std::string &command)
{
	if (base->isParameterEmpty(command))
	{
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string authErrMsg = ":" ERR_NEEDMOREPARAMS
			BOLDRED " Please make sure you entered: " BOLDYELLOW "/join " BOLDWHITE "<channel_name> " BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

	if (!Client::isClientRegistered(clientSocket, server))
	{
		DEBUG_MSG(BOLDRED << " client not registered yet!! ")

		std::string authErrMsg = ":" ERR_NOTREGISTERED
		BOLDRED " Please make sure you entered: " BOLDWHITE "<password> <nickname> <username> " BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}
	return (true);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void OperCommand::executeCommand(ICommands *base, const int &clientSocket, Server *server, Client *client, const std::string &command)
{
	(void)clientSocket;
	(void)client;
	//1. check the client is it normal member or operator
	//2. then we send the command to either part operator client or partMemberClient
	std::string channelName = base->getParameters(command)[0];
	std::string ss = server->serverClientsMap[clientSocket]->getChannelName1();
	std::cout << "param0: #" << ss << std::endl;
	// std::string operName = base->getParameters(command)[1];
	 Channel *existingChannel = server->serverChannelsMap[ss];
	int soso = existingChannel->getTargetClientFD(channelName);
	//std::string targetUser = base->getParameters(command)[1];

	// if (channelName[0] == '#')
	// {
	// 	channelName = channelName.substr(1);
	// }

	 std::string response = ":irc_server 381 " + channelName + " :You are now an IRC operator\r\n";
	 sendResponse(soso,response);
	// //checks if the client is in channel or not.
	// std::map<std::string, Channel *>::iterator channelIterator = server->serverChannelsMap.find(channelName);
	// if (channelIterator != server->serverChannelsMap.end())
	// {

	// 	Channel *existingChannel = server->serverChannelsMap[channelName];
	// 	std::vector<std::string> allClients = existingChannel->getAllClients2(server->serverClientsMap[clientSocket]->getNickName());
	// 	bool found = std::find(allClients.begin(), allClients.end(), targetUser) != allClients.end();

	// 	//checks if client is operator
	// 	if (existingChannel->isClientOperator(client))
	// 	{

	// 		//check if client is in channel or not
	// 		if (found)
	// 		{
	// 			if (!base->getParameters(command)[2].empty())
	// 			{
	// 				std::string reason = base->getParameters(command)[2];
	// 				KickMemberClient(clientSocket, server, channelName, targetUser, reason);
	// 			}
	// 			else
	// 			{
	// 				KickMemberClient(clientSocket, server, channelName, targetUser, "");
	// 			}
	// 		}
	// 		else
	// 		{

	// 			// Send error response for user not found in the channel
	// 			std::string response = ": 441 * <" + targetUser + "> isn't on #" + channelName + "\n\r";
	// 			sendResponse(clientSocket, response);
	// 		}
	// 	}
	// 	else
	// 	{

	// 		// Send error response for insufficient operator permissions
	// 		std::string response = ": 482 " + server->serverClientsMap[clientSocket]->getNickName() + " #" + channelName + " :You're not a channel operator\r\n";
	// 		sendResponse(clientSocket, response);
	// 	}
	// }
	// else
	// {

	// 	// Send error response for non-existent channel
	// 	std::string response = ": 403 " + server->serverClientsMap[clientSocket]->getNickName() + " #" + channelName + " :No such channel\r\n";
	// 	sendResponse(clientSocket, response);
	// }
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/