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
#include "../../include/commands/QuitCommand.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::debugCommands() {
	std::vector<std::pair<std::string, std::vector<std::string> > >::iterator itMsg;

	for (itMsg = _messages.begin(); itMsg != _messages.end(); ++itMsg) {

		std::cout << BOLDYELLOW << "Command: " << itMsg->first << RESET << std::endl;
		std::cout << BOLDYELLOW << "Command parameters: " << RESET << std::endl;

		std::vector<std::string>::iterator itParam;
		for(itParam = itMsg->second.begin(); itParam != itMsg->second.end(); itParam++) {
			std::cout << BOLDWHITE << *itParam << RESET << std::endl;
		}
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ICommands::ICommands() : _messages(), _commandsMap() {}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ICommands::~ICommands() {
	std::cout << BOLDRED << "ICommands destructor called" << RESET << std::endl;

	if (!this->_messages.empty()) {
		this->_messages.clear();
	}
	if (!this->_commandsMap.empty())
		this->_commandsMap.clear();

	this->unRegisterCommands();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::vector<std::string> ICommands::getParameters(std::string command) {
	std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it;
	for (it = _messages.begin(); it != _messages.end(); ++it) {
		if (it->first == command) {
			return (it->second);
		}
	}
	return (it->second);
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

	std::string messageLine, command, para;
	std::vector<std::string> parameters;
	std::pair<std::string, std::vector<std::string> > pair;

	std::istringstream messageStream(clientMessage);

	while (std::getline(messageStream, messageLine)) {
		std::istringstream lineStream(messageLine);
		lineStream >> command;

		while (lineStream >> para)
			parameters.push_back(para);
		_messages.push_back(std::make_pair(command, parameters));
		parameters.clear();
	}
//	debugCommands();
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
	_commandsMap["quit"] = new IRC::QuitCommand();
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
	delete (_commandsMap["quit"]);
	_commandsMap.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client& client, const std::string& command) {
	(void)base;
	(void)command;


	// loop through all the commands in the vector, and pass the command to the execute function.
	std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it;

	for (it = _messages.begin(); it != _messages.end(); ++it) {
		if (toLowerCase(it->first) == "join") {
			_commandsMap["join"]->executeCommand(this, clientSocket, server, client, it->first);
		} else if (toLowerCase(it->first) == "nick") {
			_commandsMap["nick"]->executeCommand(this, clientSocket, server, client, it->first);
		} else if (toLowerCase(it->first) == "user") {
			_commandsMap["user"]->executeCommand(this, clientSocket, server, client, it->first);
		} else if (toLowerCase(it->first) == "whois") {
			_commandsMap["whois"]->executeCommand(this, clientSocket, server, client, it->first);
		} else if (toLowerCase(it->first) == "mode") {
			_commandsMap["mode"]->executeCommand(this, clientSocket, server, client, it->first);
		} else if (toLowerCase(it->first) == "pass") {
			_commandsMap["pass"]->executeCommand(this, clientSocket, server, client, it->first);
		} else if (toLowerCase(it->first) == "ping") {
			_commandsMap["ping"]->executeCommand(this, clientSocket, server, client, it->first);
		} else if (toLowerCase(it->first) == "cap") {
			_commandsMap["cap"]->executeCommand(this, clientSocket, server, client, it->first);
		}else if (toLowerCase(it->first) == "quit") {
			_commandsMap["quit"]->executeCommand(this, clientSocket, server, client, it->first);
		}
		else
			DEBUG_MSG(BOLDRED "WRONG COMMAND!!!")
	}
	_messages.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
