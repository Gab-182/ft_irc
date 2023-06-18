# include "../../include/commands/JoinCommand.hpp"
using namespace IRC;

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
JoinCommand::JoinCommand() : ICommands() {}

JoinCommand::~JoinCommand() {}

/*————————————————————————————--------------------------------------------------------------———————————————————————————*/
void JoinCommand::executeCommand(ICommands* base, const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels) {
	(void)clients;
	(void)channels;

	// If the command 'join' has the correct parameters, then we can
	// execute the command and join or create the desired channel.
	std::cout << BOLDGREEN << "_command: " << base->getCommand() << std::endl;
//	std::cout << "_parameters.size(): " << _parameters.size() << std::endl;
//	std::cout << "_parameters[0]:  " << _parameters[0] << std::endl;
//	std::cout << "_parameters[0][0]:  " << _parameters[0][0] << std::endl;
//	std::cout << "_parameters[0][1]:  " << _parameters[0][1] << std::endl;

	if (_parameters.size() >= 1) {
		std::string channelName = _parameters[0];
		if (channelName[0] == '#') {
			channelName = channelName.substr(1); // Remove the '#' character
			// Join or create the channel here
			// ...
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
}
/*————————————————————————————--------------------------------------------------------------———————————————————————————*/