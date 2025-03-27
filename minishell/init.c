
#include "minishell.h"

int init_minishell(char **envp, t_data *data)
{
	signal(SIGINT, sigint_handler); // gérer CTRL+C
	signal(SIGQUIT, SIG_IGN);       // ignorer CTRL+
	data->env = get_env(envp);
	if (data->env == NULL)
		return (write (2, ERROR_ENV, 45), 1);
	return (0);
}
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
