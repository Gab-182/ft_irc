#include "../../include/commands/QuitCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
QuitCommand::QuitCommand() : ICommands() { }

QuitCommand::~QuitCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void QuitCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	if (!base->getParameters(command).empty()) {
		if (Client::isClientAuthenticated(clientSocket, server)) {

			/*** TODO: [1] Send message for all users indicating that client has left.*/

			/*** [2] Remove the client from all the channels.*/
			std::map<std::string, Channel*>::iterator itChannels;
			for (itChannels = server->serverChannelsMap.begin(); itChannels != server->serverChannelsMap.end(); ++itChannels) {
				itChannels->second->removeClientFromChannel(client);
			}

			/*** [3] delete the client from the clients map in the server.*/
			server->serverClientsMap.erase(clientSocket);
			DEBUG_MSG(BOLDRED << "Client has been removed!!")

			/*** [4] send quit message to client using sendResponse() function.*/
			std::string quitMsg = ": 221" + client->getNickName() + " QUIT :Closing connection\r\n";
			sendResponse(clientSocket, quitMsg);

			/*** TODO: [5] If the client was the only user inside the channel, delete the channel from the server map.*/
		}
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/