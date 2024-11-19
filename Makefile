# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	pipex

BONUS		:=	pipex_bonus

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

LIBFTDIR	:=	libft

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			:=	mandatory/pipex.c		\
				mandatory/error.c		\
				mandatory/execute.c		\
				mandatory/utils.c
				
BON			:=	bonus/pipex.c			\
				bonus/error.c			\
				bonus/execute.c			\
				bonus/utils.c

HEADER		:=	inc/pipex.h

MAKE		:=	Makefile

OBJS		:=	$(SRC:%.c=%.o)

BON_OBJS	:=	$(BON:%.c=%.o)

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
	
bonus: make_libft .bonus

.bonus: $(BON_OBJS) $(BON) Makefile $(HEADER)
	$(CC) $(CFLAGS) $(BON_OBJS) $(LIB) -o $(BONUS)

make_libft:
	make -C libft

clean:
	/bin/rm -f $(OBJS)
	/bin/rm -f $(BON_OBJS)
	make clean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(BONUS)
	make fclean -C libft

re: fclean all

.PHONY:  all clean fclean re make_libft
