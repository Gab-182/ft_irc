#include "server.hpp"



// socket -> bind -> listen -> accpet(pre req (master socket))
int main(int ac,char **av)
{
	server s;
	if(ac == 2)
	{
		s.create_socket(av[1]);
		s.accept_connection();

		//loop for the accept()
	}
	else
		std::cout << "Not the right argument"<< std::endl;
}