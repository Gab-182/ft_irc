#include "server.hpp"


server::server(){}
server::~server(){}
int server::getPort(){return port;}
int server::getAdr(){return adr;}
int server::getMasterSocket(){return master_socket;}
void server::setMasterSocket(int socket){master_socket = socket;}

// socket -> bind -> listen 
void server::create_socket(char *av)
{
	struct sockaddr_in sockin; 
	this->port = atoi(av);

	sockin.sin_addr.s_addr = htonl(INADDR_ANY);
	sockin.sin_family = AF_INET;
	sockin.sin_port = htons(this->port);
	/*
		create a socket 
		AF_INET = ipv4 , SOCK_STREAM = tcp 
	*/
	this->master_socket = socket(AF_INET,SOCK_STREAM,0);
	//bind the socket to the port
	if(bind(this->master_socket,(sockaddr*)&sockin,sizeof(sockin)) == -1)
	{
		std::cout << "Error bind" << std::endl;
		exit(1);
	}
	//backlog is the number of connection that can be waiting while the server is handling a connection
	if(listen(this->master_socket,5) == -1)
	{
		std::cout << "Error listen" << std::endl;
		exit(1);
	}
	
}

void server::accept_connection()
{
	int res;
	char buffer[4096];
	for(;;)
	{
		struct sockaddr_in client;
		socklen_t size = sizeof(client);
		this->client_socket = accept(this->master_socket,(sockaddr*)&client,&size);
		while((res = recv(this->client_socket,buffer,4096,0)) > 0)
		{
			std::cout << "Message received" << std::endl;
			std::cout << buffer << std::endl;
		}
		if (res < 0)
		{
			std::cout << "Error recv" << std::endl;
			exit(1);
		}
	close(this->client_socket);
	}
	close(this->master_socket);
}