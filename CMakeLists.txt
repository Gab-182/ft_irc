cmake_minimum_required(VERSION 3.25)
project(ft_irc)

set(CMAKE_CXX_STANDARD 98)

# Set the source files for your project
set(SOURCES
		main.cpp
		src/server/server.cpp
		src/client/Client.cpp
        src/commands/JoinCommand.cpp
		)

# Set the header files for your project
set(HEADERS
		include/IRC.hpp
		include/Server.hpp
		include/Client.hpp
		src/channel/Channel.cpp main.cpp src/commands/ICommands.cpp include/commands/NickCommand.hpp src/commands/NickCommand.cpp src/commands/UserCommand.cpp src/commands/WhoisCommand.cpp include/commands/WhoisCommand.hpp include/commands/ModeCommand.hpp src/commands/ModeCommand.cpp src/commands/PassCommand.cpp src/commands/PingCommand.cpp src/commands/CapCommand.cpp src/commands/QuitCommand.cpp)

# Create an executable target and link the source and header files
add_executable(${SOURCES} ${HEADERS})

# Define custom target for running the executable with arguments
add_custom_target(run
		COMMAND ircserv 1212 12345
		DEPENDS ircserv
		WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
		)
