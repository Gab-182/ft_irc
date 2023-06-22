#include "../../include/Server.hpp"
#include "../../include/HandShake.hpp"
#include "../../include/commands/ICommands.hpp"

using namespace IRC;

/*-------------------------------------------------------------------------------------------------------------*/
IRC::Server::Server() :
	port(), servpass(), sockets(0), _clients(0), _channels(0), master_socket(), client_socket() { }

IRC::Server::~Server(){}

/*-------------------------------------------------------------------------------------------------------------*/
int IRC::Server::getPort(){return port;}

/*-------------------------------------------------------------------------------------------------------------*/
int IRC::Server::getMasterSocket(){return master_socket;}

/*-------------------------------------------------------------------------------------------------------------*/
void IRC::Server::setMasterSocket(int socket){master_socket = socket;}

/*-------------------------------------------------------------------------------------------------------------*/
void IRC::Server::setServPass(int pass){servpass = pass;}

/*-------------------------------------------------------------------------------------------------------------*/
int IRC::Server::getServPass() const{return servpass;}

/*-------------------------------------------------------------------------------------------------------------*/
// socket -> bind -> listen 
void IRC::Server::create_socket(char *av)
{
	struct sockaddr_in sockin = {};
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
	if(bind(this->master_socket,(sockaddr*)&sockin,sizeof(sockin)) == -1) {
		std::cout << "Error bind" << std::endl;
		exit(1);
	}
	//backlog is the number of connection that can be waiting while the
	// server is handling a connection
	if(listen(this->master_socket,5) == -1) {
		std::cout << "Error listen" << std::endl;
		exit(1);
	}
}

/*-------------------------------------------------------------------------------------------------------------*/
void IRC::Server::multi_connection(HandShake* handShaker, ICommands* commands) {
 	int res;
 	int max_sd = 0;
 	char buffer[1024];
 	fd_set fdset;
 	struct sockaddr_in clientadd;
 	socklen_t size = sizeof(clientadd);
 	std::string clientMsg; // String to store client messages
	/*--------------------------------------------------------------------------------------------------*/
	while (1) {
		FD_ZERO(&fdset);						// Clear the socket set
		FD_SET(this->master_socket, &fdset);	// Add master socket to set
		max_sd = this->master_socket;			// Set the max sd to the master socket

		/*--------------------------------------------------------------------------------------------------*/
 		// Add child sockets to set
		std::vector<int>::iterator it;
		for (it = this->sockets.begin(); it != this->sockets.end(); it++) {
			int sd = *it;
			if (sd > 0)
				FD_SET(sd, &fdset);
			if (sd > max_sd)
				max_sd = sd;
		}
		/*--------------------------------------------------------------------------------------------------*/
		if (select(max_sd + 1, &fdset, NULL, NULL, NULL) == -1) {
 			std::cout << "Error select" << std::endl;
 			exit(1);
 		}
		/*--------------------------------------------------------------------------------------------------*/
		if (FD_ISSET(this->master_socket, &fdset)) {
 			if ((this->client_socket = accept(this->master_socket, (sockaddr *)&clientadd, &size)) == -1) {
 				std::cout << "Error accept" << std::endl;
 				exit(1);
 			}
			DEBUG_MSG("Connection accepted")
 			this->sockets.push_back(this->client_socket);
 			clientMsg = ""; // Initialize message for new client socket
 		}
		/*--------------------------------------------------------------------------------------------------*/
		// Check for client activity

		for (size_t i = 0; i < this->sockets.size(); i++) {
			clientMsg = ""; // Reset message for next response
 			int clientSocket = this->sockets[i];

 			if (FD_ISSET(clientSocket, &fdset)) {
 				if ((res = recv(clientSocket, buffer, 1024, 0)) == 0) {
					DEBUG_MSG("Client disconnected from socket")
					handShaker->removeClient(clientSocket, this);
 					close(clientSocket);
 					this->sockets.erase(this->sockets.begin() + i);
 					continue; // Continue to the next iteration
 				}

 				buffer[res] = '\0';
 				clientMsg += buffer;
 				std::memset(buffer, 0, 1024);

				/*-------------------------------------------------------------------------------------*/
				// Check if client is registered, if not, process handshake and register client
				DEBUG_MSG("Message: " << std::endl << "=========" << std::endl << BOLDBLUE << clientMsg)
				/*-------------------------------------------------------------------------------------*/
				// parse the client message, then check if username and nick and pass are correct,
				// if so, that mean that the client is authenticated and can proceed to the next step.

				if (!HandShake::isClientRegistered(clientSocket, this)) {
					if (!handShaker->processHandShake(clientSocket, clientMsg, this))
						continue;
				}
				/*-------------------------------------------------------------------------------------*/
				// parse the message from the interface then, execute the requested command
				//from the map of commands, then send the response to the client.

				commands->getCommandInfo(clientSocket, clientMsg);
//				commands->debugCommands();
				commands->executeCommand(commands, clientSocket, this);
				/*-------------------------------------------------------------------------------------*/

			}
		}
		// this->printClients();
	}
 	close(this->master_socket);
}

/*-------------------------------------------------------------------------------------------------------------*/
