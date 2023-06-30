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
namespace IRC {
	class Channel {
		private:
			std::string _name;
			std::string _topic;
			std::string _key;
			std::string _mode;
			/*----------------------------------------------*/
			std::vector<Client*> _members;
			std::vector<Client*> _operators;
			std::vector<Client*> _banedUsers;
			std::vector<Client*> _invites;
			size_t _maxUsers;
//			std::vector<std::string> messages;
		/*---------------------------------------------------------------------------------------------*/
		public:
			Channel();
			Channel(const std::string& name, Client* creator);
			~Channel();
		public:
			void addClientToChannel(Client* user);
			void removeClientFromChannel(Client* user);
			void addOperator(Client* user);
			void removeOperator(Client* user);
			void banUser(Client* user);
			void unbanUser(Client* user);
			void inviteUser(Client* user);
			void removeInvitee(Client* user);

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
