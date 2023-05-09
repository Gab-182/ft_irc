#include "server.hpp"



// socket -> bind -> listen -> accpet(pre req (master socket))
int main(int ac,char **av)
{
	irc::server s;
	if(ac == 3)
	{
		//todo: check if the port is a number and if the password is a number
		s.setServPass(atoi(av[2]));
		s.create_socket(av[1]);
		// s.accept_connection();
		s.multi_connection();
		//loop for the accept()
	}
	else
		std::cout << "Not the right argument"<< std::endl;
}