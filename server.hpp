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
			int port;
			int adr;
			// char msg[4096];
		public:
			// std::vector<Msg *>
			server();
			~server();
			void create_socket(char *av);
			void accept_connection();
			void multi_connection();
			int getPort();
			int getAdr();
			int getMasterSocket();
			void setMasterSocket(int socket);
			void split_msg();

	};
}

#endif