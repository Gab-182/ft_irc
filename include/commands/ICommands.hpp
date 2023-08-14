#ifndef ICOMMANDS_HPP
#define ICOMMANDS_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#define BOLDWHITE		"\033[1m\033[37m"		/* Bold White */
#define RESET			"\033[0m"				/* Reset the color */
#define BOLDGREEN		"\033[1m\033[32m"		/* Bold Green */
#define BOLDYELLOW		"\033[1m\033[33m"		/* Bold Yellow */
#define BOLDRED			"\033[1m\033[31m"		/* Bold Red */
#define BOLDBLUE		"\033[1m\033[34m"		/* Bold Blue */
#define BOLDMAGENTA		"\033[1m\033[35m"		/* Bold Magenta */
#define BOLDCYAN		"\033[1m\033[36m"		/* Bold Cyan */

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#define DEBUG 1

#if( DEBUG == 1 )
#define DEBUG_MSG(msg) std::cout													\
						<< BOLDMAGENTA												\
						<< "⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚  𝙳𝙴𝙱𝚄𝙶  ⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚⎚"	\
						<< std::endl												\
						<< BOLDCYAN << msg << RESET									\
						<< std::endl;
#elif( DEBUG == 0 )
#define DEBUG_MSG(msg)

#endif

/**
 ** Example of sending a response to the client:
 **
 **		std::string Msg = ":"
 **							" " NUMERIC " "
 **							+ :(MESSAGE)
 **							+ RESET "\r\n";
 **		sendResponse(clientSocket, Msg);
 **/
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
// Pass command replies (see RFC).
#define ERR_PASSWDMISMATCH "464" // Password incorrect.
#define ERR_NEEDMOREPARAMS "461" // Not enough parameters.
#define RPL_UMODEIS(nick, modes) \
": 221 " + nick + " :" + modes + "\r\n"



// Nick command replies (see RFC).
#define ERR_NONICKNAMEGIVEN "431" // No nickname given.
#define ERR_ERRONEUSNICKNAME "432" // Erroneous nickname.
#define ERR_NICKNAMEINUSE "433" // Nickname in use.

// User command replies (see RFC).
#define ERR_NOTREGISTERED "451" // You have not registered.

// Join command replies (see RFC).
#define RPL_YOUREOPER "381" // You are now an IRC operator.

// Mode command replies (see RFC).
#define ERR_UNKNOWNMODE "472" // Unknown mode char.
#define RPL_CHANNELMODEIS "324" // Channel mode is.

// Channel command replies (see RFC).
#define ERR_NOTONCHANNEL "442" // You're not on that channel.
#define ERR_NOSUCHCHANNEL(nick, channel) \
	": 403 " + nick + " " + channel + " :No such channel.\r\n"
#define ERR_CHANOPRIVSNEEDED "482" // You're not channel operator.

//Topic Command
#define RPL_NOTOPIC "331" // No topic is set.
#define RPL_TOPIC "332" // Topic is set.


// user not in channel.
#define ERR_USERNOTINCHANNEL(nick, channel) \
	": 441 * <" + nick + "> isn't on " + channel + "\r\n"
	 
//WHOIS command replies (see RFC).
#define RPL_WHOISUSER "311" // Whois user, <nick> <user> <host> * :<real name>.
#define ERR_NOSUCHNICK(nick) \
	": 401 " + nick + " :No such nick\r\n"
#define RPL_WHOISSERVER "312" // Whois server reply.
#define RPL_ENDOFWHOIS "318" // End of whois reply.
#define RPL_WHOISCHANNELS "319" // list of channels a user is in.

// welcome message
#define RPL_WELCOME "001" // Welcome message.

#define ERR_UNKNOWNCOMMAND "421" // Unknown command.

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	// Forward declaration of the Server class.
	class Server;
	// Forward declaration of the Client class.
	class Client;

	class ICommands {
		/*-----------------------------------------------------------------------*/
		public:
			/**
			 ** The reason to create it: irssi send one message that contain (3, 4 ...)
			 ** commands in one time.
			 *
			 ** vector that contain pair of <command, parameters vector> _messages
			 ** command		-> the command name.
			 ** parameters	-> the parameter vector of that command
			 **/
			 // TODO: Change the _message vector to map.
			std::vector<std::pair<std::string, std::vector<std::string> > > _messages;

			/**
			 ** <command, pointer to function in the commands interface> _commandsMap
			 ** key -> the command name.
			 ** value -> pointer to the execute function in the commands interface class.
			 **/
			std::map<std::string, IRC::ICommands*> _commandsMap;
		/*-----------------------------------------------------------------------*/
		public:
			ICommands();
			virtual ~ICommands();
		/*-----------------------------------------------------------------------*/
			void debugCommands();
			std::vector<std::string> getParameters(std::string command);

		/*-----------------------------------------------------------------------*/
			void registerCommands();
			void unRegisterCommands();

		/*-----------------------------------------------------------------------*/
			static void welcomeMessage(int clientSocket, Server* server);
			static void sendResponse(int clientSocket, const std::string& message);

		/*-----------------------------------------------------------------------*/
			static std::string toLowerCase(const std::string& str);
			bool isParameterEmpty(const std::string& command);

		/*-----------------------------------------------------------------------*/
			void getCommandInfo(const std::string& clientMessage);
			static void unknownCommand(int clientSocket, const std::string& command);
			virtual void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //ICOMMANDS_HPP
