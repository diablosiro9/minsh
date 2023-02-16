EXEC		=	minishell

CC			=	gcc
RM			=	rm -rf
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address

LIBFT		=	lib/libft/libft.a

GNL			=	lib/gnl/get_next_line.c

SRCS		=	./src/main.c\
				./src/utils.c\
				./src/lexer/tokenisateur.c\
				./src/exec/exec.c\
				./src/built_in/cd.c\


OBJS		=	$(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(GNL) $(LIBFT) -o $(EXEC)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(EXEC)

re: fclean all

.PHONY: all clean fclean re