# include "./include/IRC.hpp"
# include "./include/commands/ICommands.hpp"
#include <iostream>
#include <csignal>
#include <cstdlib>

using namespace IRC;


void sigintHandler(int signal) {
    std::cout << "Ctrl+C (SIGINT) received." << std::endl;
    // You can add custom actions here
    // For example, cleaning up resources, saving data, etc.
    std::exit(signal);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
// socket -> bind -> listen -> accept(pre req (master socket))
int main(int ac,char **av) {
	Server* ircServer = new IRC::Server();
	ICommands* commands = new IRC::ICommands();
	
	std::signal(SIGINT, sigintHandler);   // Ctrl+C (SIGINT)


	// Allocate memory for all the objects of the commands classes.
	commands->registerCommands();

	//TODO: check if the port is a number and if the password is a number
	if(ac == 3) {
		ircServer->setServPass(av[2]);
		ircServer->create_socket(av[1]);
		ircServer->multi_connection(commands);
	}
	else {
		std::cout << "Please provide the following arguments:" << std::endl;
		std::cout << "  <port>     : The port number to listen on." << std::endl;
		std::cout << "  <password> : The password for the server." << std::endl;
	}

	delete (commands);
	delete (ircServer);

	return (0);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
