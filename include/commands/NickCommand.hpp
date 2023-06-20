#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

//#include "../Client.hpp"
#include "ICommands.hpp"

namespace IRC {
	class NickCommand : public ICommands {
		public:
			NickCommand();
			~NickCommand();
			void registerCommands();
			void executeCommand(ICommands* base, const int& clientSocket, Server* server);

	};
}

#endif //NICKCOMMAND_HPP
