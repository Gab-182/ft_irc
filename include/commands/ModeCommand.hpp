#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class ModeCommand : public ICommands {
	public:
		ModeCommand();
		~ModeCommand();
		void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //MODECOMMAND_HPP
