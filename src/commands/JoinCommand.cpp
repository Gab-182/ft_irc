# include "../../include/commands/JoinCommand.hpp"
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
JoinCommand::JoinCommand() : ICommands() {}

JoinCommand::~JoinCommand() {}

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
void JoinCommand::executeCommand(ICommands* base, const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels) {
	(void)clients;
	(void)channels;

	std::string command = base->getCommand();
	std::vector<std::string> parameters = base->getParameters();

	// If the command 'join' has the correct parameters, then we can
	// execute the command and join or create the desired channel.
	if (parameters.size() >= 1) {
		std::string channelName = parameters[0];
		if (channelName[0] == '#') {
			channelName = channelName.substr(1); // Remove the '#' character from the channel name.
			std::cout << "Channel name: " << channelName << std::endl;
		/*-----------------------------------------------------------------------------------------*/
//			// check if the channel already exists
//			bool channelExists = false;
//
//			for (auto& channel : channels) {
//				if (channel.getName() == channelName) {
//					channelExists = true;
//					break;
//				}
//			}
//			// If the channel doesn't exist, then we create it.
//			if (!channelExists) {
//				Channel newChannel(channelName);
//				channels.push_back(newChannel);
//			}
//			// We add the client to the channel.
//			for (auto& channel : channels) {
//				if (channel.getName() == channelName) {
//					channel.addOperator(clientSocket);
//					break;
//				}
//			}

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
	parameters.clear();
}
/*————————————————————————————--------------------------------------------------------------———————————————————————————*/