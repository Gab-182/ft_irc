#ifndef CAPCOMMAND_HPP
#define CAPCOMMAND_HPP

#include "ICommands.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class CapCommand : public ICommands {
		private:
			std::string _capType;
		public:
			CapCommand();
			~CapCommand();
			void setCapType(const std::string& capType);
			std::string getCapType() const;
			void executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command);
	};
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif //CAPCOMMAND_HPP
