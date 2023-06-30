#ifndef CLIENT_HPP
#define CLIENT_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include <iostream>
#include <cstring>
#include <map>

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	// Forward declarations:
	class Server;
	class Channel;

	class Client {
		private:
			int _socket;
			std::string _userName;
			std::string _nickName;

			// true if the server sent welcome message to the client.
			// false by default.
			bool _isWelcomed;
			/**
			 **	map of all the channels that the client is in:
			 **		key: channel name
			 **		value: pointer to the channel object.
			 **/
			std::map<std::string, Channel*> _clientChannelsMap;
			
		/*------------------------------------------------------------------------------*/
		public:
			Client();
			~Client();
			explicit Client(int socket);
			Client(const Client& other);
			Client& operator=(const Client& other);

		/*------------------------------------------------------------------------------*/
			void setSocket(const int& socket);
			void setUserName(const std::string& userName);
			void setNickName(const std::string& nickName);
			void welcomeClient(bool welcome);

		/*------------------------------------------------------------------------------*/
			int getSocket() const;
			std::string getUserName();
			std::string getNickName();
			bool isWelcomed() const;

		/*------------------------------------------------------------------------------*/
			bool isClientInChannel(const std::string& channelName);
			bool isOperatorOfChannel(const int& clientSocket, const std::string& channelName);
			bool isInvitedToChannel(const int& clientSocket, const std::string& channelName);
			bool isBannedFromChannel(const int& clientSocket, const std::string& channelName);

		/*------------------------------------------------------------------------------*/
			static void addClientToServer(const int& clientSocket, Server* server);
			void addClientToChannel(Client* client, const std::string& channelName, Channel* channel);

			void removeClientFromChannel(Client* client, Channel* channel);
			void removeClientFromAllChannels(Client* client);
			void removeClientFromServer(const int& clientSocket, Server* server, Client* client);

		/*------------------------------------------------------------------------------*/
			static void sendResponse(int clientSocket, const std::string& message);
			static bool isClientAuthenticated(const int& clientSocket, Server* server);
			static bool isClientRegistered(const int& clientSocket, Server* server);
			static void removeClient(int clientSocket, IRC::Server* server);

		/*------------------------------------------------------------------------------*/
			void printClientChannelsMap();
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif