# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	pipex

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

LIBFTDIR	:=	libft

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			:=	pipex.c			\
				error.c			\
				execute.c		\
				utils.c

HEADER		:=	pipex.h

MAKE		:=	Makefile

OBJS		:=	$(SRC:%.c=%.o)

LIB			:=	$(LIBFTDIR)/libft.a

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			:=	-cc

CFLAGS		:=	-Werror -Wextra -Wall -Wunreachable-code -pthread -g -fsanitize=address

INCLUDE		:=	-I

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE)$(LIBFTDIR) -c $< -o $@

$(NAME): $(OBJS) $(SRCS) Makefile $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

make_libft:
	make -C libft

clean:
	/bin/rm -f $(OBJS)
	make clean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB)

re: fclean all

.PHONY:  all clean fclean re make_libft
