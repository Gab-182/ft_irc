#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class ModeCommand : public ICommands {
	public:
		ModeCommand();
		~ModeCommand();
		bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command);
		void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command);
		void TopicMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command,std::string channelName);
		void InviteOnlyMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command, std::string channelName);
		void LimitMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command, std::string channelName);
		void PasswordMode(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command, std::string channelName);

	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //MODECOMMAND_HPP
