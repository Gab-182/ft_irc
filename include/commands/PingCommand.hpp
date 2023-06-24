#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class PingCommand : public ICommands {
		public:
			PingCommand();
			~PingCommand();
			void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //PINGCOMMAND_HPP
