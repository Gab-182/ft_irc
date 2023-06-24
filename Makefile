NAME = ircserv

INCLUDE_DIR := ./include

SRC = main.cpp \
		src/server/server.cpp \
		src/channel/Channel.cpp \
		src/client/Client.cpp \
		src/handShake/HandShake.cpp \
		\
		src/commands/ICommands.cpp \
		src/commands/JoinCommand.cpp \
		src/commands/NickCommand.cpp \
		src/commands/UserCommand.cpp \
		src/commands/WhoisCommand.cpp \

OBJ = $(SRC:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -g3 -std=c++98 -I$(INCLUDE_DIR)

RM = rm -rf

.DEFAULT_GOAL := help

.PHONY: all clean fclean re help

all: $(NAME) irssi

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)


clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


help:
	@echo "\n\033[1;32mAvailable rules:\033[0m"
	@echo "  \033[1;36mall\033[0m       : Compile and build IRC server"
	@echo "  \033[1;36mclean\033[0m     : Remove object files"
	@echo "  \033[1;36mfclean\033[0m    : Remove object files and executable"
	@echo "  \033[1;36mre\033[0m        : Clean and rebuild the executable"

#❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄