#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class ModeCommand : public ICommands {
	public:
		ModeCommand();
		~ModeCommand();
		bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client, const std::string& command);
		void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //MODECOMMAND_HPP
