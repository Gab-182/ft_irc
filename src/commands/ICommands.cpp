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
#include "../../include/commands/PrivMsgCommand.hpp"
#include "../../include/commands/PartCommand.hpp"
#include "../../include/commands/KickCommand.hpp"
#include "../../include/commands/TopicCommand.hpp"
#include "../../include/commands/InviteCommand.hpp"

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

	// "<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
	std::string welcomeMsg1 = ":irc 001 " + server->serverClientsMap[clientSocket]->getNickName() + " :Welcome to the perfect Chat system " + server->serverClientsMap[clientSocket]->getNickName() + "!" +  server->serverClientsMap[clientSocket]->getUserName() + "@soso\n";
	sendResponse(clientSocket, welcomeMsg1);
	//":" + servername + " 002 " + nick + " :Your host is " + servername + ", running version " + version + "\n"

	std::string welcomeMsg2 = ":irc 002 " + server->serverClientsMap[clientSocket]->getNickName() + ":Your host is soso\n";
	sendResponse(clientSocket, welcomeMsg2);
	std::string welcomeMsg3 = ":irc 003 " + server->serverClientsMap[clientSocket]->getNickName() + " :Created on july->2023\n";
	sendResponse(clientSocket, welcomeMsg3);
 //":" + servername + " 004 " + nick + " " + servername + " " + version + " " + usermodes + " " + chanmodes + " :" + servername + " server\n"
	std::string welcomeMsg4 = ":irc 004 " + server->serverClientsMap[clientSocket]->getNickName() + " irc 333 i x :irc server\n";
	sendResponse(clientSocket, welcomeMsg4);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::string ICommands::toLowerCase(const std::string& str) {
	std::string lowerCaseStr = str;
	std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(), ::tolower);
	return (lowerCaseStr);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool ICommands::isParameterEmpty(const std::string& command) {
	return (getParameters(command).empty());
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::getCommandInfo(const std::string& clientMessage) {

	std::string messageLine, command, para;
	std::vector<std::string> parameters;
	std::pair<std::string, std::vector<std::string> > pair;

	std::istringstream messageStream(clientMessage);

	while (std::getline(messageStream, messageLine)) {
		std::istringstream lineStream(messageLine);
		lineStream >> command;

		while (lineStream >> para){
			parameters.push_back(para);
		}
			
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
	_commandsMap["part"] = new IRC::PartCommand();
	_commandsMap["privmsg"] = new IRC::PrivMsgCommand();
	_commandsMap["kick"] = new IRC::KickCommand();
	_commandsMap["topic"] = new IRC::TopicCommand();
	_commandsMap["invite"] = new IRC::InviteCommand();
	
}

void ICommands::unRegisterCommands() {
	delete (_commandsMap["join"]);
	delete (_commandsMap["nick"]);
	delete (_commandsMap["user"]);
	delete (_commandsMap["whois"]);
	delete (_commandsMap["mode"]);
	delete (_commandsMap["pass"]);
	delete (_commandsMap["part"]);
	delete (_commandsMap["ping"]);
	delete (_commandsMap["cap"]);
	delete (_commandsMap["quit"]);
	delete (_commandsMap["privmsg"]);
	delete (_commandsMap["kick"]);
	delete (_commandsMap["topic"]);
	delete (_commandsMap["invite"]);
	_commandsMap.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::unknownCommand(int clientSocket,  const std::string& command) {
	std::string response = ":"
							ERR_UNKNOWNCOMMAND " "
							BOLDYELLOW + command
							+ BOLDRED " :Unknown command\n"
							+ BOLDYELLOW "The server only accepts the following commands:\n"
							+ BOLDWHITE "\t NICK <nickname>\n"
							+ BOLDWHITE "\t USER <username>\n"
							+ BOLDWHITE "\t PASS <password>\n"
							+ BOLDWHITE "\t JOIN <#channel_name> <#channel_name> ...\n"
							+ BOLDWHITE "\t PRIVMSG <nickname> <message>\n"
							+ BOLDWHITE "\t TOPIC <channel_name> <topic>\n"
							+ BOLDWHITE "\t PART <channel_name>\n"
							+ BOLDWHITE "\t OPER <username> <password>\n"
							+ BOLDWHITE "\t MODE <channel_name> <mode> <mode parameter>\n"
							+ BOLDWHITE "\t WHOIS <nickname>\n"
							+ BOLDWHITE "\t PING <unique token>\n"
							+ BOLDWHITE "\t CAP LS\n"
							+ BOLDWHITE "\t CAP END\n"
							+ BOLDWHITE "\t QUIT\n"
							+ BOLDYELLOW "Please try again"
							+ RESET "\r\n";
	sendResponse(clientSocket, response);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ICommands::executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command) {
	(void)base;
	(void)command;


	// loop through all the commands in the vector, and pass the command to the execute function.
	// if and else if statements can be changed to the map instead
	//_commandsMap.find(command.toLowercase()).second->excuteCOmmand(this, c,serv, cl, it->first)

	
	std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it;

    std::cout << "InviteCommand::executeCommand" << std::endl;
	
	for (it = _messages.begin(); it != _messages.end(); ++it) {
 		   std::cout << "InviteCommand::executeCommand :3" << std::endl;
		if (toLowerCase(it->first) == "join")
			_commandsMap["join"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "nick")
			_commandsMap["nick"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "user")
			_commandsMap["user"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "whois")
			_commandsMap["whois"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "mode")
			_commandsMap["mode"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "pass")
			_commandsMap["pass"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "ping")
			_commandsMap["ping"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "cap")
			_commandsMap["cap"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "quit")
			_commandsMap["quit"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "privmsg")
			_commandsMap["privmsg"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "part")
			_commandsMap["part"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "topic")
			_commandsMap["topic"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "kick")
			_commandsMap["kick"]->executeCommand(this, clientSocket, server, client, it->first);
		else if (toLowerCase(it->first) == "invite")
		{
			_commandsMap["invite"]->executeCommand(this, clientSocket, server, client, it->first);
		}	
// TODO: implement these commands:
// ====================================================================================================
//		else if (toLowerCase(it->first) == "oper")
//			_commandsMap["oper"]->executeCommand(this, clientSocket, server, client, it->first);

		else
			unknownCommand(clientSocket, it->first);
	}
	_messages.clear();
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
