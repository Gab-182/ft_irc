#ifndef CLIENT_HPP
#define CLIENT_HPP

/*-------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <cstring>

/*-------------------------------------------------------------------------------------------------------------*/
namespace IRC {
	class Client {
		private:
			int _socket;
			std::string _userName;
			std::string _nickName;
			bool _isRegistered;
		public:
			Client();
			Client(int socket);
			~Client();
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎  SETTERS && GETTERS  ❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄*/
			void setSocket(const int& socket);
			void setUserName(const std::string& userName);
			void setNickName(const std::string& nickName);
			void setIsRegistered(bool isRegistered);
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
			int getSocket() const;
			std::string getUserName();
			std::string getNickName();
			bool getIsRegistered() const;
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
	};
}
/*-------------------------------------------------------------------------------------------------------------*/
#endif