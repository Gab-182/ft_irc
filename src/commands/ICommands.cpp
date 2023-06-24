#include "../../include/commands/ICommands.hpp"

// For the forward declaration of the classes
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

// The commands
#include "../../include/commands/JoinCommand.hpp"
#include "../../include/commands/NickCommand.hpp"
#include "../../include/commands/UserCommand.hpp"
#include "../../include/commands/WhoisCommand.hpp"
#include "../../include/commands/ModeCommand.hpp"
#include "../../include/commands/PassCommand.hpp"
#include "../../include/commands/PingCommand.hpp"
#include "../../include/commands/CapCommand.hpp"


using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::debugCommands() {
	std::cout << BOLDYELLOW << "Command parameters: " << RESET << std::endl;
	std::vector<std::string>::iterator it;
	for(it = this->_parameters.begin(); it != this->_parameters.end(); it++) {
		std::cout << BOLDWHITE << *it << RESET << std::endl;
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ICommands::ICommands() : _command(), _parameters(), _commandsMap() {}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ICommands::~ICommands() {
	std::cout << BOLDRED << "ICommands destructor called" << RESET << std::endl;

	if (!this->_parameters.empty())
		this->_parameters.clear();
	if (!this->_commandsMap.empty())
		this->_commandsMap.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::string ICommands::getCommand() {
	return this->_command;
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::vector<std::string> ICommands::getParameters() {
	return this->_parameters;
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::sendResponse(int clientSocket, const std::string& message) {
	if (send(clientSocket, message.c_str(), message.size(), 0) == -1)
		DEBUG_MSG("Failed to send message to the client: " << message)
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::welcomeMessage(int clientSocket, Server* server) {
	std::string welcomeMsg = ":"
							 + server->serverClientsMap[clientSocket]->getNickName()
							 + " 001 :Welcome to the Internet Relay Network\r\n";
	sendResponse(clientSocket, welcomeMsg);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::string ICommands::toLowerCase(const std::string& str) {
	std::string lowerCaseStr = str;
	std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(), ::tolower);
	return (lowerCaseStr);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::getCommandInfo(const int& clientSocket, const std::string& clientMessage) {
	(void)clientSocket;

	std::string messageLine, parameter;
	std::istringstream messageStream(clientMessage);

	while (std::getline(messageStream, messageLine)) {
		std::istringstream lineStream(messageLine);
		lineStream >> this->_command;
		if (_parameters.size() > 0)
			this->_parameters.clear();
		while (lineStream >> parameter)
			this->_parameters.push_back(parameter);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
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
	_commandsMap["join"] = new IRC::JoinCommand();
	_commandsMap["nick"] = new IRC::NickCommand();
	_commandsMap["user"] = new IRC::UserCommand();
	_commandsMap["whois"] = new IRC::WhoisCommand();
	_commandsMap["mode"] = new IRC::ModeCommand();
	_commandsMap["pass"] = new IRC::PassCommand();
	_commandsMap["ping"] = new IRC::PingCommand();
	_commandsMap["cap"] = new IRC::CapCommand();

}

void ICommands::unRegisterCommands() {
	delete (_commandsMap["join"]);
	delete (_commandsMap["nick"]);
	delete (_commandsMap["user"]);
	delete (_commandsMap["whois"]);
	delete (_commandsMap["mode"]);
	delete (_commandsMap["pass"]);
	delete (_commandsMap["ping"]);
	delete (_commandsMap["cap"]);
	_commandsMap.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client& client) {
	(void)base;

	if (toLowerCase(_command) == "join") {
		_commandsMap["join"]->executeCommand(this, clientSocket, server, client);
	}
	else if (toLowerCase(_command) == "nick") {
		_commandsMap["nick"]->executeCommand(this, clientSocket, server, client);
	}
	else if (toLowerCase(_command) == "user") {
		_commandsMap["user"]->executeCommand(this, clientSocket, server, client);
	}
	else if (toLowerCase(_command) == "whois") {
		_commandsMap["whois"]->executeCommand(this, clientSocket, server, client);
	}
	else if (toLowerCase(_command) == "mode") {
		_commandsMap["mode"]->executeCommand(this, clientSocket, server, client);
	}
	else if (toLowerCase(_command) == "pass") {
		_commandsMap["pass"]->executeCommand(this, clientSocket, server, client);
	}
	else if (toLowerCase(_command) == "ping") {
		_commandsMap["ping"]->executeCommand(this, clientSocket, server, client);
	}
	else if (toLowerCase(_command) == "cap") {
		_commandsMap["cap"]->executeCommand(this, clientSocket, server, client);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
