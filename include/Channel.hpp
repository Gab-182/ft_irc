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

#define ERR_NOTONCHANNEL "442" // ERR_NOTONCHANNEL "<channel> :You're not on that channel"
#define ERR_NOSUCHCHANNEL "403" // ERR_NOSUCHCHANNEL "<channel> :No such channel"
#define ERR_ALREADYREGISTRED "462" // ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
#define ERR_CHANOPRIVSNEEDED "482" // ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class Channel {
		private:
			std::string _name;
			std::string _topic;
			std::string _key;
			std::string _mode;
			size_t _chennelUsersNumber;
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
			 * @brief ➤ The baned users from the channel.
			 */
			std::vector<Client*> _banedUsers;
			/**
			 * @brief ➤ The users that are invited to the channel.
			 */
			std::vector<Client*> _invites;
			/**
			 * @brief ➤ The max users that can be in the channel.
			 */
			size_t _maxUsers;
//			std::vector<std::string> messages;
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
			 ** @param user ➤ pointer to the client to remove from the channel.
			 **/
			void removeMemberFromChannel(Client* user);

			/**-----------------------------------------------------------------------------------------
			 ** @brief Add the client to the operators vector if it's not already in it.
			 ** and remove it from all the other vectors of the channel.
			 ** @param user ➤ pointer to the operator client to add to the channel.
			 **/
			void addOperatorToChannel(Client* user);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from the operators vector if it's in it.
			 ** @param user ➤ pointer to the operator client to remove from the channel.
			 **/
			void removeChannelOperator(Client* user);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Add the client to the baned users vector if it's not already in it.
			 ** and remove it from all the other vectors of the channel.
			 ** @param user ➤ pointer to the client to ban from the channel.
			 **/
			void banUserFromChannel(Client* user);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from the baned users vector if it's in it.
			 ** @param user ➤ pointer to the client to unban from the channel.
			 **/
			void unbanUserFromChannel(Client* user);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Add the client to the invites vector if it's not already in it.
			 ** @param user ➤ pointer to the client to invite to the channel.
			 **/
			void inviteUserToChannel(Client* user);

			/**-----------------------------------------------------------------------------------------
			 ** @brief ➤ Remove the client from the invites vector if it's in it.
			 ** @param user ➤ pointer to the client to remove from the invites vector.
			 **/
			void removeInviteeFromChannel(Client* user);

			/*------------  SETTERS && GETTERS  ----------------*/
			void setName(const std::string& name);
			void setTopic(const std::string& topic);
			void setKey(const std::string& key);
			void setMode(const std::string& mode);
			void setMaxUsers(const size_t& maxUsers);

			std::string getChannelName();
			std::string getTopic();
			std::string getMode();
			std::string getKey();
			size_t getMaxUsers() const;
			size_t getChannelUsersNumber() const;

			/*----------------------------------------------*/
			std::vector<Client*> getNormalClients();
			std::vector<Client*> getOperators();
			std::vector<Client*> getBanedUsers();
			std::vector<Client*> getInvites();
			/*----------------------------------------------*/
			void printChannelInfo();
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/

#endif
