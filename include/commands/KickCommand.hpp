#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class KickCommand : public ICommands {
		public:
			KickCommand();
			~KickCommand();
			static void KickMemberClient(const int& clientSocket, Server* server, const std::string& channelName, const std::string& targetUser, const std::string& reason);
			static bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command);
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif // KickCommand
