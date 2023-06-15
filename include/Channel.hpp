#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <cstring>
#include <ostream>
#include <vector>

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
namespace IRC {
	class Channel {
		private:
			std::string _name;						//▶️ The name of the channel.
			std::string _topic;						//▶️ The topic of the channel.
			std::string _key;						//▶️ The password/key required to join the channel.
			std::string _mode;						//▶️ The mode of the channel.
			std::vector<std::string> _users;		//▶️ The list of users in the channel.
			std::vector<std::string> _operators;	//▶️ The list of operators in the channel.
			std::vector<std::string> _banedUsers;	//▶️ The list of banned users in the channel.
			std::vector<std::string> _invites;		//▶️ The list of invited users to the channel.
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
		public:
			Channel(std::string name);
			~Channel();
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
		public:
			void addUser(std::string user);
			void removeUser(std::string user);
			void addOperator(std::string user);
			void removeOperator(std::string user);
			void banUser(std::string user);
			void unbanUser(std::string user);
			void inviteUser(std::string user);
			void removeInvitee(std::string user);
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎  SETTERS && GETTERS  ❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄*/
			void setName(std::string name);
			void setTopic(std::string topic);
			void setKey(std::string key);
			void setMode(std::string mode);
			std::string getName();
			std::string getTopic();
			std::string getMode();
			std::string getKey();
			std::vector<std::string> getUsers();
			std::vector<std::string> getOperators();
			std::vector<std::string> getBanedUsers();
			std::vector<std::string> getInvites();
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄*/
	};
	/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
}

#endif
