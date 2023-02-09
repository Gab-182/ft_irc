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

//poll() -> select() -> epoll() 

/*
	**select()** is a system call that allows a program to monitor multiple file descriptors
	ft_set to set the sd for select()
	todo: init the sds in a loop using FD_SET
	- FD_SET() adds the file descriptor fd to the set pointed to by fdset.
	todo: use select() to check if there is a new connection
	- select() first parameter is the highest-numbered file descriptor in any of the three sets, plus 1
	- select() second parameter is a pointer to a set of file descriptors to be checked for readability
	todo: use FD_ISSET() to chekc the mastersocket for any incoming connection
	- FD_ISSET() returns a non-zero value if the file descriptor fd is a member of the set pointed to by fdset
	todo:accept the connection
	- check if the connection is valid and a loop for recv()
	


*/

void server::multi_connection()
{
	int res;
	int max_sd = 0;
	int sd;
	char buffer[4096];
	fd_set fdset;
	struct sockaddr_in clientadd;
	socklen_t size = sizeof(clientadd);
	int client[30];

    for (int i = 0; i < 30; i++)  
    {  
       client[i] = 0;  
    }  
	for(;;)
	{
		FD_ZERO(&fdset);//clear the socket set
		FD_SET(this->master_socket,&fdset);//add master socket to set
		max_sd = this->master_socket; //set the max sd to the master socket
		//add child sockets to set
		for(int i = 0; i < 30; i++)
		{
			sd = client[i];
			if(sd > 0)
			{
				FD_SET(sd,&fdset);
			}
			if(sd > max_sd)
				max_sd = sd;
		}
		if(select(max_sd +1,&fdset,NULL,NULL,NULL) == -1)
		{
			std::cout << "Error select" << std::endl;
			exit(1);
		}
		if(FD_ISSET(this->master_socket,&fdset))
		{
			
			if((this->client_socket = accept(this->master_socket,(sockaddr*)&clientadd,&size)) == -1)
			{
				std::cout << "Error accept" << std::endl;
				exit(1);
			}
				std::cout << "Connection accepted" << std::endl; 
			for(int i = 0; i < 30 ; i++)
			{
				if(client[i] == 0)
				{
					client[i] = this->client_socket;
                    printf("Adding to list of sockets as %d\n" , i);  
					break;
				}
			}
		}
		for (int i = 0 ; i < 30; i++)
		{
			sd = client[i];

			if(FD_ISSET(sd,&fdset))
			{				
				if((res = read(sd,buffer,4096)) == 0)
				{
					std::cout << "Client disconnected" << std::endl;
					close(sd);
					client[i] = 0;
				}
				else
				{
					std::cout << "Message received" << std::endl;
					std::cout << buffer << std::endl;
				}
			}
		}
	}
	close(this->master_socket);
}

