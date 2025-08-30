NAME = minishell
LIBFT_A = libft/libft.a
SRC = minishell.c parsing/lexing.c parsing/lexing1.c parsing/utils.c parsing/parsing.c parsing/expansion.c parsing/heredoc.c parsing/parsing1.c parsing/signals.c parsing/variables.c \
exec/exec.c exec/exec_pipe.c exec/builtins.c exec/ft_cd.c
OBJ = $(SRC:.c=.o)
CFLAGS += -g -Ilibft #-Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT_A) -lreadline -o $(NAME)

$(LIBFT_A):
	$(MAKE) bonus -C libft

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm  -f $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all