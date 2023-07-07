#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class PassCommand : public ICommands {
		private:
			std::string clientPass;
		public:
			PassCommand();
			~PassCommand();
			void setClientPass(const std::string& pass);
			std::string getClientPass() const;

			bool noErrorsExist(ICommands* base, const int& clientSocket, Server* server, const std::string& command) const;
			void executeCommand(ICommands* base, const int& clientSocket, Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //PASSCOMMAND_HPP
