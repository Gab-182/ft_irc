#ifndef CHANNEL_HPP
#define CHANNEL_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#define BOLDWHITE		"\033[1m\033[37m"		/* Bold White */
#define RESET			"\033[0m"				/* Reset the color */
#define BOLDGREEN		"\033[1m\033[32m"		/* Bold Green */
#define BOLDYELLOW		"\033[1m\033[33m"		/* Bold Yellow */
#define BOLDRED			"\033[1m\033[31m"		/* Bold Red */
#define BOLDBLUE		"\033[1m\033[34m"		/* Bold Blue */
#define BOLDMAGENTA		"\033[1m\033[35m"		/* Bold Magenta */
#define BOLDCYAN		"\033[1m\033[36m"		/* Bold Cyan */

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include <cstring>
#include <ostream>
#include <vector>
#include "Client.hpp"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#define ERR_USERONCHANNEL "443" // ERR_USERONCHANNEL "<user/operator> <channel> :is already on channel"
#define ERR_BANNEDFROMCHAN "474" // ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)", banned from channel
#define ERR_BADCHANNELKEY "475" // ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)", bad channel key
#define ERR_INVITEONLYCHAN "473" // ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)", channel is invite only
#define ERR_CHANNELISFULL "471" // ERR_CHANNELISFULL "<channel> :Cannot join channel (+l)", channel is full
#define ERR_NOPRIVILEGES "481" // ERR_NOPRIVILEGES ":Permission Denied-You're not an IRC operator"
#define RPL_INVITING "341" // RPL_INVITING "<channel> <nick>"
#define ERR_CHANOPRIVSNEEDED "482" // ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class Channel {
		// Forward declarations:
		class Server;

		private:
			std::string _name;
			std::string _topic;
			std::string _key;
			std::vector<char> _modes;
			/*----------------------------------------------*/
			/**
			 * @brief ➤ The normal members of the channel.
			 */
			std::vector<Client*> _members;
			/**
			 * @brief ➤ The operators of the channel.
			 */
			std::vector<Client*> _operators;
			/**
			 * @brief ➤ The nicknames of baned users from the channel.
			 */
			std::vector<std::string> _banedUsers;
			/**
			 * @brief ➤ The nicknames of invited users to the channel.
			 */
			std::vector<std::string> _invites;
			/**
			 * @brief ➤ The max users that can be in the channel.
			 */
			size_t _maxUsers;
		/*---------------------------------------------------------------------------------------------*/
		public:
			Channel();
			/**-----------------------------------------------------------------------------------------
			 * @brief ➤ Construct a new Channel object with the given name.
			 * @param name ➤ The name of the channel.
			 */
			Channel(const std::string& name);
			~Channel();
		public:

			/**-----------------------------------------------------------------------------------------
			 * * @brief ➤ returns/gets all the client nicknames in the channel.
			 * 
			 */
			std::string getAllClients(std::string nickName);

			/**-----------------------------------------------------------------------------------------
			 * * @brief ➤ returns/gets all the client nicknames in the channel.
			 * 
			 */
			std::vector<std::string> getAllClients2(std::string nickName);

			/**-----------------------------------------------------------------------------------------
			 * * @brief ➤ returns/gets the target client FD.
			 * 
			 */
			int getTargetClientFD(std::string nickName);

			/**-----------------------------------------------------------------------------------------
			 * * @brief ➤ send messages to all clients on the channel.
			 * @commandName = the name type of command you want to send
			 * @nickName = the client nickname
			 * @param msg = msg to be sent to all clients
			 */
			void sendToAllClients(std::string commandName, std::string nickName,std::string msg);

			/**-----------------------------------------------------------------------------------------
			 * @brief ➤  Check if the joining the channel required a key.
			 * @return true ➤ if the channel required a key.
			 * @return false ➤ if the channel did not require a key.
			 */
			bool isChannelProtected() const;
			/**-----------------------------------------------------------------------------------------
			 * @brief ➤ Check if the channel is invite only.
			 * @return true ➤ if the channel is invite only.
			 * @return false ➤ if the channel is not invite only.
			 */
			bool isChannelInviteOnly() const;
			/**-----------------------------------------------------------------------------------------
			 * @brief ➤ If the channel is empty then delete it.
			 ** @param server ➤ pointer to the server.
			 * @return
			 */
			void ifChannelIsEmptyThenDeleteIt(IRC::Server* server);

			/**-----------------------------------------------------------------------------------------
			 * @brief ➤ Check if the channel is full.
			 * @return true ➤ if the channel is full.
			 * @return false ➤ if the channel is not full.
			 */
			bool isChannelFull() const;

			/**-----------------------------------------------------------------------------------------
			 * @brief ➤ Check if the client is already in the channel.
			 * @param client ➤ pointer to the client to check if it's in the channel.
			 * @return true ➤ if the client is not the channel.
			 * @return false ➤ if the client is in the channel.
			 */
			bool isValidToAddToChannel(Client* client);

			/**-----------------------------------------------------------------------------------------
			** @brief ➤ Add a normal client to the _members vector if it's not already in it.
			** @param client ➤ pointer to the client to add to the channel.
			**/
			void addMemberToChannel(Client* client);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from all the vectors of the channel.
			 ** @param client ➤ pointer to the client to remove from the channel.
			 ** @param server ➤ pointer to the server.
			 **/
			void removeMemberFromChannel(Client* client, IRC::Server* server);

			/**-----------------------------------------------------------------------------------------
			 ** @brief Add the operator client to the operators vector if it's not already in it.
			 ** @param client ➤ pointer to the operator client to add to the channel.
			 **/
			void addOperatorToChannel(Client* client);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from the operators vector if it's in it.
			 ** @param client ➤ pointer to the operator client to remove from the channel.
			 ** @param server ➤ pointer to the server.
			 **/
			void removeOperatorFromChannel(Client* client, IRC::Server* server);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Ban members from the channel.
			 ** @param client ➤ pointer to the member client to ban from the channel.
			 ** @param server ➤ pointer to the server.
			 **/
			void banMemberFromChannel(Client* client, IRC::Server* server);
			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Add the client to the baned users vector if it's not already in it.
			 ** only the operators can ban users from the channel.
			 ** the channel is not removed from the client's channels vector.
			 ** @param operatorClient ➤ pointer to the operator client who banned the client.
			 ** @param clientToBan ➤ pointer to the client to ban from the channel.
			 ** @param server ➤ pointer to the server.
			 **/
			void banUserFromChannel(Client* operatorClient, Client* clientToBan, IRC::Server* server);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from the baned users vector if it's in it.
			 ** @param client ➤ pointer to the client to unban from the channel.
			 **/
			void unbanUserFromChannel(Client* client);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Add the client to the invites vector if it's not already in it.
			 ** @param operatorClient ➤ pointer to the operator client who invited the client.
			 ** @param clientToInvite ➤ pointer to the client to invite to the channel.
			 **/
			void inviteUserToChannel(Client* operatorClient, Client* clientToInvite);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from the invites vector if it's in it.
			 ** @param client ➤ pointer to the client to remove from the invites vector.
			 **/
			void removeInviteeFromChannel(Client* client, IRC::Server* server);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from the channel completely.
			 ** @param client ➤ pointer to the client to remove from the channel.
			 ** @param server ➤ pointer to the server.
			 **/
			void removeClientFromChannel(Client* client, IRC::Server* server);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ checks if client is in channel
			 ** @param nickName ➤ nickname of the client.
			 ** @returns int.
			 **/
			int isClientinChannel(std::string nickName);

			/*------------  SETTERS && GETTERS  ----------------*/
			void setName(const std::string& name);
			void setTopic(const std::string& topic);
			void setKey(const std::string& key);
			void setMaxUsers(const size_t& maxUsers);
			void addMode(const char& mode);

			std::string getChannelName();
			std::string getTopic();
			std::vector<char> getModes();
			std::string getKey();
			size_t getMaxUsers() const;
			size_t getChannelUsersNumber() const;

			bool isClientMember(Client* client);
			bool isClientOperator(Client* client);
			bool isClientInvited(Client* client);
			bool isClientBaned(Client* client);

			/*----------------------------------------------*/
			std::vector<Client*> getNormalClients();
			std::vector<Client*> getOperators();
			std::vector<std::string> getBanedUsers();
			std::vector<std::string> getInvites();

			/*----------------------------------------------*/
			void printChannelInfo();
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/

#endif
