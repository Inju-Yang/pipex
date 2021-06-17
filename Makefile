
NAME			=	pipex
CC				=	gcc
CFLAGS_42		=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS			=	rcs
RM				=	rm -rf

PIPEX_F			=	./pipex.c\

PIPEX_O			=	./pipex.o\

LIBFT_D			=	./assets/libft/
LIBFT_A			=	./assets/libft/libft.a

.PHONY:	all clean fclean re bonus

all: $(NAME)

bonus: $(CHECK_NAME)

$(NAME): $(PIPEX_O)
	$(CC) $(CFLAGS_42) $(PIPEX_F)
	mv a.out $(NAME)

.c.o:
	$(CC) $(CFLAGS_42) -c -o $@ $<

clean:
	$(RM) $(PIPEX_O) $(NAME)

fclean: clean
	$(RM) out

re:	fclean all