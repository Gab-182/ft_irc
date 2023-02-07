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
	if(bind(newsocket,(sockaddr*)&sockin,sizeof(sockin)) == -1)
	{
		std::cout << "Error bind" << std::endl;
		exit(1);
	}
	if(listen(newsocket,10) == -1)
	{
		std::cout << "Error listen" << std::endl;
		exit(1);
	}
	//loop for the accept()	
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