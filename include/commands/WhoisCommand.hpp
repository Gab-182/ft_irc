#ifndef WHOISCOMMAND_HPP
#define WHOISCOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class WhoisCommand : public ICommands {
		public:
			WhoisCommand();
			~WhoisCommand();
			void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //WHOISCOMMAND_HPP
