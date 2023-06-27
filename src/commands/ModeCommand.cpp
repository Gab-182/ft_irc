#include "../../include/commands/ModeCommand.hpp"
#include "../../include/Client.hpp"
#include "../../include/Server.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
/*** ——————————————————————-----------------------------------———————————————————————
 *** [ +i ]
 ***  Set/Remove Invite-only Channel:
 ***	# Client sends: MODE #channel +i
 ***	# Server responds: :server.name 324 yourNick #channel +i
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +t ]
 *** Set/Remove TOPIC Command Restrictions (+t):
 *** 	# Client sends: MODE #channel +t
 ***	# Server responds: :server.name 324 yourNick #channel +t
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +k ]
 *** Set/Remove Channel Key (Password) (+k):
 ***	# Client sends: MODE #channel +k password
 ***	# Server responds: :server.name 324 yourNick #channel +k password
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +o ]
 *** Give/Take Channel Operator Privilege (+o):
 ***	# Client sends: MODE #channel +o user
 ***	# Server responds: :server.name 381 yourNick #channel :You are now an operator
 *** ——————————————————————-----------------------------------———————————————————————
 *** [ +l ]
 *** Set/Remove User Limit to Channel (+l):
 ***	# Client sends: MODE #channel +l limit
 ***	# Server responds: :server.name 324 yourNick #channel +l limit
 *** ——————————————————————-----------------------------------———————————————————————
 ***/

/**
 ** at eh beginning the irssi client will send:
 **
 ** MODE Welcome to the Internet Relay Network +i
 **
 ** if (base->getParameters(command).back() == "+i") {
 ** 		std::string modMsg = "MODE "
 ** 							 + server->serverClientsMap[clientSocket]->getNickName()
 ** 							 + " +i\r\n";
 ** 		sendResponse(clientSocket, modMsg);
 ** }
 **
 **/
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ModeCommand::ModeCommand() : ICommands() { }

ModeCommand::~ModeCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ModeCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client& client, const std::string& command) {
	(void) client;

	// MODE <channel name> <mode>
	if (base->getParameters(command).size() == 2) {
		std::string channelName = base->getParameters(command)[0];
		std::string mode = base->getParameters(command)[1];

		// Check if the channel exist,
		// check if the user is operator in that channel,
		// if so apply the mode

		// Check if the client has already entered a correct password before.
		if (Client::isClientAuthenticated(clientSocket, server)) {

		}


//		Client not authenticated exception
//		if (!Client::isClientAuthenticated(clientSocket, server))

		// [not authenticated] error
		else {
			DEBUG_MSG(BOLDRED << " client not authenticated yet!! ")

			std::string authErrMsg = BOLDRED "Please make sure you entered: "
									 BOLDWHITE "[PassWord] "
									 BOLDRED "correctly!!" RESET "\r\n";
			sendResponse(clientSocket, authErrMsg);
		}
	}

//	wrong mode parameters exception
//	if (base->getParameters(command).size() != 2)

	// [MODE parameters] error
	else {
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string authErrMsg = BOLDRED "Please make sure you entered: "
								 BOLDYELLOW "MODE "
								 BOLDWHITE "<channel_name> <mode> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/