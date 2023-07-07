#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class QuitCommand : public ICommands {
		public:
			QuitCommand();
			~QuitCommand();
			static bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command);
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //QUITCOMMAND_HPP
