#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class NickCommand : public ICommands {
		private:
			bool isDuplicatedNick(const int& clientSocket, const std::string& nickName, Server* server);
			void generateNickName(int clientSocket, Server* server);
			bool validNickName(int clientSocket, std::string& clientNick, Server* server);

		public:
			NickCommand();
			~NickCommand();
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client& client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //NICKCOMMAND_HPP
