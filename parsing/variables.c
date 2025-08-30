#include "../minishell.h"

char	**ft_load_env(char **envp)
{
	int		i;
	int		len;
	char	**env;

	if (!envp)
		return (NULL);
	len = ft_doubleptr_len((void **)envp);
	env = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!env)
		return (perror("malloc: "), NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}