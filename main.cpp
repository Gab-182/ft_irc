# include "./include/IRC.hpp"
# include "./include/commands/ICommands.hpp"
/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
// socket -> bind -> listen -> accept(pre req (master socket))
int main(int ac,char **av) {
	IRC::Server ircServer;
	IRC::HandShake handShaker;
	IRC::ICommands *commands = new IRC::ICommands();

	if(ac == 3) {
		//todo: check if the port is a number and if the password is a number
		ircServer.setServPass(atoi(av[2]));
		ircServer.create_socket(av[1]);
		ircServer.multi_connection(handShaker, commands);
	}
	else {
		std::cout << "Please provide the following arguments:" << std::endl;
		std::cout << "  <port>     : The port number to listen on." << std::endl;
		std::cout << "  <password> : The password for the server." << std::endl;
	}
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/