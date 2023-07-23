# Color variables
RESET = \033[0m
BOLD = \033[1m
GREEN = \033[1;32m
CYAN = \033[1;36m
YELLOW = \033[33m
BLUE = \033[94m


NAME = ircserv

INCLUDE_DIR := ./include

SRC =	main.cpp \
		\
		src/server/server.cpp \
		src/channel/Channel.cpp \
		src/client/Client.cpp \
		\
		src/commands/ICommands.cpp \
		src/commands/JoinCommand.cpp \
		src/commands/NickCommand.cpp \
		src/commands/UserCommand.cpp \
		src/commands/WhoisCommand.cpp \
		src/commands/ModeCommand.cpp \
		src/commands/PassCommand.cpp \
		src/commands/PingCommand.cpp \
		src/commands/CapCommand.cpp \
		src/commands/QuitCommand.cpp \
		src/commands/PrivMsgCommand.cpp \
		src/commands/PartCommand.cpp \
		src/commands/KickCommand.cpp \
		src/commands/OperCommand.cpp \

OBJ = $(SRC:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -g3 -std=c++98 -I$(INCLUDE_DIR)

RM = rm -rf

all: $(NAME) irssi

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)


clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

leaks:
	valgrind --log-file=valgrind_output.txt ./ircserv 1212 1

# Target rules
.PHONY: all clean fclean re leaks

# Help message
help:
	@echo ""
	@echo "$(BOLD)Available rules:$(RESET)"
	@echo "  $(CYAN)all$(RESET)\t\t: Compile and build IRC server"
	@echo "  $(CYAN)clean$(RESET)\t\t: Remove object files"
	@echo "  $(CYAN)fclean$(RESET)\t: Remove object files and executable"
	@echo "  $(CYAN)re$(RESET)\t\t: Clean and rebuild the executable"
	@echo "  $(CYAN)leaks$(RESET)\t\t: Run valgrind to check for leaks"
	@echo ""
	@echo "$(YELLOW)Note:$(RESET)"
	@echo "$(BLUE)\tThe 'make leaks' rule will create a valgrind_output.txt file and"
	@echo "\trun the server on port 1212 with the password 1."
	@echo "\tIf you want to run the server on another port or with another password,"
	@echo "\tyou will need to modify the Makefile."
	@echo ""

# Default rule
.DEFAULT_GOAL := all
#❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄