#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#include <exception>
#include <string>

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
namespace IRC {
	class IRCServerException : public std::exception {
	public:
		IRCServerException() { }
		~IRCServerException() { }
		explicit IRCServerException(const std::string& message) : message_(message) {}

		const char* what() const {
			return message_.c_str();
		}

	private:
		std::string message_;
	};
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
	class AuthErrorException : public IRCServerException {
	public:
		explicit AuthErrorException(const std::string& message) : IRCServerException(message) {}
	};

	class WrongParametersException : public IRCServerException {
	public:
		explicit WrongParametersException(const std::string& message) : IRCServerException(message) {}
	};
/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
}

/*————————————————————————————--------------------------------------------------------------——————————————————————————*/
#endif // EXCEPTIONS_HPP
