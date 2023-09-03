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

		std::string memberMsg = BOLDGREEN " Successfully joined channel: ["
							+ channelName
							+ "] as a operator."
							+ RESET "\r\n";
	sendResponse(clientSocket, memberMsg);

	std::string msgToAll = ":"
							+ server->serverClientsMap[clientSocket]->getNickName()
							+ " JOIN #"
							+ channelName +
							"\r\n";
	newChannel->sendToAllClients("JOIN", server->serverClientsMap[clientSocket]->getNickName(), msgToAll);
	std::string userListResponse = ": 353 " + client->getNickName() + " = " + channelName + " :@" + client->getNickName() + "\r\n";
    sendResponse(clientSocket, userListResponse);

	std::string totalNicksResponse = ": 366 " + client->getNickName() + " " + channelName + " :End of /NAMES list\r\n";
	sendResponse(clientSocket, totalNicksResponse);
	std::cout << "---------------------121----------"<<std::endl;
	std::string response3 = ":irc 332 " + client->getNickName() + " " + channelName + " :" + newChannel->getTopic() + "\r\n" ;
	sendResponse(clientSocket,response3);
	std::cout << "---------------------131----------"<<std::endl;
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

	std::string msgToAll = ":"
							+ server->serverClientsMap[clientSocket]->getNickName()
							+ " JOIN #"
							+ channelName +
							"\r\n";
	existingChannel->sendToAllClients("JOIN", server->serverClientsMap[clientSocket]->getNickName(), msgToAll);
	std::string allClients = existingChannel->getAllClients(server->serverClientsMap[clientSocket]->getNickName());
	std::string userListResponse = ": 353 " + client->getNickName() + " = " + channelName + " :" + allClients + "\r\n";
    sendResponse(clientSocket, userListResponse);

	std::string totalNicksResponse = ": 366 " + client->getNickName() + " " + channelName + " :End of /NAMES list\r\n";
	sendResponse(clientSocket, totalNicksResponse);

	std::string response3 = ":irc 332 " + client->getNickName() + " " + channelName + " :" + existingChannel->getTopic() + "\r\n";
	sendResponse(clientSocket,response3);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void JoinCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {

	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	std::string channelName = base->getParameters(command)[0];
	if (channelName[0] == '#') 
	{
		channelName = channelName.substr(1); // Remove the '#' character from the channel name.

		/*-----------------------------------------------------------------------------------------*/
		// If the channel name is valid: Check if the channel exists in the server channels map.
		std::map<std::string, Channel *>::iterator itChannel;
		itChannel = server->serverChannelsMap.find(channelName);
		Channel *existingChannel = NULL;
		if (itChannel == server->serverChannelsMap.end())
		{
				std::cout << "user operator" << std::endl;
			joinOperatorClient(clientSocket, server, client, channelName);
		}
		else
		{
			existingChannel = server->serverChannelsMap[channelName];
			std::string userName = server->serverClientsMap[clientSocket]->getNickName();

			if (existingChannel->isClientinChannel(userName) == 1)
			{
				std::cout << "user is already in channel" << std::endl;
					sendResponse(clientSocket, ERR_USERONCHANNEL(userName));
			}
			else
			{
				existingChannel = server->serverChannelsMap[channelName];
				// existingChannel->printModes();
				// existingChannel->printInvitees();
				std::string userName = server->serverClientsMap[clientSocket]->getNickName();

				// std::cout << "SIZE -->"<<base->getParameters(command).size() << std::endl;
				if(existingChannel->isPasswordLocked() == true) {
					if (base->getParameters(command).size() != 2  || existingChannel->isPasswordCorrect(base->getParameters(command)[1]) == false)
					{
						std::cout << "pass check" << std::endl;
							sendResponse(clientSocket, ERR_BADCHANNELKEY(userName, channelName));
					}
					else {
						joinMemberClient(clientSocket, server, client, channelName);
						//sendResponse(clientSocket, RPL_CHANNELMODEIS(userName, channelName, existingChannel->getModes()));
					}
				}
				else if (existingChannel->isChannelLimitedMode() && (existingChannel->getlimit() <= existingChannel->getChannelUsersNumber()))
					sendResponse(clientSocket, ERR_CHANNELISFULL(channelName));
				else if (existingChannel->isClientinChannel(userName) == 1)
					sendResponse(clientSocket, ERR_USERONCHANNEL(userName));
				else if(existingChannel->isChannelInviteOnly() && existingChannel->isClientInvited(client))
					this->joinMemberClient(clientSocket, server, client, channelName);
				else if(!existingChannel->isChannelInviteOnly()) //channel is not invite only
					this->joinMemberClient(clientSocket, server, client, channelName);
				else
					sendResponse(clientSocket, ERR_INVITEONLYCHAN(userName, channelName));
			}
		}
	}
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