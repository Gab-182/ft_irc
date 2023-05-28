#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <bitset>
#include <climits>
#include <algorithm>
#include <sstream>

#include "./parser/MsgParser.hpp"
#include "message.hpp"
#include "client.hpp"

namespace irc
{
	class client;
	class message;
	class server
	{
		private:
			int master_socket;
			int client_socket;
			
			std::vector <int> sockets;
			std::vector <std::string> msg;
			std::vector <std::string> msgtmp;
			int port;
			int adr;
			int servpass;
			// std::vector <client> clients;
			// char msg[4096];
		public:
			// std::vector<Msg *>
			server();
			~server();
			/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
			void setServPass(int pass); 
			void create_socket(char *av);
			void accept_connection();
			void multi_connection(irc::MsgParser parser);
			int getMasterSocket();
			void setMasterSocket(int socket);
			void split_msg();
			int passCheck();
			std::string nickCheck();
			std::string userCheck();
			/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
			int getServPass();
			int getPort();
			int getAdr();
			std::vector <std::string> getMsg();
			/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
	};
}

#endif