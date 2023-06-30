#include "../../include/commands/CapCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
CapCommand::CapCommand() : ICommands() { }

CapCommand::~CapCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void CapCommand::setCapType(const std::string& capType) { this->_capType = capType; }

std::string CapCommand::getCapType() const { return (this->_capType); }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void CapCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	(void) server;
	(void) client;

	if (base->isParameterEmpty(command))
		sendResponse(clientSocket, "CAP * NAK :Missing CAP subcommand\r\n");
	setCapType(base->getParameters(command)[0]);

	if (toLowerCase(getCapType()) == "ls")
		sendResponse(clientSocket, "CAP * ACK :302 CAP LS\r\n");

	else if (toLowerCase(getCapType()) == "end")
		sendResponse(clientSocket, "CAP * ACK :CAP END\r\n");
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/