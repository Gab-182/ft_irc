#ifndef MSGPARSER_HPP
#define MSGPARSER_HPP

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
#include <cstring>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <sys/socket.h>

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
#define BOLDWHITE		"\033[1m\033[37m"		/* Bold White */
#define RESET			"\033[0m"				/* Reset the color */
#define BOLDGREEN		"\033[1m\033[32m"		/* Bold Green */
#define BOLDYELLOW		"\033[1m\033[33m"		/* Bold Yellow */
#define BOLDRED			"\033[1m\033[31m"		/* Bold Red */
#define BOLDBLUE			"\033[1m\033[34m"		/* Bold Blue */
#define BOLDMAGENTA		"\033[1m\033[35m"		/* Bold Magenta */
#define BOLDCYAN			"\033[1m\033[36m"		/* Bold Cyan */

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
#define DEBUG 1

#if( DEBUG == 1 )
#define DEBUG_MSG(msg) std::cout												\
						<< BOLDMAGENTA										\
						<< "———————————————————————[⤵️]—————————————————————"\
						<< std::endl										\
						<< BOLDCYAN << msg << RESET							\
						<< std::endl										\
						<< BOLDMAGENTA										\
						<< "———————————————————————[⤴️]—————————————————————"\
						<< RESET << std::endl;
#elif( DEBUG == 0 )
#define DEBUG_MSG(msg)

#endif
/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/

namespace IRC {
	class MsgParser {
		private:
			std::string generateGuestNick();
			bool duplicatedClient(const std::string& nickname);
			int checkPass(int clientSocket, const std::string& clientPass, const int& serverPass);
			int checkNick(int clientSocket, const std::string& clientNick);
			void checkName(int clientSocket, const std::string& clientName, const std::string& clientRealName);
			/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
		public:
			std::map<int, std::string> clientsNicks;
			std::set<std::string> sentMessages;  // Track sent messages
			std::map<int, std::pair<std::string, std::string> > clientsData;
		public:
			MsgParser();
			~MsgParser();
			MsgParser(const MsgParser &other);
//			MsgParser &operator=(const MsgParser &other);
			/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
			void welcomeMessage(int clientSocket);
			void sendResponse(int clientSocket, const std::string& message);
			void processHandShake(int clientSocket, const std::string& clintsMessage, const int& serverPass);
			/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
	};
}
/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/

#endif