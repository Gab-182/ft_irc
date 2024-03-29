#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class NickCommand : public ICommands {
		private:
			static bool isDuplicatedNick(const int& clientSocket, const std::string& nickName, Server* server);
			static void generateNickName(int clientSocket, Server* server);
			static bool validNickName(int clientSocket, std::string& clientNick, Server* server);
			static bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command);
			static void processNickCommand(const int& clientSocket, std::string& clientNick, Server* server);

		public:
			NickCommand();
			~NickCommand();
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //NICKCOMMAND_HPP
