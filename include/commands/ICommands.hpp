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
		protected:
			std::string _command;
			std::vector<std::string> _parameters;
		/*-----------------------------------------------------------------------*/
		public:
			std::map<std::string, IRC::ICommands*> _commandsMap;
		/*-----------------------------------------------------------------------*/
		public:
			ICommands();
			virtual ~ICommands();
			void debugCommands();
			std::string getCommand();
			std::vector<std::string> getParameters();

			void registerCommands();
			void sendResponse(int clientSocket, const std::string& message);
			static std::string toLowerCase(const std::string& str);
			void getCommandInfo(const int& clientSocket, const std::string& clientMessage);
			virtual void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client& client);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //ICOMMANDS_HPP
