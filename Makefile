
NAME			=	pipex
CC				=	gcc
CFLAGS_42		=	-Wall -Wextra -Werror
RM				=	rm -rf

PIPEX_C			=	pipex.c\
					pipex_utils.c

PIPE_B_C		=	bonus/pipex_bonus.c\
					bonus/pipex_utils_bonus.c\
					bonus/pipex_gnl.c\
					bonus/heredoc_bonus.c\
					bonus/multi_bonus.c

PIPEX_O			=	$(PIPEX_C:.c=.o)
PIPE_B_O		=	$(PIPE_B_C:.c=.o)

LIBFT_D			=	./libft/
LIBFT_A			=	./libft/libft.a

.PHONY:	all clean fclean re bonus

all: $(NAME)

$(NAME): $(PIPEX_O)
	make -C $(LIBFT_D)
	$(CC) $(CFLAGS_42) $(LIBFT_A) $(PIPEX_C)
	mv a.out $(NAME)

bonus: fclean $(PIPE_B_O)
	make -C $(LIBFT_D)
	$(CC) $(CFLAGS_42) $(LIBFT_A) $(PIPE_B_C)
	mv a.out $(NAME)

.c.o:
	$(CC) $(CFLAGS_42) -c -o $@ $<

clean:
	$(RM) $(PIPEX_O) $(PIPE_B_O) $(NAME)

fclean: clean
	$(RM) out tmp
	make fclean -C $(LIBFT_D)

re:	fclean all