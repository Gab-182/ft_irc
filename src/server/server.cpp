#include "../../include/Server.hpp"
#include "../../include/Client.hpp"
#include "../../include/commands/ICommands.hpp"

using namespace IRC;

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
Server::Server() :
	port(), servpass(), sockets(0), master_socket(), client_socket() { }

Server::~Server(){}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
int Server::getPort() const{return port;}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
int Server::getMasterSocket() const{return master_socket;}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Server::setMasterSocket(int socket){master_socket = socket;}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Server::setServPass(std::string pass){servpass = pass;}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
std::string Server::getServPass() const {return servpass;}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
// socket -> bind -> listen 
void Server::create_socket(char *av)
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

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Server::respondToClient(const int& clientSocket, Client* client, std::string& clientMsg, ICommands* commands) {
	// DEBUG_MSG("Message: " << std::endl << "=========" << std::endl << BOLDBLUE << clientMsg)
	commands->getCommandInfo(clientMsg);
	commands->executeCommand(commands, clientSocket, this, client, "start");

//	// Debugging:
	// if (client != NULL) {
	// 	this->printClients();
	// 	this->printChannels();
	// }
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Server::multi_connection(ICommands* commands) {
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

			/*-----------------------------------------------------------*/
			// Find the client in the server's map
			std::map<int, Client *>::iterator itClient;
			itClient = this->serverClientsMap.find(clientSocket);
			/*-----------------------------------------------------------*/

 			if (FD_ISSET(clientSocket, &fdset)) {
 				if ((res = recv(clientSocket, buffer, 1024, 0)) == 0) {

					/*------------------------------------------------------------------------------------------------*/
					// If the client is allocated and saved to the server, then remove it from the server.
					if (itClient != this->serverClientsMap.end())
						itClient->second->removeClientFromServer(clientSocket, this, itClient->second);
					/*------------------------------------------------------------------------------------------------*/

					close(clientSocket);
 					this->sockets.erase(this->sockets.begin() + i);
 					continue;
 				}

 				buffer[res] = '\0';
 				clientMsg += buffer;
 				std::memset(buffer, 0, 1024);
				respondToClient(clientSocket, itClient->second, clientMsg, commands);
			}
		}
	}
 	close(this->master_socket);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Server::printClients() {
	int i = 1;
	std::cout << BOLDGREEN << '\t' << '\t' << "Clients" << std::endl;
	std::map<int, Client*>::iterator it;
	for (it = serverClientsMap.begin(); it != serverClientsMap.end() ;++it) {
		if (it ->first && it->second) {
			std::cout << BOLDBLUE << "Client: [" << BOLDGREEN << i << BOLDBLUE << "]" << std::endl;
			std::cout << BOLDBLUE << '\t' << "Socket: [" << BOLDWHITE << it->first << BOLDBLUE << "]" << std::endl;
			std::cout << BOLDBLUE << '\t' << "Nick: [" << BOLDWHITE << it->second->getNickName() << BOLDBLUE << "]"
					  << std::endl;
			std::cout << BOLDBLUE << '\t' << "User: [" << BOLDWHITE << it->second->getUserName() << BOLDBLUE << "]"
					  << std::endl;
			std::cout << BOLDBLUE << '\t' << "isClientWelcomed: [" << BOLDWHITE << it->second->isClientWelcomed() << BOLDBLUE << "]"
					  << std::endl;
			std::cout << BOLDYELLOW << "-----------------------------------------------" << std::endl;
		}
		i++;
	}
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
int Server::getClients(std::string nickName) {
	std::map<int, Client*>::iterator it;
	for (it = serverClientsMap.begin(); it != serverClientsMap.end() ;++it) {
		if (it ->first && it->second) {
			if (nickName == it->second->getNickName())
				return (1);
		}
	}
	return (0);
}

int	Server::getSocket(std::string nickName)	{
	
	std::map<int, Client*>::iterator it;
	for (it = serverClientsMap.begin(); it != serverClientsMap.end() ;++it) {
		if (it ->first && it->second) {
			if (nickName == it->second->getNickName())
				return (it->second->getSocket());
		}
	}
	return (-1);
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
void Server::printChannels() {
	std::map<std::string, Channel*>::iterator it;
	std::cout << BOLDGREEN << "Channels" << std::endl;
	for (it = serverChannelsMap.begin(); it != serverChannelsMap.end() ;++it) {
		if (!(it ->first.empty()))
			std::cout << BOLDBLUE << "Channel: [" << BOLDGREEN << it->first << BOLDBLUE << "]" << std::endl;
	}
	std::cout << BOLDYELLOW << "-----------------------------------------------" << std::endl;
}


int Server::getClientSocket(std::string nickName) {
	std::map<int, Client*>::iterator it;
	for (it = serverClientsMap.begin(); it != serverClientsMap.end() ;++it) {
		if (it ->first && it->second) {
			if (nickName == it->second->getNickName())
				return (it->first);
		}
	}
	return (0);
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/