# include "../../include/Commands.hpp"

using namespace IRC;

Commands::Commands() {}

Commands::~Commands() {}

/*————————————————————————————————⟪⟪ JOIN ⟫⟫———————————————————————————————*/
void Commands::join(int clientSocket, const std::string& channelName) {
	/*
	 ** parse the message.
	 *
	 ** if the command join is correctly written then:
	 **		if channel is not there:
	 *			create it
	 *		if the channel already created:
	 *			check the mode of the channel
	 **/

	std::string msg = ":"+clientNick+"!~"+clientName+"@"+host+" JOIN #"+channelName+"\r\n";
	if (send(clientSocket, msg.c_str(), msg.length(), 0) == -1) {
		DEBUG_MSG("Error sending [" << msg << "] to client");
	}
}

/*————————————————————————————⟪⟪ SEND Command ⟫⟫———————————————————————————*/
void Commands::handleCommands(int clientSocket, const std::string& clientMsg) {
	(void)clientSocket;

	std::istringstream iss(clientMsg);
	std::string commandMessage;
	std::string command;

	/**
	 ** 	if client message is " CAP LS 302 " then:
	 ** 		command = CAP
	 ** 		commandMessage = LS 302
	 **/
	// get the command name only.
	std::getline(iss, command, ' ');
	// get the command name and the message
	std::getline(iss, commandMessage, '\n');

	if (command == "JOIN") {
		std::string channelName = commandMessage;
		join(clientSocket, channelName);
	}
	exit(0);
}

/*------------------------------------------------------------------------*/