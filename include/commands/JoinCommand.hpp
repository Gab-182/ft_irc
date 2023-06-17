#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "../Client.hpp"
#include "ICommands.hpp"

namespace IRC {
	class JoinCommand : public ICommands {
		public:
			JoinCommand();
			~JoinCommand();
			void registerCommands();
			void executeCommand(const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels);
		};
}


#endif //JOIN
