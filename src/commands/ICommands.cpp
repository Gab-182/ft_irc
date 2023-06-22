#include "../../include/commands/ICommands.hpp"
#include "../../include/Server.hpp"

#include "../../include/commands/JoinCommand.hpp"
#include "../../include/commands/NickCommand.hpp"
using namespace IRC;

/*----------------------------------------------------------------------------------------------*/
void ICommands::debugCommands() {
	std::cout << BOLDGREEN << "Command name: " << RESET << this->_command << std::endl;
	std::cout << BOLDGREEN << "Command parameters: " << RESET << std::endl;
	std::vector<std::string>::iterator it;
	for(it = this->_parameters.begin(); it != this->_parameters.end(); it++) {
		std::cout << BOLDWHITE << *it << RESET << std::endl;
	}
}

/*----------------------------------------------------------------------------------------------*/
ICommands::ICommands() : _command(), _parameters(), _commandsMap() {}

/*----------------------------------------------------------------------------------------------*/
ICommands::~ICommands() {
	std::cout << BOLDRED << "ICommands destructor called" << RESET << std::endl;

	if (!this->_parameters.empty())
		this->_parameters.clear();
	if (!this->_commandsMap.empty())
		this->_commandsMap.clear();
}

/*----------------------------------------------------------------------------------------------*/
std::string ICommands::getCommand() {
	return this->_command;
}

/*----------------------------------------------------------------------------------------------*/
std::vector<std::string> ICommands::getParameters() {
	return this->_parameters;
}

/*----------------------------------------------------------------------------------------------*/
void ICommands::sendResponse(int clientSocket, const std::string& message) {
	if (send(clientSocket, message.c_str(), message.size(), 0) == -1)
		DEBUG_MSG("Failed to send message to the client: " << message)
}

/*----------------------------------------------------------------------------------------------*/
void ICommands::getCommandInfo(const int& clientSocket, const std::string& clientMessage) {
	(void)clientSocket;
	std::string messageLine, command, parameter;
	std::istringstream messageStream(clientMessage);

	messageStream >> command;
	this->_command = command;

	// Cleaning the parameters vector before adding new ones to it.
	if (_parameters.size() > 0)
		this->_parameters.clear();
	while (messageStream >> parameter) {
		this->_parameters.push_back(parameter);
	}
}

/*------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Register all commands in a map, so we can use them later
 * register them by doing:
 * commands[key] = new <Command class>;
 * key is the command name, and the value is the command class
 *
 * @param commands map of commands to register
 * @return void
 */
void ICommands::registerCommands() {
	_commandsMap["JOIN"] = new IRC::JoinCommand();
	_commandsMap["NICK"] = new IRC::NickCommand();
}

/*----------------------------------------------------------------------------------------------*/
void ICommands::executeCommand(ICommands* base, const int& clientSocket, Server* server) {
	(void)clientSocket;
	(void)base;
	(void)server;

if (_command == "JOIN") {
		_commandsMap["JOIN"]->executeCommand(this, clientSocket, server);
	} else if (_command == "NICK") {
		_commandsMap["NICK"]->executeCommand(this, clientSocket, server);
	}

//	else {
//		std::cout << BOLDRED << "Command not found" << RESET << std::endl;
//	}
}

/*----------------------------------------------------------------------------------------------*/