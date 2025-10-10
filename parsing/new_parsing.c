#include "../minishell.h"

void ft_trunc(char *filename, t_cli *cli)
{
	if (cli->outfile)
		free(cli->outfile);
	cli->outfile = ft_strdup(filename);
	cli->r_mode = WRITE;
    cli->breaks_pipe = true;
}

int is_operator(const char *s)
{
    return (
        strcmp(s, "|") == 0 ||
        strcmp(s, "||") == 0 ||
        strcmp(s, "&&") == 0
    );
}



int	ft_new_parse(t_token *tokens, t_cli *cli)
{
	int		i;
	int		len;
	int		group;

	if (!tokens || !cli)
		return (2);
	i = 0;
	group = 1;
	len = ft_token_count(tokens);
	cli->n_tokens = 1;
	while (i < len)
	{
		if (!tokens[i].value)
		{
			i++;
			continue;
		}
		if (tokens[i].value && !ft_strncmp(tokens[i].value, ">>", 2))
		{
			if (i + 1 >= len)
				return(perror("missing target for >>, SYN ERR"), ft_free_tokens(tokens), 2);
			ft_append(tokens[i + 1].value, cli);
			i += 2;
			continue;
		}
		else if (tokens[i].value[0] != '\0' && strcmp(tokens[i].value, "<<") == 0)
		{
			if (i + 1 >= len)
            	return (ft_perror("missing target for <<", SYN_ERR), ft_free_tokens(tokens), 2);
        	if (ft_heredoc(tokens[i + 1].value, cli) == 130)
            return (ft_free_tokens(tokens), 130);
        	i += 2;
        	continue;
		}
        else if (tokens[i].value && !ft_strncmp(tokens[i].value, ">", 1) && ft_strlen(tokens[i].value) == 1)
{
	if (i + 1 >= len)
		return (ft_perror("missing target for >", SYN_ERR), ft_free_tokens(tokens), 2);
	ft_trunc(tokens[i + 1].value, cli);
	i += 2;
	continue;
}
else if (tokens[i].value && !ft_strncmp(tokens[i].value, "<", 1) && ft_strlen(tokens[i].value) == 1)
{
	if (i + 1 >= len)
		return (ft_perror("missing target for <", SYN_ERR), ft_free_tokens(tokens), 2);
	ft_infile(tokens[i + 1].value, cli);
	i += 2;
	continue;
}
		else if (tokens[i].value && is_operator(tokens[i].value))
		{
			cli->next = ft_parse_op(tokens[i].value, cli);
			if (!cli->next)
				return (2);
			cli = cli->next;
		}
		else
			ft_parse_token(tokens, i, cli, &group);
        i++;
	}
	return (0);
}