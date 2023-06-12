#❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄
NAME = ircserv

INCLUDE_DIR := ./include

SRC = main.cpp \
		src/server/server.cpp \
		src/handShake/HandShake.cpp \
		src/channel/Channel.cpp \
		src/client/Client.cpp \
		src/commands/Commands.cpp \

OBJ = $(SRC:.cpp=.o)

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -g3 -std=c++98 -I$(INCLUDE_DIR)

RM = rm -rf

.DEFAULT_GOAL := help

.PHONY: all clean fclean re help

#irssi:
#	cd irssi/ && docker build -t irssi . &&\
#	docker run -it --rm -e TERM -e COLUMNS -e LINES irssi

all: $(NAME) irssi

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)


clean:
	$(RM) $(OBJ)
#	docker rmi irssi

fclean: clean
	$(RM) $(NAME)
#	docker irssi prune -f

re: fclean all


help:
	@echo "\n\033[1;32mAvailable rules:\033[0m"
	@echo "  \033[1;36mall\033[0m       : Compile and build IRC server"
#	@echo "  \033[1;36mirssi\033[0m     : Compile and build irssi client"
	@echo "  \033[1;36mclean\033[0m     : Remove object files"
	@echo "  \033[1;36mfclean\033[0m    : Remove object files and executable"
	@echo "  \033[1;36mre\033[0m        : Clean and rebuild the executable"

#❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄❄︎❄