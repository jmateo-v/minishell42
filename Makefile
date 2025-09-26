NAME = minishell
LIBFT_A = libft/libft.a
SRC = minishell.c\
	parsing/lexing.c\
	parsing/lexing1.c\
	parsing/utils.c\
	parsing/parsing.c\
	parsing/parsing1.c\
	parsing/expansion.c\
	parsing/heredoc.c\
	parsing/signals.c\
	parsing/shenv.c\
	parsing/wildcards.c\
	parsing/wc_utils.c\
	lexing/new_lexing.c\
	exec/builtins.c\
	exec/exec.c\
	exec/exec_pipe.c\
	exec/ft_cd.c\
	exec/ft_export.c\
	exec/ft_unset.c\

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