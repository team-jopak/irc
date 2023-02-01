.SUFFIXES:	.cpp .o

SRCS_N		= main Client Channel Server util_funcs

SRCS_F		= $(addsuffix .cpp, $(SRCS_N))

SRCS		= $(addprefix ./src/, $(SRCS_F))

OBJS		= $(SRCS:.cpp=.o)

INC			= -I./include

NAME		= ircserv

CC			= c++
CFLAGS		= -Wextra -Wall -Werror -std=c++98 -g

.cpp.o:		$(OBJS)
			${CC} $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			${CC} $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			clean all

.PHONY:		clean all fclean re