#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

class server
{
	private:
		int master_socket;
		int client_socket;
		std::vector <int> sockets;
		int port;
		int adr;
		//vector of sockets ..
		
	public:
		server();
		~server();
		void create_socket(char *av);
		void accept_connection();
		void multi_connection();
		int getPort();
		int getAdr();
		int getMasterSocket();
		void setMasterSocket(int socket);

};


#endif