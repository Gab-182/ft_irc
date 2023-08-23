
#ifndef NOTICECOMMAND_HPP
#define NOTICECOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class NoticeCommand : public ICommands {
	private:
		static void generateUserName(int clientSocket, Server* server);
		static bool validUserName(int clientSocket, std::string& userName, Server* server);
		static bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command);
		static void processUserName(const int& clientSocket ,std::string& userName, Server* server);

	public:
		NoticeCommand();
		~NoticeCommand();
		void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //PrivMsgCommand
