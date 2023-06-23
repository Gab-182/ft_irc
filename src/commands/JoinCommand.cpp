# include "../../include/commands/JoinCommand.hpp"
#include "../../include/Client.hpp"
# include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
JoinCommand::JoinCommand() : ICommands() { }

JoinCommand::~JoinCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void JoinCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client) {
	// If the command 'join' has the correct parameters, then we can
	// execute the command and join or create the desired channel.
	if (base->getParameters().size() >= 1) {
		std::string channelName = base->getParameters()[0];
		if (channelName[0] == '#') {
			channelName = channelName.substr(1); // Remove the '#' character from the channel name.
		/*-----------------------------------------------------------------------------------------*/
			// If the channel doesn't exist, then we create it.
			if (server->serverChannelsMap.find(channelName) == server->serverChannelsMap.end()) {
				Channel* newChannel = new Channel(channelName, client);

				DEBUG_MSG("Channel: [" << channelName << "] has been created."
							<< std::endl << "Adding user: [" << client.getNickName() << "] to the channel.")

				// save the channel in the server's channels map.
				server->serverChannelsMap.insert(std::pair<std::string, Channel*>(channelName, newChannel));
				DEBUG_MSG("Channel " << channelName << " has been added to the server's channels map.")
			}
			// else if the channel is already created, then we add the user to the channel.
			else {

				DEBUG_MSG("Channel " << channelName << " already exists." << std::endl
									 << "Adding user: [" << client.getNickName() << "] to the channel.")

				server->serverChannelsMap[channelName]->addUser(client);
			}
		/*-----------------------------------------------------------------------------------------*/
			// We send a response to the client.
			std::string response = "Successfully joined channel: " + channelName;
			sendResponse(clientSocket, response); // Assuming you have a function to send the response
		} else {
			std::string response = "Invalid channel name. Channel names should start with '#'.";
			sendResponse(clientSocket, response); // Assuming you have a function to send the response
		}
	} else {
		std::string response = "Invalid parameters. Usage: /join #channel";
		sendResponse(clientSocket, response); // Assuming you have a function to send the response
	}

	// Cleaning the parameters vector before adding new ones to it.
	base->getParameters().clear();
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/