#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

/*---------------------------------------------------------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include "../Client.hpp"
#include "ICommands.hpp"

/*---------------------------------------------------------------------------------------------------------------------------------*/
/**
 ** Command: JOIN
 ** Parameters: <channel>{,<channel>} [<key>{,<key>}]
 **
 ** Description:
 ** - The JOIN command is used by a user to request to start listening to one or more channels.
 ** - The <channel> parameter specifies the name of the channel(s) to join, separated by commas if joining multiple channels.
 ** - Optionally, the [<key>{,<key>}] parameter can be used to provide a password or key to join password-protected channels.
 ** - If a channel does not exist, it will be created when the first user joins it.
 ** - Once a user has joined a channel, they can receive all messages sent to that channel.
 **
 ** Command Examples:
 ** - JOIN #channel1
 ** - JOIN #channel1,#channel2
 ** - JOIN &privatechannel password
 ** - JOIN #protected,#secret secretkey
 **
 ** Note:
 ** - The JOIN command is typically used after the user has successfully connected to the IRC server and authenticated.
 ** - It allows the user to join channels and participate in conversations with other users in those channels.
 ** - The JOIN command is an essential command in IRC for channel communication and collaboration.
 */

/*---------------------------------------------------------------------------------------------------------------------------------*/
namespace IRC {
	class JoinCommand : public ICommands {
		public:
			JoinCommand();
			~JoinCommand();
			void executeCommand(ICommands* base, const int& clientSocket, const std::vector<Client>& clients, std::vector<Channel>& channels);
		};
}

/*---------------------------------------------------------------------------------------------------------------------------------*/
#endif //JOIN
