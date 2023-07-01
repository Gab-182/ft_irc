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
			bool operator==(const Client& other) const;

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
			bool isMemberInChannel(Client* client, const std::string& channelName);
			bool isOperatorOfChannel(Client* client, const std::string& channelName);
			bool isInvitedToChannel(Client* client, const std::string& channelName);
			bool isBannedFromChannel(Client* client, const std::string& channelName);

		/*------------------------------------------------------------------------------*/
			void addChannelToClientChannelsMap(Channel* channel);
			void removeChannelFromClientChannelsMap(const std::string& channelName);

		/*------------------------------------------------------------------------------*/
//			void removeClientFromAllChannels(Client* client);
//			void removeClientFromServer(const int& clientSocket, Server* server, Client* client);

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