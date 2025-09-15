#include "../minishell.h"

int	ft_match_wildcard(char *token, char *wildcard)
{
	size_t	i;
	size_t	j;
	size_t	i_anchor;
	size_t	j_after_asterisk;

    if (!token || !wildcard || (token[0] == '.' && wildcard[0] != '.'))
		return (0);
    i = 0;
	j = 0;
	i_anchor = 0;
	j_after_asterisk = 0;
    while (token[i])
    {
        if (wildcard[j] == '*')
        {
			while (wildcard[j] == '*')
				j++;
			if (!wildcard[j])
				return (1);
			j_after_asterisk = j;
			i_anchor = i;
			continue;
        }
        if (wildcard[j] == token[i])
        {
			i++;
			j++;
			continue;
		}
        if (j_after_asterisk)
        {
			i_anchor++;
			i = i_anchor;
			j = j_after_asterisk;
			continue;
		}
		return (0);
    }
    while (wildcard[j] == '*')
		j++;
    return (wildcard[j] == '\0');
}