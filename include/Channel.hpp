#ifndef CHANNEL_HPP
#define CHANNEL_HPP

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
			std::vector<Client*> _users;
			std::vector<Client*> _operators;
			std::vector<Client*> _banedUsers;
			std::vector<Client*> _invites;
//			std::vector<std::string> messages;
		/*---------------------------------------------------------------------------------------------*/
		public:
			Channel();
			Channel(const std::string& name, const Client& creator);
			~Channel();
		public:
			void addUser(const Client& user);
			void removeUser(Client user);
			void addOperator(const Client& user);
			void removeOperator(Client user);
			void banUser(const Client& user);
			void unbanUser(Client user);
			void inviteUser(const Client& user);
			void removeInvitee(Client user);

			/*------------  SETTERS && GETTERS  ----------------*/
			void setName(const std::string& name);
			void setTopic(const std::string& topic);
			void setKey(const std::string& key);
			void setMode(const std::string& mode);
			std::string getName();
			std::string getTopic();
			std::string getMode();
			std::string getKey();
			/*----------------------------------------------*/
			std::vector<Client*> getUsers();
			std::vector<Client*> getOperators();
			std::vector<Client*> getBanedUsers();
			std::vector<Client*> getInvites();
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/

#endif
