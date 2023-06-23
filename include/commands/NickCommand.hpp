#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class NickCommand : public ICommands {
		public:
			NickCommand();
			~NickCommand();

			bool isDuplicatedNick(const int& clientSocket, const std::string& nickName, Server* server);
			void generateNickName(int clientSocket, Server* server);
			bool validNickName(int clientSocket, std::string& clientNick, Server* server);

			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client& client);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //NICKCOMMAND_HPP
