#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class JoinCommand : public ICommands {
		public:
			JoinCommand();
			~JoinCommand();
			static void joinOperatorClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName);
			static void joinMemberClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName);
			static bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command);
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif // JOINCOMMAND_HPP
