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
		5) Set the topic
			
	*/
	(void)base;
	(void)client;
	(void)server;
	(void)clientSocket;
	(void)command;

	std::cout <<base->getParameters(command).size() << std::endl;
	//if the number of parameters is 2
	if(base->getParameters(command).size() == 2)
	{

		//if the channel doesn't exist
		if (!server->serverChannelsMap.count(base->getParameters(command)[0])) {
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_NOSUCHCHANNEL + " " +
			 client->getNickName() + " " + base->getParameters(command)[0] + " :No such channel\r\n";
			std::cout << "channel doesn't exist" << std::endl;
			sendResponse(clientSocket, response);
		}
		// if the client is not in the channel
		std::map<std::string, Channel*>::iterator it = server->serverChannelsMap.find(base->getParameters(command)[0]);
		if(it == server->serverChannelsMap.end())
		{
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_NOTONCHANNEL + " " +
			 client->getNickName() + " " + base->getParameters(command)[0] + " :You're not on that channel\r\n";
			std::cout << "client is not in the channel" << std::endl;
			sendResponse(clientSocket, response);
		}
		// TODO if the client is not operator
		//if the topic length is greater than 200 characters
		if(base->getParameters(command)[1].length() > 200)
		{
			std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " +  ERR_NOTONCHANNEL + " " +
			 client->getNickName() + " " + base->getParameters(command)[0] + " :Topic is too long\r\n";
			std::cout << "topic is too long" << std::endl;
			sendResponse(clientSocket, response);
		}
		//set the topic 
		it->second->setTopic(base->getParameters(command)[1]);
		std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " TOPIC " + base->getParameters(command)[0] + " :" + base->getParameters(command)[1] + "\r\n";
		std::cout << "set the topic" << std::endl;
		sendResponse(clientSocket, response);
	}
	// todo else if (base->getParameters(command).size() == 1)
	// {

	// }
	else
	{
		std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " " + ERR_NEEDMOREPARAMS + " " + client->getNickName() + " TOPIC :Not enough parameters\r\n";
		sendResponse(clientSocket, response);
		return;
	}
	std::cout << "eeee"<< std::endl;
	std::string channelName = base->getParameters(command)[0];
	std::cout << "channelName: " << channelName << " " << base->getParameters(command)[1] << std::endl;
}