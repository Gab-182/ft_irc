#include "../../include/commands/ICommands.hpp"
using namespace IRC;

ICommands::ICommands() : _command(), _parameters() { }

ICommands::~ICommands() { }

void ICommands::getCommand(const int& clientSocket, const std::string clientMessage) {
	std::string messageLine, command, parameter;
	std::istringstream messageStream(clientMessage);

	messageStream >> command;
	std::getline(messageStream, parameter);

	std::cout << "socket: " << clientSocket << std::endl;
	std::cout << "command: " << command << std::endl;
	std::cout << "parameter: " << parameter << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
}