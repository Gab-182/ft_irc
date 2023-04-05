#ifndef CLIENT_HPP
#define CLIENT_HPP

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
#include "server.hpp"

class client
{
	private:
		std::string user;
		std::string pass;
		std::string nick;
		std::string host;
	public:
		client();
		~client();
		void set_user(std::string user);
		void set_pass(std::string pass);
		void set_nick(std::string nick);
		void set_host(std::string host);
		std::string get_user();
		std::string get_pass();
		std::string get_nick();
		std::string get_host();
		void print();
};

#endif