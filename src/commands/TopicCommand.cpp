# include "../../include/commands/TopicCommand.hpp"
#include "../../include/Client.hpp"
# include "../../include/Server.hpp"

using namespace IRC;

TopicCommand::TopicCommand() : ICommands() { }
TopicCommand::~TopicCommand() { }


void TopicCommand::executeCommand(ICommands *base, const int &clientSocket, IRC::Server *server, Client *client,
								  const std::string &command) {

	/*
			? Set a topic			OR			? Get a topic that already exists 
		TOPIC <channel> [<topic>]					TOPIC <channel>
		1) Check # of arguments 2					1) Check # of arguments 1
		2) Check the channel exists					2) Check the channel exists
		3) Check the client is in the channel		3) Check the client is in the channel
		4) Check the client is operator				4) Check the client is operator
		5) Check the topic length ~200 characters	5) Display the topic
		6) Set the topic
		7) free topic if it exists then set the new one
		- update all clients in the channel with the new topic
		- update the channel topic
		!---------------------------REMAINS---------------------------!
		- //?check if the client is operator
	*/
	//if the number of parameters is 2
	std::string channelname = base->getParameters(command)[0];
	std::map<std::string, Channel *>::iterator itChannel;
	Channel *existingChannel = NULL;
	itChannel = server->serverChannelsMap.find(channelname);
	if (itChannel == server->serverChannelsMap.end()){
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_NOSUCHCHANNEL + " " +
			 client->getNickName() + " " + channelname + " :No such channel\r\n";
			sendResponse(clientSocket, response);
	}
	else if (base->getParameters(command).size() == 2)
	{	
		std::string topicname = base->getParameters(command)[1];
		 existingChannel = server->serverChannelsMap[channelname];
	
		//if the channel doesn't exist
		if (!server->serverChannelsMap.count(channelname)) {
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_NOSUCHCHANNEL + " " +
			 client->getNickName() + " " + channelname + " :No such channel\r\n";
			sendResponse(clientSocket, response);
 
		}
		// if the client is not in the channel
		else if(itChannel == server->serverChannelsMap.end())
		{
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_NOTONCHANNEL + " " +
			 client->getNickName() + " " + channelname + " :You're not on that channel\r\n";
			sendResponse(clientSocket, response);
		}
		else if (base->getParameters(command)[1].length() > 200)
		{
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " +  ERR_NOTONCHANNEL + " " +
			 client->getNickName() + " " + channelname + " :Topic is too long\r\n";
			sendResponse(clientSocket, response);
 		}
		else if (!existingChannel->isTopicLocked() || existingChannel->isClientOperator(client))//OR AN OPERATOR 
		{
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " TOPIC " + channelname + " :" + topicname + "\r\n";
			existingChannel->setTopic(topicname);
			std::cout << existingChannel->getTopic()<<std::endl;
			existingChannel->sendToAllClients("TOPIC", server->serverClientsMap[clientSocket]->getNickName(), response);
		}
		else
		{
			// NO PERMISSION
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_CHANOPRIVSNEEDED + " " +
			 client->getNickName() + " " + channelname + " :You're not channel operator\r\n";
			sendResponse(clientSocket, response);
		}
	}
	else if (base->getParameters(command).size() == 1)
	{
 		 existingChannel = server->serverChannelsMap[channelname];
 		//if the client in the channel
		if (!server->serverChannelsMap.count(channelname)) {
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_NOSUCHCHANNEL + " " +
			 client->getNickName() + " " + channelname + " :No such channel\r\n";
			sendResponse(clientSocket, response);
 
		}
		// no topic 
		else if (existingChannel->getTopic().empty())
		{
 			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " TOPIC " + channelname + " :" + existingChannel->getTopic() + "\r\n";
			std::cout << "no topic" << std::endl;
			sendResponse(clientSocket, response);
 
		}
		else
		{
 			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " TOPIC " + channelname + " :" + existingChannel->getTopic() + "\r\n";
			std::cout << "get the topic " << existingChannel << std::endl;
			sendResponse(clientSocket, response);
		}
	}
 }