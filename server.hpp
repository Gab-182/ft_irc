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

class server
{
	private:
		int port;
		int addres;
	public:
		server();
		~server();
		void create_socket(char *av); 

}


#endif