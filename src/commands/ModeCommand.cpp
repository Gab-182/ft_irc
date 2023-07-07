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

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
ModeCommand::ModeCommand() : ICommands() { }

ModeCommand::~ModeCommand() { }

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
bool ModeCommand::noErrorsExist(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	(void) client;

	// MODE <channel name> <mode>
	if (base->getParameters(command).size() < 2) {
		DEBUG_MSG(BOLDRED << " wrong parameters!! ")

		std::string authErrMsg = BOLDRED "Please make sure you entered: "
								 BOLDYELLOW "MODE "
								 BOLDWHITE "<channel_name> <mode> "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

	else if (!Client::isClientAuthenticated(clientSocket, server)) {
		DEBUG_MSG(BOLDRED << " client not authenticated yet!! ")

		std::string authErrMsg = BOLDRED "Please make sure you entered: "
								 BOLDWHITE "[PassWord] "
								 BOLDRED "correctly!!" RESET "\r\n";
		sendResponse(clientSocket, authErrMsg);
		return (false);
	}

//	// check if client is in channel and is channel operator
//	else if (!server->isClientInChannel(client.getNickname(), base->getParameters(command)[0])) {
//		DEBUG_MSG(BOLDRED << " client not in channel!! ")
//
//		std::string authErrMsg = BOLDRED "Please make sure you entered: "
//								 BOLDWHITE "[Channel Name] "
//								 BOLDRED "correctly!!" RESET "\r\n";
//		sendResponse(clientSocket, authErrMsg);
//		return (false);
//	}
//
//	else if (!server->isClientChannelOperator(client.getNickname(), base->getParameters(command)[0])) {
//		DEBUG_MSG(BOLDRED << " client not channel operator!! ")
//
//		std::string authErrMsg = BOLDRED "Please make sure you entered: "
//								 BOLDWHITE "[Channel Operator] "
//								 BOLDRED "correctly!!" RESET "\r\n";
//		sendResponse(clientSocket, authErrMsg);
//		return (false);
//	}

	return (true);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void ModeCommand::executeCommand(ICommands* base, const int& clientSocket, IRC::Server* server, Client* client, const std::string& command) {
	if (!noErrorsExist(base, clientSocket, server, client, command))
		return ;

	std::string channelName = base->getParameters(command)[0];
	std::string mode = base->getParameters(command)[1];
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/