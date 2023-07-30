#include "../../include/commands/WhoisCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
WhoisCommand::WhoisCommand() : ICommands() { }

WhoisCommand::~WhoisCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool WhoisCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
	if (base->isParameterEmpty(command)) {
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string authErrMsg = ":"
								 ERR_NEEDMOREPARAMS " "
								 BOLDRED ":Please make sure you entered: "
								 BOLDYELLOW "/whois "
								 BOLDWHITE "<nickname> "
								 BOLDRED "correctly!!"
								 RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

	if (!Client::isClientRegistered(clientSocket, server)) {
		DEBUG_MSG(BOLDRED << "client not registered yet!!")

		std::string regErrMsg = ":"
								 ERR_NOTREGISTERED " "
								 BOLDRED ":Please make sure you entered: "
								 BOLDWHITE "<password> <nickname> <username> "
								 BOLDRED "correctly!!!"
								 RESET "\r\n";
		sendResponse(clientSocket, regErrMsg);
		return (false);
	}

	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void WhoisCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	(void)client;
	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	std::string clientNick = base->getParameters(command)[0];

	std::map<int, Client*>::iterator whoisIt;
	for (whoisIt = server->serverClientsMap.begin(); whoisIt != server->serverClientsMap.end(); ++whoisIt) {
		if (whoisIt->second->getNickName() == clientNick) {
			if (Client::isClientRegistered(clientSocket, server)) {
				std::string response = ":"
										RPL_WHOISUSER " "
										+ whoisIt->second->getNickName()
										+ " * :" + whoisIt->second->getUserName()
										+ "\r\n";
				sendResponse(clientSocket, response);
				return;
			}
			else {
				std::string response = ERR_NOSUCHNICK(whoisIt->second->getNickName());
				sendResponse(clientSocket, response);
				return;
			}
		}
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
