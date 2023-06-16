#include "../../include/commands/ICommands.hpp"
using namespace IRC;

ICommands::ICommands() : _command(), _parameters() { }

ICommands::~ICommands() {
	if (!this->_parameters.empty())
		this->_parameters.clear();
}

void ICommands::getCommandInfo(const int& clientSocket, const std::string& clientMessage) {
	(void)clientSocket;
	std::string messageLine, command, parameter;
	std::istringstream messageStream(clientMessage);

	messageStream >> command;
	this->_command = command;
	while (messageStream >> parameter) {
		this->_parameters.push_back(parameter);
	}


//	// Printing the command info
//	std::cout << BOLDGREEN << "Command: " << BOLDYELLOW << this->_command << std::endl;
//
//	std::cout << BOLDGREEN << "Parameters: " << std::endl;
//
//	std::vector<std::string>::iterator it;
//	for(it = this->_parameters.begin(); it != this->_parameters.end(); it++) {
//		std::cout << '\t' << BOLDWHITE << *it << RESET << std::endl;
//	}

	// destroy the vector
	this->_parameters.clear();
}