.SUFFIXES:	.cpp .o

SRCS_N		= main Client Channel Ch_client Message Server Reply util_funcs Tcpflow

SRCS_C		= Mode_cmd Command

SRCS		= $(addprefix ./src/, $(addsuffix .cpp, $(SRCS_N))) $(addprefix ./src/Commands/, $(addsuffix .cpp, $(SRCS_C)))

OBJS		= $(SRCS:.cpp=.o)

INC			= -I./include

NAME		= ircserv

CC			= c++
#CFLAGS		= -Wextra -Wall -Werror -std=c++98 -g
CFLAGS		= -Wextra -Wall -Werror -std=c++98 -g3 -fsanitize=address

.cpp.o:		$(OBJS)
			${CC} $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			${CC} $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			
			make fclean
			make -j8 all

.PHONY:		clean all fclean re
