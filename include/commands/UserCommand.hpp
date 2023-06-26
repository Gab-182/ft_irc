#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class UserCommand : public ICommands {
		private:
			static void generateUserName(int clientSocket, Server* server);
			static bool validUserName(int clientSocket, std::string& userName, Server* server);
			static void processUserName(const int& clientSocket ,std::string& userName, Server* server);

		public:
			UserCommand();
			~UserCommand();
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client& client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //USERCOMMAND_HPP
