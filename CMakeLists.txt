cmake_minimum_required(VERSION 3.25)
project(ft_irc)

set(CMAKE_CXX_STANDARD 98)

# Set the source files for your project
set(SOURCES
		main.cpp
		src/server/server.cpp
		src/parser/HandShake.cpp
		src/client/Client.cpp
		src/commands/Commands.cpp
		src/interface/IrcInterface.cpp
		)

# Set the header files for your project
set(HEADERS
		include/Server.hpp
		include/Client.hpp
		include/HandShake.hpp
		src/interface/IrcInterface.hpp
		)

# Create an executable target and link the source and header files
add_executable(ircserv ${SOURCES} ${HEADERS})

# Define custom target for running the executable with arguments
add_custom_target(run
		COMMAND ircserv 1212 12345
		DEPENDS ircserv
		WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
		)
