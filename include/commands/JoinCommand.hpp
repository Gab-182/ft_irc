#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include <sys/socket.h>
#include "../Client.hpp"
#include "ICommands.hpp"

namespace IRC {
	class JoinCommand : public ICommands {
		public:
			JoinCommand();
			~JoinCommand();
			void executeCommand(ICommands* base, const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels);
		};
}


#endif //JOIN
