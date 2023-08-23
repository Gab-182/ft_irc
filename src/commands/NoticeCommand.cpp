#include "../../include/commands/NoticeCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
NoticeCommand::NoticeCommand() : ICommands() { }

NoticeCommand::~NoticeCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool NoticeCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
	if (base->isParameterEmpty(command) || base->getParameters(command).size() < 2) {
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string paramErrMsg = ":"
								  ERR_NEEDMOREPARAMS " "
								  BOLDRED ":Wrong parameters!! "
								  BOLDWHITE "<#Channel_name> <Message>"
								  RESET "\r\n";
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
void NoticeCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
	(void) client;

	std::string channelName = base->getParameters(command)[0];

	//if # is found this means privmsg to channel
	//else means privmsg to user.
	if (channelName[0] == '#')
	{
		std::string channelName2 = channelName.substr(1);
		std::map<std::string, Channel *>::iterator itChannel;
		itChannel = server->serverChannelsMap.find(channelName2);
		std::string nickName = server->serverClientsMap[clientSocket]->getNickName();

		if (itChannel != server->serverChannelsMap.end())
		{
			Channel *existingChannel = server->serverChannelsMap[channelName2];
			int found = existingChannel->isClientinChannel(nickName);

			if (found == 0)
			{
				std::string response = ERR_USERNOTINCHANNEL(nickName, channelName2);
				sendResponse(clientSocket, response);
			}
			else 
			{
				if (base->getParameters(command).size() > 1)
				{
					
					std::string message = base->getParameters(command)[1];
					for (unsigned int i = 2; i < base->getParameters(command).size(); i++){
						DEBUG_MSG(base->getParameters(command)[i]);
						message += " " + base->getParameters(command)[i];
					}
					
					std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " NOTICE " + channelName + " :" + message + "\r\n";
					existingChannel->sendToAllClients("NOTICE",server->serverClientsMap[clientSocket]->getNickName(),response);
					std::cout << "sending" << message << std::endl;
				}
				else
				{
					std::string message = base->getParameters(command)[1];
					for (unsigned int i = 2; i < base->getParameters(command).size(); i++){
						DEBUG_MSG(base->getParameters(command)[i]);
						message += " " + base->getParameters(command)[i];
					}
					std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " NOTICE " + channelName + " :" + message + "\r\n";
					existingChannel->sendToAllClients("NOTICE",server->serverClientsMap[clientSocket]->getNickName(),response);
					std::cout << "sending " << message << std::endl;
				}
			}
		}
		else
		{
			std::string response = ERR_NOSUCHCHANNEL(nickName, channelName);
			sendResponse(clientSocket, response);
		}
			
	} else {
		
			std::string nickName = server->serverClientsMap[clientSocket]->getNickName();
			int foundNick = server->getClients(channelName);
			if (foundNick == 1)
			{
				std::string message = base->getParameters(command)[1];
					for (unsigned int i = 2; i < base->getParameters(command).size(); i++){
						DEBUG_MSG(base->getParameters(command)[i]);
						message += " " + base->getParameters(command)[i];
					}
				std::string response = ":" + server->serverClientsMap[clientSocket]->getNickName() + " NOTICE " + channelName + " :" + message + "\r\n";
				int targetClientSocket = server->getSocket(channelName);
				if (targetClientSocket == -1)
					DEBUG_MSG("ERROR: target client socket not found ERROR")
				sendResponse(targetClientSocket, response);
				DEBUG_MSG("NICK  FOUND")

			} else {
				DEBUG_MSG("NICK NOT FOUND")
				std::string response = ERR_NOSUCHNICK(channelName);
				sendResponse(clientSocket, response);
			}

	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
