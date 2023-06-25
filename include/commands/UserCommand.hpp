#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class UserCommand : public ICommands {
		private:
			void generateUserName(int clientSocket, Server* server);
			bool validUserName(int clientSocket, std::string& userName, Server* server);

		public:
			UserCommand();
			~UserCommand();
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client& client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //USERCOMMAND_HPP
