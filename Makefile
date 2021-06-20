
NAME			=	pipex
CC				=	gcc
CFLAGS_42		=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS			=	rcs
RM				=	rm -rf

PIPEX_F			=	./pipex.c\
					./pipex_utils.c

PIPEX_O			=	./pipex.o\
					./pipex_utils.o

LIBFT_D			=	./libft/
LIBFT_A			=	./libft/libft.a

.PHONY:	all clean fclean re bonus

all: $(NAME)

bonus: $(CHECK_NAME)

$(NAME): $(PIPEX_O)
	make -C $(LIBFT_D)
	$(CC) $(CFLAGS_42) $(LIBFT_A) $(PIPEX_F)
	mv a.out $(NAME)

.c.o:
	$(CC) $(CFLAGS_42) -c -o $@ $<

clean:
	$(RM) $(PIPEX_O) $(NAME)

fclean: clean
	$(RM) out
	make fclean -C $(LIBFT_D)

re:	fclean all