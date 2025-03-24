/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <mwallis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:00:39 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/21 01:01:31 by mwallis          ###   ########.fr       */
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



void	free_env(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	free_input_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
		free(tab[i++]);
	free(tab);
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





	// A supprimer c'etait juste pour tester l'environnement
    // ✅ Test d'affichage de l’environnement copié
    //for (int i = 0; data.env[i]; i++)
    //    printf("%s\n", data.env[i]);




	signal(SIGINT, sigint_handler); // gérer CTRL+C
	signal(SIGQUIT, SIG_IGN);       // ignorer CTRL+ 

	while (1)
	{
		input_line = readline(prompt = get_prompt());
		free(prompt);
		if (!input_line)
		{
			write(1, "exit\n", 5);
			free_env(data.env);
			exit(0);
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
			free_input_tab(input_tab);
			continue;
		}

		if (fork() == 0)
		{
			signal(SIGINT, SIG_DFL);   // la commande doit pouvoir être interrompue
			signal(SIGQUIT, SIG_DFL);  // idem pour CTRL+ 
			execvp(input_tab[0], input_tab);
			perror("minishell");
			exit(1);./
		}
		wait(&status);

		free(input_line);
		free_input_tab(input_tab);
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
