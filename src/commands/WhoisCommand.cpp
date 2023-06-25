#include "../../include/commands/WhoisCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
WhoisCommand::WhoisCommand() : ICommands() { }

WhoisCommand::~WhoisCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void WhoisCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client, const std::string& command) {
	(void) client;

	if (!base->getParameters(command).empty()) {
		std::string clientNick = base->getParameters(command)[0];

		std::map<int, Client*>::iterator whoisIt;
		for (whoisIt = server->serverClientsMap.begin(); whoisIt != server->serverClientsMap.end(); ++whoisIt) {
			if (whoisIt->second->getNickName() == clientNick) {
				if (Client::isClientRegistered(clientSocket, server)) {
					std::string response = "311 " + whoisIt->second->getNickName()
										   + " " + whoisIt->second->getUserName()
										   + " * :" + whoisIt->second->getUserName()
										   + "\r\n";
					sendResponse(clientSocket, response);
					return;
				}
			}
		}
		sendResponse(clientSocket, "401 "
									+ server->serverClientsMap[clientSocket]->getNickName()
									+ " :No such nick/channel\r\n");
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
