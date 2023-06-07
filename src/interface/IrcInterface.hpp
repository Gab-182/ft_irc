#ifndef IRCINTERFACE_HPP
#define IRCINTERFACE_HPP

#include <vector>
#include <cstring>
#include <iostream>
# include "../../includes/IRC/Client.hpp"
namespace IRC {
	class IrcInterface {
		protected:
			// Vector to store all the [clients] on the IRC server.
			std::vector<Client> _clients;
			// Vector to store all the [channels] on the IRC server.
			std::vector<Channel> _channels;

		public:
			IrcInterface();
			~IrcInterface();

			void addClient(const Client& client);
			void addChannel(const Channel& channel);
			void removeClient(const Client& client);
			void removeChannel(const Channel& channel);
	};

} // IRC

#endif //IRCINTERFACE_HPP
