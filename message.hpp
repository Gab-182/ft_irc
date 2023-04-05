#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "server.hpp"
#include "client.hpp"

namespace irc
{
	class message
	{
		class client;
		private:
			std::string msg;
			std::string prefix;
			std::string command;
			std::vector<std::string> params;
		public:
			message();
			~message();
			void set_msg(std::string msg);
			void set_prefix(std::string prefix);
			void set_command(std::string command);
			void set_params(std::string params);
			std::string get_msg();
			std::string get_prefix();
			std::string get_command();
			std::vector<std::string> get_params();
			void print();
	};
}
#endif