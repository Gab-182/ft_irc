#include "../../include/Server.hpp"
using namespace IRC;


/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
Server::Server() : master_socket(), client_socket(), port(), adr(), servpass(){}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
Server::~Server(){}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int Server::getPort(){return port;}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int Server::getAdr(){return adr;}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int Server::getMasterSocket(){return master_socket;}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void Server::setMasterSocket(int socket){master_socket = socket;}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void Server::setServPass(int pass){servpass = pass;}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
int Server::getServPass(){return servpass;}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
// socket -> bind -> listen 
void Server::create_socket(char *av)
{
	struct sockaddr_in sockin;
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
	if(bind(this->master_socket,(sockaddr*)&sockin,sizeof(sockin)) == -1)
	{
		std::cout << "Error bind" << std::endl;
		exit(1);
	}
	//backlog is the number of connection that can be waiting while the
	// server is handling a connection
	if(listen(this->master_socket,5) == -1)
	{
		std::cout << "Error listen" << std::endl;
		exit(1);
	}
	
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
void Server::accept_connection()
{
		int res;
	char buffer[4096];
	for(;;)
	{
		struct sockaddr_in client;
		socklen_t size = sizeof(client);
		this->client_socket = accept(this->master_socket,(sockaddr*)&client,&size);
		while((res = recv(this->client_socket,buffer,4096,0)) > 0)
		{
			std::cout << "Message received" << std::endl;
			std::cout << buffer << std::endl;
		}
		if (res < 0)
		{
			std::cout << "Error recv" << std::endl;
			exit(1);
		}
	close(this->client_socket);
	}
	close(this->master_socket);
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
//poll() -> select() -> epoll() 

/*
	**select()** is a system call that allows a program to monitor multiple file descriptors
	ft_set to set the sd for select()
	todo: init the sds in a loop using FD_SET
	- FD_SET() adds the file descriptor fd to the set pointed to by fdset.
	todo: use select() to check if there is a new connection
	- select() first parameter is the highest-numbered file descriptor in any of the three sets, plus 1
	- select() second parameter is a pointer to a set of file descriptors to be checked for readability
	todo: use FD_ISSET() to chekc the mastersocket for any incoming connection
	- FD_ISSET() returns a non-zero value if the file descriptor fd is a member of the set pointed to by fdset
	todo:accept the connection
	- check if the connection is valid and a loop for recv()
	


*/

/*check the password and send the welcome message
	if the password is correct return 1
	else return 0
*/
int Server::passCheck()
{
	int pass;
	std::string tmp = this->msgtmp[1];
	std::stringstream ss(tmp);
	std::string split;
	
	while(std::getline(ss,split,' '))
	{
		if(split == "PASS")
		{
			std::getline(ss,split,' ');
			pass = atoi(split.c_str());
			if(pass == this->servpass)
			{
				return(1);
			}
			else
			{
				std::cout << "Password is incorrect" << std::endl;
				std::string msg = "ERROR :Invalid password\r\n";
				if(send(this->sockets[0],msg.c_str(),msg.size(),0) == -1)
					std::cout<< "this is not SEND WHY\n";
				return(0);
			}
		}
	}
	return(0);

}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
std::string Server::nickCheck()
{
	std::string tmp = this->msgtmp[2];
	std::stringstream ss(tmp);
	std::string split;
	while(std::getline(ss,split,' '))
	{
		if(split == "NICK")
		{
			std::getline(ss,split,' ');
			if(split.empty())
			{
				std::cout << "Nick is empty" << std::endl;
				std::string msg = "ERROR :Invalid nickname\r\n";
				return("");
			}
			else {
				std::cout << "Nick is not empty" << std::endl;
				return(split);

			}
		}
	}
	return("");
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
std::string Server::userCheck()
{
	std::string tmp = this->msgtmp[3];
	std::stringstream ss(tmp);
	std::string split;
	while(std::getline(ss,split,' '))
	{
		if(split == "USER")
		{
			std::getline(ss,split,' ');
			if(split.empty())
			{
				return("");
			}
			else {
				std::cout << "User is not empty" << std::endl;
				return(split);
			}
		}
	}
	return("");
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
/*
	check id passCheck return 1 && nick is not empty && user is not empty 
	then push_back the client to the vector of clients and fill client info in the client class
	socket.back() to send as the last socket
	?should i check if the nick is already taken or not
	?chekc if there is error msgs to send
*/
void Server::split_msg()
{
	std::stringstream ss(this->msg.back());
	std::string split, nick, user;
	while(std::getline(ss,split,'\n'))
	{
		this->msgtmp.push_back(split);
	}
	if (this->msgtmp.size() == 4)  // when client replay with CAP,PASS,NICK,USER
	{
		if(passCheck() == 1)
		{
			//split NICK
			nick = nickCheck();
			//split USER
			user = userCheck();
			std::string msg = "CAP * LS :multi-prefix sasl\r\n";
			std::string wlcome = ":"+ nick +" 001 "+nick+" :Welcome to the Internet Relay Network "+nick+"!~"+user+"@localhost\r\n";
			if(send(this->sockets.back(),msg.c_str(),msg.size(),0) == -1)
				std::cout<< "error occurred while sending CAP LS\n";
			if(send(this->sockets.back(),wlcome.c_str(),wlcome.size(),0) == -1)
				std::cout<< "error occurred while sending welcome msg\n";
		}
	}
	//erase all elem in msgtmp
	this->msgtmp.clear();
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
 void Server::multi_connection(MsgParser parser)
 {
 	int res;
 	int max_sd = 0;
 	char buffer[1024];
 	fd_set fdset;
 	struct sockaddr_in clientadd;
 	socklen_t size = sizeof(clientadd);
 	std::string clientMsg; // String to store client messages

 	for (;;)
 	{
 		FD_ZERO(&fdset);						// Clear the socket set
 		FD_SET(this->master_socket, &fdset);	// Add master socket to set
 		max_sd = this->master_socket;			// Set the max sd to the master socket

 		// Add child sockets to set
 		std::vector<int>::iterator it;
 		for (it = this->sockets.begin(); it != this->sockets.end(); it++)
 		{
 			int sd = *it;
 			if (sd > 0)
 				FD_SET(sd, &fdset);
 			if (sd > max_sd)
 				max_sd = sd;
 		}
 		if (select(max_sd + 1, &fdset, NULL, NULL, NULL) == -1)
 		{
 			std::cout << "Error select" << std::endl;
 			exit(1);
 		}

 		if (FD_ISSET(this->master_socket, &fdset))
 		{
 			if ((this->client_socket = accept(this->master_socket, (sockaddr *)&clientadd, &size)) == -1)
 			{
 				std::cout << "Error accept" << std::endl;
 				exit(1);
 			}
			DEBUG_MSG("Connection accepted")
 			this->sockets.push_back(this->client_socket);
 			clientMsg = ""; // Initialize message for new client socket
 		}

 		for (size_t i = 0; i < this->sockets.size(); i++)
 		{
 			int clientSocket = this->sockets[i];
 			if (FD_ISSET(clientSocket, &fdset))
 			{
 				if ((res = recv(clientSocket, buffer, 1024, 0)) == 0)
 				{
					DEBUG_MSG("Client disconnected from socket")
 					close(clientSocket);
 					this->sockets.erase(this->sockets.begin() + i);
 					continue; // Continue to the next iteration
 				}
 				buffer[res] = '\0';
 				clientMsg += buffer;
 				std::memset(buffer, 0, 1024);
				DEBUG_MSG(BOLDMAGENTA << "HandShake Message: " << RESET << std::endl << clientMsg)
				parser.processHandShake(clientSocket, clientMsg, this->getServPass());
 			}
 		}
 	}
 	close(this->master_socket);
 }


/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
//void Server::multi_connection(MsgParser parser)
//{
//	int res;
//	int max_sd = 0;
//	int sd;
//	char buffer[1024];
//	fd_set fdset;
//	struct sockaddr_in clientadd;
//	socklen_t size = sizeof(clientadd);
//	int clientSocket;
//
//	for(;;)
//	{
//		FD_ZERO(&fdset);//clear the socket set
//		FD_SET(this->master_socket,&fdset);//add master socket to set
//		max_sd = this->master_socket; //set the max sd to the master socket
//		//add child sockets to set
//		for(std::vector<int>::iterator it = this->sockets.begin(); it != this->sockets.end(); it++)
//		{
//			sd = *it;
//			if(sd > 0) {
//				FD_SET(sd,&fdset);
//			}
//			if(sd > max_sd) {
//				max_sd = sd;
//			}
//		}
//		if(select(max_sd +1,&fdset,NULL,NULL,NULL) == -1)
//		{
//			std::cout << "Error select" << std::endl;
//			exit(1);
//		}
//		if(FD_ISSET(this->master_socket,&fdset))
//		{
//			if((this->client_socket = accept(this->master_socket,(sockaddr*)&clientadd,&size)) == -1)
//			{
//				std::cout << BOLDRED << "🟡 Error accept 🔴" << RESET << std::endl;
//				exit(1);
//			}
//			std::cout << BOLDYELLOW << "🟡 Connection accepted 🔴" << RESET << std::endl;
//			this->sockets.push_back(this->client_socket);
//			this->msg.push_back("");
//		}
//		//new function get_msg()
//		for(size_t i = 0; i < this->sockets.size(); i++)
//		{
//			clientSocket = this->sockets[i];
//			if(FD_ISSET(this->sockets[i],&fdset))
//			{
//				if((res = recv(this->sockets[i],buffer,1024,0)) == 0)
//				{
//					std::cout << BOLDRED << "🟡 Client disconnected 🔴" << RESET << std::endl;
//					close(this->sockets[i]);
//					this->sockets.erase(this->sockets.begin() + i);
//				}
//				else
//				{
//					buffer[res]= '\0';
//					this->msg[i] += buffer;
//					std::memset(buffer,0,1024);
//				}
////				std::cout << BOLDGREEN << "🟡 Message received 🔴" << RESET << std::endl;
////				std::cout << BOLDGREEN << "🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡"
////											<< this->msg[i] << std::endl
////											<< " 🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴"
////											<< RESET << std::endl;
////				split_msg();
//				parser.processHandShake(this->sockets[i], this->msg[i], this->getServPass());
//			}
//		}
//	}
//	close(this->master_socket);
//}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
std::vector <std::string> Server::getMsg() {
	return this->msg;
}

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/