# include "./include/IRC.hpp"
# include "./include/commands/ICommands.hpp"

/*------------------------------------------------------------------------------------------------------------------*/
// socket -> bind -> listen -> accept(pre req (master socket))
int main(int ac,char **av) {
	IRC::Server* ircServer = new IRC::Server();
	IRC::HandShake* handShaker = new IRC::HandShake();
	IRC::ICommands* commands = new IRC::ICommands();


	// Allocate memory for all the objects of the commands classes.
	commands->registerCommands();

	//TODO: check if the port is a number and if the password is a number
	if(ac == 3) {
		ircServer->setServPass(atoi(av[2]));
		ircServer->create_socket(av[1]);
		ircServer->multi_connection(handShaker, commands);
	}
	else {
		std::cout << "Please provide the following arguments:" << std::endl;
		std::cout << "  <port>     : The port number to listen on." << std::endl;
		std::cout << "  <password> : The password for the server." << std::endl;
	}

	// Deleting all the objects created in the main function to prevent memory leaks.
	// TODO: You should properly delete all the objects of the commands classes.

	delete commands;
	delete handShaker;
	delete ircServer;

	return (0);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/