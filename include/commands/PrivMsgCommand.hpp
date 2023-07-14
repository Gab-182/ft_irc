
#ifndef PRIVMSGCOMMAND_HPP
#define PRIVMSGCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class PrivMsgCommand : public ICommands {
	private:
		static void generateUserName(int clientSocket, Server* server);
		static bool validUserName(int clientSocket, std::string& userName, Server* server);
		static bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command);
		static void processUserName(const int& clientSocket ,std::string& userName, Server* server);

	public:
		PrivMsgCommand();
		~PrivMsgCommand();
		void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //PrivMsgCommand
