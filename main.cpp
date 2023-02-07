#include "server.hpp"

// socket -> bind -> listen 
void server::create_socket(char *av)
{
	struct sockaddr_in sockin; 
	int port = atoi(av);
	sockin.sin_addr.s_addr = htonl(INADDR_ANY);
	sockin.sin_family = AF_INET;
	sockin.sin_port = htons(port);
	/*
		create a socket 
		AF_INET = ipv4 , SOCK_STREAM = tcp 
	*/
	int newsocket = socket(AF_INET,SOCK_STREAM,0);
	bind(newsocket,(sockaddr*)&sockin,sizeof(sockin));
	
		
}

// socket -> bind -> listen -> accpet(pre req (master socket))
int main(int ac,char **av)
{
	server s;
	if(ac == 2)
	{
		s.create_socket(av[1]);
		

		//loop for the accept()
	}
	else
		std::cout << "Not the right argument"<< std::endl;
}