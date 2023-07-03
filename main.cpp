# include "./include/IRC.hpp"
# include "./include/commands/ICommands.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
// socket -> bind -> listen -> accept(pre req (master socket))
int main(int ac,char **av) {
	Server* ircServer = new IRC::Server();
	ICommands* commands = new IRC::ICommands();


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
