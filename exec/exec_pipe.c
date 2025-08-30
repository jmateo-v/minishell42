/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:21:28 by dogs              #+#    #+#             */
/*   Updated: 2025/08/28 11:42:35 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_pipeline(t_cli *cli)
{
    t_cli *current;
    int prev_pipe;
    int pipe_fd[2];
    pid_t pid;
    bool has_next;
    int fd_in;
    int flags;
    int fd_out;
    int status;
    int last_status;
    
    last_status = 0;
    current = cli;
    prev_pipe = -1;
    ft_set_sig(IGNORE);
    while (current)
    {
        has_next = (current->next != NULL);
        if (has_next)
        {
            if(pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            ft_set_sig(DEFAULT);
            if (current->infile)
            {
                fd_in = open(current->infile, O_RDONLY);
                if (fd_in < 0)
                {
                    perror(current->infile);
                    exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            else if (prev_pipe != -1)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            if(current->outfile)
            {
                flags = O_WRONLY | O_CREAT;
                if (current->r_mode == 1)
                    flags |= O_TRUNC;
                else if (current->r_mode == 2)
                    flags |= O_APPEND;
                fd_out = open(current->outfile, flags, 0644);
                if (fd_out < 0)
                {
                    perror(current->outfile);
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            else if (has_next)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            if (prev_pipe != -1)
                close(prev_pipe);
            if (has_next)
                close(pipe_fd[0]);
            execve(current->cmd, current->args, current->env);
            perror("execve");
            exit(127);
        }
        else
        {
            if (prev_pipe != -1)
                close(prev_pipe);
            if (has_next)
            {
                close(pipe_fd[1]);
                prev_pipe = pipe_fd[0];
            }
            else
                prev_pipe = -1;         
        }
        current = current->next;
    }
    ft_set_sig(PARENT);
    while(wait(&status) > 0)
        last_status = status;
    return (WEXITSTATUS(last_status));
}