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
			void debugCommands();
			std::vector<std::string> getParameters(std::string command);

			void registerCommands();
			void unRegisterCommands();
			static void welcomeMessage(int clientSocket, Server* server);
			static void sendResponse(int clientSocket, const std::string& message);
			static std::string toLowerCase(const std::string& str);
			void getCommandInfo(const int& clientSocket, const std::string& clientMessage);
			virtual void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //ICOMMANDS_HPP
