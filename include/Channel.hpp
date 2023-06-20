#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <cstring>
#include <ostream>
#include <vector>

#include "Client.hpp"
/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
namespace IRC {
	class Channel {
		private:
			std::string _name;						//▶️ The name of the channel.
			std::string _topic;						//▶️ The topic of the channel.
			std::string _key;						//▶️ The password/key required to join the channel.
			std::string _mode;						//▶️ The mode of the channel.
			std::vector<Client> _users;				//▶️ The list of users in the channel.
			std::vector<Client> _operators;			//▶️ The list of operators in the channel.
			std::vector<Client> _banedUsers;		//▶️ The list of banned users in the channel.
			std::vector<Client> _invites;			//▶️ The list of invited users to the channel.
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
		public:
			Channel();
			Channel(std::string name);
			~Channel();
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
		public:
			void addUser(Client user);
			void removeUser(Client user);
			void addOperator(Client user);
			void removeOperator(Client user);
			void banUser(Client user);
			void unbanUser(Client user);
			void inviteUser(Client user);
			void removeInvitee(Client user);
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎  SETTERS && GETTERS  ❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄*/
			void setName(std::string name);
			void setTopic(std::string topic);
			void setKey(std::string key);
			void setMode(std::string mode);
			std::string getName();
			std::string getTopic();
			std::string getMode();
			std::string getKey();
			std::vector<Client> getUsers();
			std::vector<Client> getOperators();
			std::vector<Client> getBanedUsers();
			std::vector<Client> getInvites();
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄*/
	};
	/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
}

#endif
