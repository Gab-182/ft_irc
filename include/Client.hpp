#ifndef CLIENT_HPP
#define CLIENT_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include <iostream>
#include <cstring>

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	// Forward declarations:
	class Server;

	class Client {
		private:
			int _socket;
			std::string _userName;
			std::string _nickName;
			bool _isWelcomed;
			
		/*--------------------------------------------------------*/
		public:
			Client();
			Client(int socket);
			~Client();
			Client(const Client& other);
			Client& operator=(const Client& other);
		/*--------------------------------------------------------*/
			void setSocket(const int& socket);
			void setUserName(const std::string& userName);
			void setNickName(const std::string& nickName);
			void welcomeClient(bool welcome);
		/*--------------------------------------------------------*/
			int getSocket() const;
			std::string getUserName();
			std::string getNickName();
			bool isWelcomed() const;
		/*--------------------------------------------------------*/
			static void sendResponse(int clientSocket, const std::string& message);
			static bool isClientAuthenticated(const int& clientSocket, Server* server);
			static bool isClientRegistered(const int& clientSocket, Server* server);
			static void removeClient(int clientSocket, IRC::Server* server);
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif