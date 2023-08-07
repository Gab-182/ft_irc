#ifndef SERVER_HPP
#define SERVER_HPP

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <bitset>
# include <map>
#include <vector>
#include <algorithm>

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "./Channel.hpp"

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
// Forward declaration of the HandShake class

namespace IRC
{
	// Forward declarations:
	class HandShake;
	class ICommands;
	class Client;

	class Server {
		/*-----------------------------------------------------------------*/
		private:
			int port;
			std::string servpass;
			std::vector <int> sockets;
			int master_socket;
			int client_socket;
			std::vector <std::string> msg;

		public:
			Server();
			~Server();
		/*-----------------------------------------------------------------*/
			// map of the all the clients on the server:
			//	key: client socket
			//	value: pointer to the client object.
			std::map<int, Client*> serverClientsMap;

			// map of the all the channels on the server:
			//	key: channel name
			//	value: pointer to the channel object.
			std::map<std::string, Channel*> serverChannelsMap;
		/*-----------------------------------------------------------------*/
			void setMasterSocket(int socket);
			void setServPass(std::string pass);
			int getMasterSocket() const;
			std::string getServPass() const;
			int getPort() const;

		/*-----------------------------------------------------------------*/

			int getClients(std::string nickName);
			void printClients();
			void printChannels();
			int getClientSocket(std::string nickName);
		/*-----------------------------------------------------------------*/
			void create_socket(char *av);
			void respondToClient(const int& clientSocket, Client* client, std::string& clientMsg, ICommands* commands);
			void multi_connection(IRC::ICommands* commands);
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/

#endif