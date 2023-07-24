#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class TopicCommand : public ICommands {
		public:
			TopicCommand();
			~TopicCommand();
			// void partOperatorClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName);
			// static void partMemberClient(const int& clientSocket, Server* server, Client* client, const std::string& channelName);
			// static bool noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, const std::string& command);
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif // PartCommand
