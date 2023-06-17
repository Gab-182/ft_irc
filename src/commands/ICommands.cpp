#include "../../include/commands/ICommands.hpp"
using namespace IRC;

/*----------------------------------------------------------------------------------------------*/
ICommands::ICommands() : _command(), _parameters() {}

/*----------------------------------------------------------------------------------------------*/
ICommands::~ICommands() {
	if (!this->_parameters.empty())
		this->_parameters.clear();
}

/*----------------------------------------------------------------------------------------------*/
void ICommands::getCommandInfo(const int& clientSocket, const std::string& clientMessage) {
	(void)clientSocket;
	std::string messageLine, command, parameter;
	std::istringstream messageStream(clientMessage);

	messageStream >> command;
	this->_command = command;
	while (messageStream >> parameter) {
		this->_parameters.push_back(parameter);
	}

	std::vector<std::string>::iterator it;
	for(it = this->_parameters.begin(); it != this->_parameters.end(); it++) {
		std::cout << '\t' << BOLDWHITE << *it << RESET << std::endl;
	}

	this->_parameters.clear();
}

/*----------------------------------------------------------------------------------------------*/
//void ICommands::executeCommand(const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels) {
//	(void)clientSocket;
//	(void)clients;
//	(void)channels;
//	std::cout << BOLDRED << "This is the ICommands executeCommand function called" << RESET << std::endl;
//}

/*----------------------------------------------------------------------------------------------*/
void ICommands::executeCommand() {
	std::cout << BOLDRED << "This is the ICommands executeCommand function called" << RESET << std::endl;
}

/*----------------------------------------------------------------------------------------------*/
std::string ICommands::getCommandName() const {
	return this->_command;
}

/*----------------------------------------------------------------------------------------------*/
std::vector<std::string> ICommands::getCommandParameters() const {
	return this->_parameters;
}

/*----------------------------------------------------------------------------------------------*/