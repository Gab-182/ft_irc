#ifndef COMMANDS_HPP
#define COMMANDS_HPP

/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/
#define DEBUG 1

#if( DEBUG == 1 )
#define DEBUG_MSG(msg) std::cout														\
						<< BOLDMAGENTA												\
						<< "⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⫷⦙⧛ 𝙳𝙴𝙱𝚄𝙶 ⧚⦙⫸︎⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯"	\
						<< std::endl												\
						<< BOLDCYAN << msg << RESET									\
						<< std::endl												\
						<< BOLDMAGENTA												\
						<< "⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯⎯"		\
						<< RESET << std::endl;
#elif( DEBUG == 0 )
#define DEBUG_MSG(msg)

#endif
/*❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄*/

namespace IRC {
	class Commands {
		public:
			Commands();
			~Commands();
			/*—————————————————————————————————⟪⟪ Commands ⟫⟫———————————————————————————————*/
			void sendCommand(int client_socket, const std::string& message);
			void Commands::join(int clientSocket, const std::string& channel);
			void Commands::part(int clientSocket, const std::string& channel);
//			void privmsg(const std::string& target, const std::string& message);
//			void Commands::notice(const std::string& target, const std::string& message);
//			void Commands::quit(const std::string& message);
//			void Commands::nick(const std::string& nickname);
//			void Commands::oper(const std::string& name, const std::string& password);
//			void Commands::mode(const std::string& target, const std::string& mode);
//			void Commands::topic(const std::string& channel, const std::string& topic);
//			void Commands::kick(const std::string& channel, const std::string& user, const std::string& comment);
//			void Commands::invite(const std::string& nickname, const std::string& channel);
	};
}


#endif //COMMANDS_HPP
