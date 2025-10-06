NAME = minishell

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

GNL_DIR = get_next_line
GNL_A = $(GNL_DIR)/get_next_line.a
GNL_HEADER = -I$(GNL_DIR)

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
    exec/ft_unset.c

OBJ = $(SRC:.c=.o)

CFLAGS += -g -I$(LIBFT_DIR) $(GNL_HEADER) -Wall -Wextra -Werror #-fsanitize=address

all: $(NAME)

$(NAME): $(LIBFT_A) $(GNL_A) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT_A) $(GNL_A) -lreadline -o $(NAME)

$(LIBFT_A):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(GNL_A):
	$(MAKE) -C $(GNL_DIR)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(GNL_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)

re: fclean all