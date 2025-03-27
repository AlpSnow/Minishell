/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:00:39 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/27 22:50:47 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int global_interrupted = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input_line;
	char	**input_tab;
	int		status;
	t_data	data;
	char *prompt;

	if(init_minishell(envp, &data))
		return (-1);
	(void)argv;
	if (argc != 1)
		return (write (2, ERROR_ARGC, 58), 1);
	while (1)
	{
		global_interrupted = 0;
		input_line = readline(prompt = get_prompt(&data));
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
