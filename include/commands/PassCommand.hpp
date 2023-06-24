#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class PassCommand : public ICommands {
		public:
			PassCommand();
			~PassCommand();
			void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //PASSCOMMAND_HPP
