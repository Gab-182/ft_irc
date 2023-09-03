#include "../../include/commands/ModeCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"
#include <cstdlib>
#include <iostream>
using namespace IRC;

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
	return (true);
}

void ModeCommand::TopicMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command,std::string channelName)
{	
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


void ModeCommand::LimitMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command, std::string channelName)
{
	std::string mode = base->getParameters(command)[1];
	const char modeChar = mode[1];
	char modeSign = mode[0];
	Channel* existingChannel = server->serverChannelsMap[channelName];
	if(existingChannel->isClientOperator(client))
	{
				std::cout << "-----------------------LIMIT----------------------" << std::endl;

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
			//set limit
			std::string limit = base->getParameters(command)[2];
			//convert string to size_t 
			char *p;
			size_t limitSize = strtoul(limit.c_str(),&p,10);
			if (*p)
			{
				std::cout << "not a number" << std::endl;
				return ;
			}
			else
			{
				std::cout << "set number" << limitSize << std::endl;
				existingChannel->setlimit(limitSize);
				std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + "\r\n"; 
				existingChannel->sendToAllClients("MODE",  server->serverClientsMap[clientSocket]->getNickName() , response);
			}
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

void ModeCommand::PasswordMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command, std::string channelName)
{
	std::string mode = base->getParameters(command)[1];
	const char modeChar = mode[1];
	char modeSign = mode[0];
	std::string password = base->getParameters(command)[2];
	Channel* existingChannel = server->serverChannelsMap[channelName];
		if (password.empty())
	{
		DEBUG_MSG("ERROR PASSWORD CANT BE EMPTY")
		return ;
	}
	if(existingChannel->isClientOperator(client))
	{
		if (modeSign == '-')
		{
			//remove the restriction and delete the mode from the channel
			existingChannel->removeMode(modeChar);
			existingChannel->setKey(NULL);
			//send response to all clients in the channel
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + "\r\n"; 
			existingChannel->sendToAllClients("MODE",   server->serverClientsMap[clientSocket]->getNickName() , response);
		}
		if(modeSign == '+')
		{ 
			existingChannel->addMode(modeChar);
			existingChannel->setKey(password);
			DEBUG_MSG(existingChannel->getKey());
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + " " + password + "\r\n"; 
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

void ModeCommand::OperMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command, std::string channelName)
{
	std::string mode = base->getParameters(command)[1];
	const char modeChar = mode[1];
	char modeSign = mode[0];
	std::string targetClient = base->getParameters(command)[2];
	Channel* existingChannel = server->serverChannelsMap[channelName];
	if (targetClient.empty())
	{
		DEBUG_MSG("ERROR PASSWORD CANT BE EMPTY")
		return ;
	}
	if (existingChannel->isClientinChannel(targetClient) == 0)
	{
			DEBUG_MSG("NICK NOT FOUND")
			std::string response = ERR_NOSUCHNICK(targetClient);
			sendResponse(clientSocket, response);
			return ;
	}
	if(existingChannel->isClientOperator(client))
	{
		//we get target client object
		int targetClientSocket = server->getClientSocket(targetClient);
		Client* targetClientObject = server->serverClientsMap[targetClientSocket];

		if (modeSign == '-')
		{
			//remove the restriction and delete the mode from the channel
			existingChannel->removeMode(modeChar);
			//existingChannel->removeOperatorFromChannel(targetClientObject, server);
			existingChannel->operatorToMember(targetClientObject);
			//send response to all clients in the channel
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + " " + targetClient + "\r\n"; 
			existingChannel->sendToAllClients("MODE",   server->serverClientsMap[clientSocket]->getNickName() , response);
		}
		if(modeSign == '+')
		{
			existingChannel->addMode(modeChar);
			//
			existingChannel->memberToOperator(targetClientObject);
			// existingChannel->removeMemberFromChannel(targetClientObject, server);
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + RPL_CHANNELMODEIS + " " + client->getNickName() + " #" + channelName + " " + mode + " " + targetClient + "\r\n"; 
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
	
	if (server->serverChannelsMap.find(channelName) == server->serverChannelsMap.end())
	{
		std::cout << "channel not exist" << std::endl;
		std::string response = ERR_NOSUCHCHANNEL(server->serverClientsMap[clientSocket]->getNickName(),channelName);
		sendResponse(clientSocket, response);
		return ;
	}
	else {
		std::string mode ;
		if (!base->getParameters(command).empty()) 
			mode = base->getParameters(command)[1];
		if (mode == "+t" || mode == "-t")
			TopicMode(base, clientSocket, server, client, command, channelName);
		//i
		else if ((mode == "+i" || mode == "-i") )
		{
			std::cout << "-----------------InviteOnlyMode--"<< mode <<"------------" << std::endl;
			InviteOnlyMode(base, clientSocket, server, client, command , channelName);
		}
		else if ((mode == "+l" || mode == "-l"))
			LimitMode(base, clientSocket, server, client, command , channelName);
		else if ((mode == "+k" || mode == "-k"))
			PasswordMode(base, clientSocket, server, client, command , channelName);
		else if ((mode == "+o" || mode == "-o"))
			OperMode(base, clientSocket, server, client, command , channelName);
		}
	

	} else {
		//check if the nick is valid or not
		if (base->getParameters(command)[1].empty() == true)
		{
			std::string mode = "+i";
			std::string response = ":" + channelName + " MODE " + channelName + " :+i\r\n";
			sendResponse(clientSocket,response);
		}
		else
		{
			std::string mode = base->getParameters(command)[1];
			std::string response = ":" + channelName + " MODE " + channelName + " :" + mode + "\r\n";
			sendResponse(clientSocket, response);
		}
	
	}
}


/*————————————————————————————--------------------------------------------------------------——————————————————————————*/