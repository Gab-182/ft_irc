#ifndef HANDSHAKE_HPP
#define HANDSHAKE_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <sys/socket.h>
#include <fstream>

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
// Forward declaration of the server class

namespace IRC {
	// Forward declarations:
	class Server;
	class Client;

	class HandShake {
		public:
			std::map<int, std::set<std::string> > _sentMessages;  // Track sent messages

		private:
			bool processPassMessage(int clientSocket, const std::string& clientPass, Server* server);
			void processModeMessage(int clientSocket, std::istringstream& lineStream, Server* server);

			void sendResponse(int clientSocket, const std::string& message);
			void welcomeMessage(int clientSocket, Server* server);
			static std::string toLowerCase(const std::string& str);

		public:
			HandShake();
			~HandShake();
			int processHandShake(int clientSocket, std::string& clientsMessage, Server* server);
			void removeClient(int clientSocket, IRC::Server* server);
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/

#endif