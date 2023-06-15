#ifndef JOIN_HPP
#define JOIN_HPP

#include "../Client.hpp"
#include "ICommands.hpp"

namespace IRC {
	class Join : public ICommands {
		public:
			Join();
			~Join();
			void join(int clientSocket, const std::vector<Client>& clients);
	};
}


#endif //JOIN
