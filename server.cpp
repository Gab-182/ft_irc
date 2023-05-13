#include "server.hpp"


std::string storage = "";
irc::server::server(){}
irc::server::~server(){}
int irc::server::getPort(){return port;}
int irc::server::getAdr(){return adr;}
int irc::server::getMasterSocket(){return master_socket;}
void irc::server::setMasterSocket(int socket){master_socket = socket;}

void irc::server::setServPass(int pass){servpass = pass;}
int irc::server::getServPass(){return servpass;}

// socket -> bind -> listen 
void irc::server::create_socket(char *av)
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

void irc::server::accept_connection()
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
void irc::server::passCheck()
{
	int pass;
	std::string tmp = this->msgtmp[1];
	std::stringstream ss(tmp);
	std::string split;
	
	while(std::getline(ss,split,' '))
	{
		if(split == "PASS")
		{
			std::getline(ss,split,' ');
			pass = atoi(split.c_str());
			if(pass == this->servpass)
			{
				std::cout << "Password is correct" << std::endl;
				std::string msg = "CAP * LS :multi-prefix sasl\r\n";
				if(send(this->sockets[0],msg.c_str(),msg.size(),0) == -1)
					std::cout<< "this is not SEND WHY\n";
				// std::cout << "Message sent" << std::endl;
				std::string wlcome = ":oobn 001 oobn :Welcome to the Internet Relay Network oobn!~oobn@localhost\r\n";
				if(send(this->sockets[0],wlcome.c_str(),wlcome.size(),0) == -1)
					std::cout<< "this is not SEND WHY\n";
			}
			else
			{
				std::cout << "Password is incorrect" << std::endl;
				std::string msg = "ERROR :Invalid password\r\n";
				if(send(this->sockets[0],msg.c_str(),msg.size(),0) == -1)
					std::cout<< "this is not SEND WHY\n";
			}
		}
	}

}

void irc::server::split_msg()
{
	// this->msgtmp.push_back(this->msg.back());
	std::stringstream ss(this->msg.back());
	std::string split;
	while(std::getline(ss,split,'\n'))
	{
		this->msgtmp.push_back(split);
	}
	if (this->msgtmp.size() == 4)  // when client replay with CAP,PASS,NICK,USER
	{
		//slpit PASS
		passCheck();
		//split NICK

		//split USER

	}
	//erase all elem in msgtmp
	this->msgtmp.clear();
}

void irc::server::multi_connection()
{
	int res;
	int max_sd = 0;
	int sd;
	char buffer[1024];
	fd_set fdset;
	struct sockaddr_in clientadd;
	socklen_t size = sizeof(clientadd);
	for(;;)
	{
		FD_ZERO(&fdset);//clear the socket set
		FD_SET(this->master_socket,&fdset);//add master socket to set
		max_sd = this->master_socket; //set the max sd to the master socket
		//add child sockets to set
		for(std::vector<int>::iterator it = this->sockets.begin(); it != this->sockets.end(); it++)
		{
			sd = *it;
			if(sd > 0)
				FD_SET(sd,&fdset);
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
			this->sockets.push_back(this->client_socket);
			this->msg.push_back("");
		}
		//new function get_msg() 
		for(size_t i = 0; i < this->sockets.size(); i++)
		{
			
			if(FD_ISSET(this->sockets[i],&fdset))
			{
				if((res = recv(this->sockets[i],buffer,1024,0)) == 0)
				{
					std::cout << "Client disconnected" << std::endl;
					close(this->sockets[i]);
					this->sockets.erase(this->sockets.begin() + i);
				}
				else
				{
					buffer[res]= '\0';
					 
					std::cout << "Message received" << this->sockets.size() << std::endl;
					this->msg[i] += buffer;
					std::cout <<  "+- "<< buffer <<  " -+ "<<std::endl;
					// if(send(this->sockets[i],msg.c_str(),msg.size(),0) == -1)
					// 	std::cout<< "this is not SEND WHY\n";
					// std::cout << "Message ended" << std::endl;
					     
					std::memset(buffer,0,1024);

					for(std::vector<std::string>::iterator it = this->msg.begin(); it != this->msg.end(); it++)
					{
						std::cout <<*it << std::endl;
					}
				}
				split_msg();
			}
		}
	}
	close(this->master_socket);


}

