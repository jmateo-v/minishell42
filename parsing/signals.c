#include "../minishell.h"

void    ft_sig_int(int signal)
{
	char nl;

	nl = '\n';
    g_sigint_received = 1;
	if (signal == SIGINT)
		write(1, "^C", 2);
    ioctl(STDIN_FILENO, TIOCSTI, &nl);
}

/* void    ft_set_sig(int option)
{
    struct sigaction        sa;

    ft_memset(&sa, 0, sizeof(sa));
    if (option == PARENT)
    {
        sa.sa_handler = ft_sig_int;
        sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
        sigaction(SIGQUIT, &sa, NULL);
    }
    else if (option == CHILD)
    {
        sa.sa_handler = SIG_DFL;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
	}
    else if (option == IGNORE)
    {
        sa.sa_handler = SIG_IGN;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
    }
	return ;
}*/
void ft_set_sig(int option)
{
    struct sigaction sa;

    if (option == PARENT)
    {
        ft_memset(&sa, 0, sizeof(sa));
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = ft_sig_int;
        sigaction(SIGINT, &sa, NULL);

        ft_memset(&sa, 0, sizeof(sa));
        sa.sa_flags = 0;
        sa.sa_handler = SIG_IGN;
        sigaction(SIGQUIT, &sa, NULL);
    }
    else if (option == CHILD)
    {
        ft_memset(&sa, 0, sizeof(sa));
        sa.sa_flags = 0;
        sa.sa_handler = SIG_DFL;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
    }
    else if (option == IGNORE)
    {
        ft_memset(&sa, 0, sizeof(sa));
        sa.sa_flags = 0;
        sa.sa_handler = SIG_IGN;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
    }
}