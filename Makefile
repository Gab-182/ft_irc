
SRC =	main.cpp server.cpp

OBJ = ${SRC:.cpp=.o}

NAME = serv

CXX = c++

CXXFLAGS =  -Wall -Werror -Wextra -std=c++98

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