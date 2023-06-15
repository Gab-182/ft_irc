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
			std::string _host;
			std::string _userName;
			std::string _realName;
			std::string _nickName;
			bool _isRegistered;
		public:
			Client();
			~Client();
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄︎  SETTERS && GETTERS  ❄❄︎❄❄︎❄︎❄❄︎❄❄❄︎❄*/
			void setSocket(const int& socket);
			void setHost(const std::string& host);
			void setUserName(const std::string& userName);
			void setRealName(const std::string& realName);
			void setNickName(const std::string& nickName);
			void setIsRegistered(bool isRegistered);
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
			int getSocket() const;
			std::string getUserName();
			std::string getRealName();
			std::string getNickName();
			std::string getHost();
			bool getIsRegistered() const;
		/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
	};
}
/*-------------------------------------------------------------------------------------------------------------*/
#endif