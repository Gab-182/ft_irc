#ifndef INVITECOMMAND_HPP
#define INVITECOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class InviteCommand : public ICommands {
	public:
		InviteCommand();
		~InviteCommand();
		bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command);
		void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //MODECOMMAND_HPP
