
SRC =	main.cpp \
		server.cpp\
		./parser/MsgParser.cpp\

OBJ = ${SRC:.cpp=.o}

NAME = ircserv

CXX = c++

CXXFLAGS =  -Wall -Werror -Wextra -g3 -std=c++98

RM = rm -rf

all : ${NAME}

${NAME} : ${OBJ}
		${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

clean : 
		${RM} ${OBJ}

fclean : clean
		${RM} ${NAME}
 
re : fclean all

.PHONY: clean fclean all re