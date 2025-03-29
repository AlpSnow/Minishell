/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:00:39 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/28 18:14:25 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char	*input_line;
	char	**input_tab;
	//int		status;
	t_data	data;
	char *prompt;

	(void)argv;
	if (argc != 1)
		return (write (2, ERROR_ARGC, 58), 1);
	if(init_minishell(envp, &data))
		return (-1);
	while (1)
	{
		input_line = readline(prompt = get_prompt(&data));
		free(prompt);
		if (input_line == NULL)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			free_tab(data.env);
			exit(0);
		}

		if (input_line[0] == '\0')
		{
			free(input_line);
			continue;
		}
		add_history(input_line);

		//debut fonction lexer;
		//fonction check les erreurs;

		input_tab = ft_split(input_line, ' ');
		if (!input_tab || !input_tab[0])
		{
			free(input_line);
			free_tab(input_tab);
			continue;
		}
		exec_command(input_tab, &data);
		free(input_line);
		free_tab(input_tab);
	}

	return (0);
}
