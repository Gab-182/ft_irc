#include "../../include/commands/ModeCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
/*** ——————————————————————-----------------------------------———————————————————————
 *** [ +i ]
 ***  Set/Remove Invite-only Channel:
 ***	# Client sends: MODE #channel +i
 ***	# Server responds: :server.name 324 yourNick #channel +i
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +t ]
 *** Set/Remove TOPIC Command Restrictions (+t):
 *** 	# Client sends: MODE #channel +t
 ***	# Server responds: :server.name 324 yourNick #channel +t
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +k ]
 *** Set/Remove Channel Key (Password) (+k):
 ***	# Client sends: MODE #channel +k password
 ***	# Server responds: :server.name 324 yourNick #channel +k password
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +o ]
 *** Give/Take Channel Operator Privilege (+o):
 ***	# Client sends: MODE #channel +o user
 ***	# Server responds: :server.name 381 yourNick #channel :You are now an operator
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +l ]
 *** Set/Remove User Limit to Channel (+l):
 ***	# Client sends: MODE #channel +l limit
 ***	# Server responds: :server.name 324 yourNick #channel +l limit
 *** ——————————————————————-----------------------------------———————————————————————
 ***/

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ModeCommand::ModeCommand() : ICommands() { }

ModeCommand::~ModeCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool ModeCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	(void) client;
	(void) command;
	(void) base;

	// // MODE <channel name> <mode>
	if (base->getParameters(command).size() < 2) {
		DEBUG_MSG(BOLDRED << " wrong parameters......!! ")

		std::string authErrMsg = BOLDRED "Please make sure you entered: "
								 BOLDYELLOW "MODE "
								 BOLDWHITE "<channel_name> <mode> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}
	// client not 
	else if (!Client::isClientAuthenticated(clientSocket, server)) {
		DEBUG_MSG(BOLDRED << " client not authenticated yet!! ")

		std::string authErrMsg = BOLDRED "Please make sure you entered: "
								 BOLDWHITE "[PassWord] "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}
	
//	// check if client is in channel and is channel operator
//	else if (!server->isClientInChannel(client.getNickname(), base->getParameters(command)[0])) {
//		DEBUG_MSG(BOLDRED << " client not in channel!! ")
//
//		std::string authErrMsg = BOLDRED "Please make sure you entered: "
//								 BOLDWHITE "[Channel Name] "
//								 BOLDRED "correctly!!" RESET "\r\n";
//		sendResponse(clientSocket, authErrMsg);
//		return (false);
//	}
//
//	else if (!server->isClientChannelOperator(client.getNickname(), base->getParameters(command)[0])) {
//		DEBUG_MSG(BOLDRED << " client not channel operator!! ")
//
//		std::string authErrMsg = BOLDRED "Please make sure you entered: "
//								 BOLDWHITE "[Channel Operator] "
//								 BOLDRED "correctly!!" RESET "\r\n";
//		sendResponse(clientSocket, authErrMsg);
//		return (false);
//	}

	return (true);
}

void ModeCommand::TopicMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command,std::string channelName)
{	
	// std::map<std::string, Channel*>::iterator it = server->serverChannelsMap.find(channelName);
	// t set/remove the ristriction of the topic command to channel operators only
	// if +t set risriction
	// if -t remove restriction
	/*
		+t
			1) if the client in the channel
			2) if the client is operator
			3) if the channel is not already +t
			4) set the channel to +t
			5) send response to all clients in the channel
		-t
			1) if the client in the channel
			2) if the client is operator
			3) if the channel is already +t
			4) set the channel to -t
			5) send response to all clients in the channel

	*/

	//------------------------------------------------------------//
	// std::string channelName = base->getParameters(command)[0];
	// Channel* existingChannel = NULL;
	// if (channelName[0] == '#'){
	// 	 channelName = channelName.substr(1);}
	std::string mode = base->getParameters(command)[1];
	const char modeChar = mode[1];
	char modeSign = mode[0];
	Channel* existingChannel = server->serverChannelsMap[channelName];
	//------------------------------------------------------------//

	if(existingChannel->isClientOperator(client))
	{
		if(modeSign == '-')
		{
			//remove the restriction and delete the mode from the channel
			existingChannel->removeMode(modeChar);
			//send response to all clients in the channel
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + "\r\n"; 
			existingChannel->sendToAllClients("MODE",   server->serverClientsMap[clientSocket]->getNickName() , response);
		}
		else if(modeSign == '+')
		{
			std::cout << "client is operator" << std::endl;
			existingChannel->addMode(modeChar);
			for (size_t i = 0 ; i < existingChannel->getModes().size(); i++)
				std::cout <<  existingChannel->getModes()[i] << std::endl;
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + "\r\n"; 
			existingChannel->sendToAllClients("MODE",  server->serverClientsMap[clientSocket]->getNickName() , response);
		}
	}
	else
	{
		std::cout << "client is not operator MODE" << std::endl;
		std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_CHANOPRIVSNEEDED + " " +
			client->getNickName() + " #" + channelName + " :You're not channel operator\r\n";
		sendResponse(clientSocket, response);
	}
}

void ModeCommand::InviteOnlyMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command, std::string channelName)
{
	// std::cout << "-----------------InviteOnlyMode--------------" << std::endl;
	// std::string channelName = base->getParameters(command)[0];
	// Channel* existingChannel = NULL;
	// if (channelName[0] == '#'){
	// 	 channelName = channelName.substr(1);
	// }
	std::string mode = base->getParameters(command)[1];
	const char modeChar = mode[1];
	char modeSign = mode[0];
	Channel* existingChannel = server->serverChannelsMap[channelName];
	if(existingChannel->isClientOperator(client))
	{
		if (modeSign == '-')
		{
			//remove the restriction and delete the mode from the channel
			existingChannel->removeMode(modeChar);
			//send response to all clients in the channel
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + "\r\n"; 
			existingChannel->sendToAllClients("MODE",   server->serverClientsMap[clientSocket]->getNickName() , response);
		}
		if(modeSign == '+')
		{
			existingChannel->addMode(modeChar);
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + "\r\n"; 
			existingChannel->sendToAllClients("MODE",  server->serverClientsMap[clientSocket]->getNickName() , response);
		}
	}
	else
	{
		std::cout << "client is not operator MODE" << std::endl;
		std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_CHANOPRIVSNEEDED + " " +
			client->getNickName() + " #" + channelName + " :You're not channel operator\r\n";
		sendResponse(clientSocket, response);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ModeCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	if (!noErrorsExist(base, clientSocket, server, client, command))
		return ;
	//check channel name if existied or not
	std::string channelName = base->getParameters(command)[0];

	if (channelName[0] == '#'){
		 channelName = channelName.substr(1);
	}
	if (server->serverChannelsMap.find(channelName) == server->serverChannelsMap.end())
	{
		std::cout << "channel not exist" << std::endl;
		std::string response = ERR_NOSUCHCHANNEL(server->serverClientsMap[clientSocket]->getNickName(),channelName);
		// sendResponse(clientSocket, response);
		return ;
	}
	else
	{
		std::string mode ;
		if (!base->getParameters(command).empty()) 
			mode = base->getParameters(command)[1];
		std::cout << "====>> mode: " << mode << std::endl;
		if (mode == "+t" || mode == "-t")
			TopicMode(base, clientSocket, server, client, command, channelName);
		//i
		else if ((mode == "+i" || mode == "-i") )
		{
			std::cout << "-----------------InviteOnlyMode--"<< mode <<"------------" << std::endl;
			InviteOnlyMode(base, clientSocket, server, client, command , channelName);
		}
	}
	//l
	//k
	//o
}


/*————————————————————————————--------------------------------------------------------------——————————————————————————*/