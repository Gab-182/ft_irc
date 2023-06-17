#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "../Client.hpp"
#include "ICommands.hpp"
#include "ICommands.hpp"

namespace IRC {
	class NickCommand : public ICommands {
		public:
			NickCommand();
			~NickCommand();
			void executeCommand(const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels);
		};
}


#endif //NICKCOMMAND_HPP
