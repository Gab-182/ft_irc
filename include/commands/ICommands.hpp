#ifndef ICOMMANDS_HPP
#define ICOMMANDS_HPP

#include <unistd.h>
#include <cstring>
#include <sstream>
#include <iostream>

#include "../Client.hpp"
#include "../Channel.hpp"

namespace IRC {
	class ICommands {
		protected:
			std::string _command;
			std::vector<std::string> _parameters;

		public:
			ICommands();
			~ICommands();
			/*-----------------------------------------------------------------------*/
			void getCommand(const int& clientSocket, const std::string clientMessage);

//			/*-----------------------------------------------------------------------*/
//			std::vector<std::string> getParameters(const int& clientSocket) {
//
//			}
//
//			/*-----------------------------------------------------------------------*/
//			virtual void executeCommand(const int& clientSocket) = 0;
	};
}


#endif //ICOMMANDS_HPP
