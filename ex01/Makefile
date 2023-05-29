SRC			=	\
main.cpp	\
RPN.cpp \

INC			= \
RPN.hpp \

NAME		=	RPN

INCDIR	=	./includes
INCS		= $(addprefix ${INCDIR}/,${INC})

SDIR		=	./src
SRCS		=	$(addprefix ${SDIR}/,${SRC})
ODIR		=	./out
OBJS		=	$(patsubst ${SDIR}/%,${ODIR}/%,${SRCS:.cpp=.o})

CC			=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98 -I ${INCDIR}
RM			=	rm -rf

all: ${NAME}

${ODIR}/%.o: ${SDIR}/%.cpp ${INCS} Makefile
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -c $< -o $@ -g3

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${ODIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
