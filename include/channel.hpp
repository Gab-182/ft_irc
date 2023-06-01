#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <cstring>
#include <ostream>
#include <vector>

namespace IRC {
    /**
     * @class Channel
     * @brief Represents an IRC channel with various properties and functionality.
     */
	/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
    class Channel {
    private:
        std::string _name;						//▶️ The name of the channel.
        std::string _topic;						//▶️ The topic of the channel.
        std::string _key;                		//▶️ The password/key required to join the channel.
        std::string _mode;               		//▶️ The mode of the channel.
        std::vector<std::string> _users;		//▶️ The list of users in the channel.
        std::vector<std::string> _operators;	//▶️ The list of operators in the channel.
        std::vector<std::string> _baned_users;	//▶️ The list of banned users in the channel.
        std::vector<std::string> _invites;		//▶️ The list of invited users to the channel.
	/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
    public:
        /**
         * @brief Constructs a Channel object with the specified name.
         * @param name The name of the channel.
         */
        Channel(std::string name);

        /**
         * @brief Destructor for the Channel object.
         */
        ~Channel();

        /**
         * @brief Copy constructor for the Channel object.
         * @param other The Channel object to be copied.
         */
        Channel(const Channel& other);

        /**
         * @brief Assignment operator for the Channel object.
         * @param other The Channel object to be assigned.
         * @return Reference to the assigned Channel object.
         */
        Channel& operator=(const Channel& other);
	/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
    public:
        /**
         * @brief Adds a user to the channel.
         * @param user The user to be added.
         */
        void AddUser(std::string user);

        /**
         * @brief Removes a user from the channel.
         * @param user The user to be removed.
         */
        void RemoveUser(std::string user);

        /**
         * @brief Adds an operator to the channel.
         * @param user The user to be added as an operator.
         */
        void AddOperator(std::string user);

        /**
         * @brief Removes an operator from the channel.
         * @param user The user to be removed as an operator.
         */
        void RemoveOperator(std::string user);

        /**
         * @brief Bans a user from the channel.
         * @param user The user to be banned.
         */
        void BanUser(std::string user);

        /**
         * @brief Unbans a user from the channel.
         * @param user The user to be unbanned.
         */
        void UnbanUser(std::string user);

        /**
         * @brief Invites a user to the channel.
         * @param user The user to be invited.
         */
        void InviteUser(std::string user);

        /**
         * @brief Removes an invitee from the channel.
         * @param user The user to be removed from the invites list.
         */
        void RemoveInvitee(std::string user);
    };
	/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄❄❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
}

#endif
