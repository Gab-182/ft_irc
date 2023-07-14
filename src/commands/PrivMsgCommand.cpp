#include "../../include/commands/PrivMsgCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
PrivMsgCommand::PrivMsgCommand() : ICommands() { }

PrivMsgCommand::~PrivMsgCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool PrivMsgCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
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
void PrivMsgCommand::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
	(void) client;

	if (!noErrorsExist(base, clientSocket, server, command))
		return;

	std::string channelName = base->getParameters(command)[0];
	if (channelName[0] == '#') {
		channelName = channelName.substr(1);

		// TODO: Check if the channel existed in the server's channels map
		// TODO: Check if the client is a member or operator inside the channel.

	}

	/*-----------------------------------------------------------------------------------------*/
	// If the channel name is invalid: Send a response to the client.
	/*-----------------------------------------------------------------------------------------*/
	else {
		std::string response =  BOLDRED"Invalid channel name."
								BOLDWHITE "Channel names should start with '#'."
								RESET "\r\n";
		sendResponse(clientSocket, response);
	}

}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
