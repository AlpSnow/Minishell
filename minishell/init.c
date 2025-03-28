
#include "minishell.h"

/*
   init_minishell initialise l'environnement du shell.
   Si la variable d'environnement MINISHELL_NESTED existe,
   cela signifie que l'instance est imbriquée et nous
   ignorons SIGINT pour éviter que CTRL+C ne soit géré
   dans chaque instance. Sinon, nous sommes dans le shell
   principal et nous installons notre handler personnalisé.
*/

int init_minishell(char **envp, t_data *data)
{
	signal(SIGINT, sigint_handler); // gérer CTRL+C
	signal(SIGQUIT, SIG_IGN);       // ignorer CTRL+
	data->env = copy_env(envp);
	if (data->env == NULL)
		return (write (2, ERROR_ENV, 45), 1);
	return (0);
}


char *increase_shlvl(char *shlvl_line)
{
    int shlvl;
    char *lvl_str;
    char *new_shlvl;

    shlvl = ft_atoi(shlvl_line + 6);
    shlvl++;
    lvl_str = ft_itoa(shlvl);
    if (!lvl_str)
        return (NULL);
    new_shlvl = ft_strjoin("SHLVL=", lvl_str);
    free(lvl_str);
    return (new_shlvl);
}

char **copy_env(char **envp)
{
    char    **env;
    int     i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    env = malloc(sizeof(char *) * (i + 1));
    if (env == NULL)
        return (NULL);
    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
        {
            env[i] = increase_shlvl(envp[i]);
            if (!env[i])
            {
                while (i > 0)
                    free(env[--i]);
                free(env);
                return (NULL);
            }
        }
        else
        {
            env[i] = ft_strdup(envp[i]);
            if (env[i] == NULL)
            {
                while (i > 0)
                    free(env[--i]);
                free(env);
                return (NULL);
            }
        }
        i++;
    }
    env[i] = NULL;
    return (env);
}

/* Gestionnaire de SIGINT : il enregistre le signal dans la variable
   globale et rafraîchit le prompt via readline. */
void sigint_handler(int signum)
{
    (void)signum;
    write(1, "\n", 1);
    rl_on_new_line();       // readline sait qu'une ligne vide commence
    rl_replace_line("", 0); // efface la ligne en cours
    rl_redisplay();         // réaffiche le prompt
}
