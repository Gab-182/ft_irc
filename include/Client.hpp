#ifndef CLIENT_HPP
#define CLIENT_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include <iostream>
#include <cstring>

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class Client {
		private:
			int _socket;
			std::string _userName;
			std::string _nickName;
//			std::string _realName;
//			std::string _host;
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
		/*--------------------------------------------------------*/
			int getSocket() const;
			std::string getUserName();
			std::string getNickName();
		/*--------------------------------------------------------*/
	};
}
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif