/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:00:39 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/26 13:45:37 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		input_line = readline(prompt = get_prompt());
		free(prompt);
		if (!input_line)
			mini_exit(5, &data);
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

	return (0);
}

char	*get_prompt(void)
{
	char	*user;
	char	*host;
	char	*cwd;
	char	*prompt;
	char	*tmp;

	user = getenv("USER");         // nom d'utilisateur
	host = getenv("HOSTNAME");     // nom de la machine
	if (!host) {
		char hostname[256];
		gethostname(hostname, sizeof(hostname));
		host = hostname;
	}
	cwd = getcwd(NULL, 0);         // répertoire courant

	// Si on est dans le home, affiche ~
	char *home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		cwd = tmp;
	}

	tmp = ft_strjoin(user, "@");
	prompt = ft_strjoin(tmp, host);
	free(tmp);

	tmp = ft_strjoin(prompt, ":");
	free(prompt);
	prompt = ft_strjoin(tmp, cwd);
	free(tmp);
	free(cwd);

	tmp = prompt;
	prompt = ft_strjoin(prompt, "$ ");
	free(tmp);

	return (prompt);
}


