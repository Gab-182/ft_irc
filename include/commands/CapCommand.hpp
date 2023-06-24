#ifndef CAPCOMMAND_HPP
#define CAPCOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class CapCommand : public ICommands {
		public:
			CapCommand();
			~CapCommand();
			void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //CAPCOMMAND_HPP
