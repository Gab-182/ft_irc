#include "../../include/commands/QuitCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
QuitCommand::QuitCommand() : ICommands() { }

QuitCommand::~QuitCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool QuitCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command) {
	(void) base;
	(void) command;

	if (!Client::isClientRegistered(clientSocket, server)) {
		DEBUG_MSG(BOLDRED << " client not registered yet!! ")

		std::string authErrMsg = ":"
								 ERR_NOTREGISTERED
								 BOLDRED " Please make sure you entered: "
								 BOLDWHITE "<password> <nickname> <username> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}
	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void QuitCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	if (!noErrorsExist(base, clientSocket, server, command))
		return;
	/**
	 * TODO: Send message for all users that inside all the channels that the user was in indicating that client has left
	 *
	 * TODO: If the client was the only user inside the channel, delete the channel from the server map.
	 */

	std::string quitMsg = ": " + client->getNickName() + " QUIT :Closing connection\r\n";
	sendResponse(clientSocket, quitMsg);
	client->removeClientFromServer(clientSocket, server, client);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/