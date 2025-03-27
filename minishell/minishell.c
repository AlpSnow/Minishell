/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:00:39 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/25 20:48:08 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int global_interrupted = 0;

char **get_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		env[i] = ft_strdup(envp[i]);
		if (env[i] == NULL)
		{
			while (i > 0)
				free(env[--i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	sigint_handler(int signum)
{
	(void)signum;
	global_interrupted = 1;
	write(1, "\n", 1);
	rl_on_new_line();       // readline sait qu'une ligne vide commence
	rl_replace_line("", 0); // efface la ligne en cours
	rl_redisplay();         // réaffiche le prompt
}

int	main(int argc, char **argv, char **envp)
{
	char	*input_line;
	char	**input_tab;
	int		status;
	t_data	data;
	char *prompt;

	(void)argv;
	if (argc != 1)
		return (write (2, ERROR_ARGC, 58), 1);

	data.env = get_env(envp);
	if (data.env == NULL)
		return (write (2, ERROR_ENV, 45), 1);
	signal(SIGINT, sigint_handler); // gérer CTRL+C
	signal(SIGQUIT, SIG_IGN);       // ignorer CTRL+

	while (1)
	{
		global_interrupted = 0;
		input_line = readline(prompt = get_prompt());
		free(prompt);

		/*
		int fd = open ("valgrind.supp", O_RDONLY);
		char *gnl = get_next_line(fd);
		printf("%s", gnl);
		*/


		if (input_line == NULL)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			free_tab(data.env);
			exit(0);
		}
		if (global_interrupted == 1)
		{
			free(input_line);
			continue;
		}
		if (input_line[0] == '\0')
		{
			free(input_line);
			continue;
		}
		add_history(input_line);
		input_tab = ft_split(input_line, ' ');
		if (!input_tab || !input_tab[0])
		{
			free(input_line);
			free_tab(input_tab);
			continue;
		}
		exec_command(input_tab, &data);
		wait(&status);
		free(input_line);
		free_tab(input_tab);
	}


/*
	int fd = open ("valgrind.supp", O_RDONLY);
	char *gnl = get_next_line(fd);
	printf("%s", gnl);
*/
	return (0);
}
