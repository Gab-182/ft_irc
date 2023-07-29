#include "../../include/commands/KickCommand.hpp"
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
KickCommand::KickCommand() : ICommands() {}

KickCommand::~KickCommand() {}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool KickCommand::noErrorsExist(ICommands *base, const int &clientSocket, IRC::Server *server, const std::string &command)
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
void KickCommand::KickMemberClient(const int &clientSocket, Server *server, const std::string &channelName, const std::string &targetUser, const std::string &reason)
{


	 std::map<std::string, Channel *>::iterator itChannel;
	 Channel *existingChannel = NULL;
	 itChannel = server->serverChannelsMap.find(channelName);
	 std::string oprName = server->serverClientsMap[clientSocket]->getNickName();
	

	// Check if existingChannel is a valid pointer
	if (itChannel != server->serverChannelsMap.end())
	{
		 existingChannel = server->serverChannelsMap[channelName];
		if (!targetUser.empty())
		{
			if (existingChannel->isClientinChannel(targetUser) == 1)
			{
				int soso = existingChannel->getTargetClientFD(targetUser);
				if (soso != -1)
				{
					Client *soso1 = server->serverClientsMap[soso];
					existingChannel->removeClientFromChannel(soso1, server);
					if (!reason.empty())
					{
						std::string kickCommand = ":" + oprName + " KICK #" + channelName + " " + targetUser + " " + reason + "\r\n";
						sendResponse(soso, kickCommand);
					}
					else
					{
						std::string kickCommand = ": KICK #" + channelName + " " + targetUser + " " + oprName + "\r\n";
						sendResponse(soso, kickCommand);
					}
				}
			}
			else
			{
				std::string response = ERR_USERNOTINCHANNEL(targetUser, channelName);
				sendResponse(clientSocket, response);
			}
			
		}
		else
		{
			std::string response = ERR_NOSUCHNICK(targetUser);
			sendResponse(clientSocket, response);
		}
	}
	else
	{
		std::string response = ERR_NOSUCHCHANNEL(oprName, channelName);
		sendResponse(clientSocket, response);
	}
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void KickCommand::executeCommand(ICommands *base, const int &clientSocket, Server *server, Client *client, const std::string &command)
{
	//1. check the client is it normal member or operator
	//2. then we send the command to either part operator client or partMemberClient
	std::string channelName = base->getParameters(command)[0];
	std::string targetUser = base->getParameters(command)[1];

	if (channelName[0] == '#')
	{
		channelName = channelName.substr(1);
	}

	//checks if the client is in channel or not.
	std::map<std::string, Channel *>::iterator channelIterator = server->serverChannelsMap.find(channelName);
	if (channelIterator != server->serverChannelsMap.end())
	{

		Channel *existingChannel = server->serverChannelsMap[channelName];
		std::vector<std::string> allClients = existingChannel->getAllClients2(server->serverClientsMap[clientSocket]->getNickName());
		bool found = std::find(allClients.begin(), allClients.end(), targetUser) != allClients.end();

		//checks if client is operator
		if (existingChannel->isClientOperator(client))
		{

			//check if client is in channel or not
			if (found)
			{
				if (!base->getParameters(command)[2].empty())
				{
					std::string reason = base->getParameters(command)[2];
					KickMemberClient(clientSocket, server, channelName, targetUser, reason);
				}
				else
				{
					KickMemberClient(clientSocket, server, channelName, targetUser, "");
				}
			}
			else
			{

				// Send error response for user not found in the channel
				std::string response = ": 441 * <" + targetUser + "> isn't on #" + channelName + "\n\r";
				sendResponse(clientSocket, response);
			}
		}
		else
		{

			// Send error response for insufficient operator permissions
			std::string response = ": 482 " + server->serverClientsMap[clientSocket]->getNickName() + " #" + channelName + " :You're not a channel operator\r\n";
			sendResponse(clientSocket, response);
		}
	}
	else
	{

		// Send error response for non-existent channel
		std::string response = ": 403 " + server->serverClientsMap[clientSocket]->getNickName() + " #" + channelName + " :No such channel\r\n";
		sendResponse(clientSocket, response);
	}
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/