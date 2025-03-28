
#include"minishell.h"

int is_build_in(char *name)//verifie si un argument est une fonctions built in et renvoie son ID
{
	if (!ft_strcmp("exit", name))
		return (1);
	if (!ft_strcmp("export", name))
		return (1);
	// a completer au fur et a mesure
	else
		return (0);
}

void built_in_exec(char **arg, t_data *data)//execute les fonctions build in si elle doit l'etre,  //A MERGE AVEC IS BUILT IN ?
{
	if (!strcmp("exit", arg[0]))
		bi_exit(arg, data);
	if (!strcmp("export", arg[0]))
		bi_export(arg, data);
}

int exec_command(char **cmd_arg, t_data *data)
{
    pid_t pid;
    int   status;

    // Si c'est un built-in, on l’exécute direct
    if (is_build_in(cmd_arg[0]))
    {
        built_in_exec(cmd_arg, data);
        return (0);
    }



    // Sinon, avant le fork, on teste si la commande est "./minishell"
    if (ft_strcmp(cmd_arg[0], "./minishell") == 0)
    {
        pid = fork();
        if (pid < 0)
            return (perror("fork"), 1);
        if (pid == 0)
        {
            // -- ENFANT --
            // “bonne pratique” ou “vraie shell robustesse”, il est généralement conseillé de remettre tout en SIG_DFL avant de lancer un programme inconnu
            // Mais on peut s'en passer. C'est simplement une bonne pratique
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            execve("./minishell", cmd_arg, data->env);
            // Si on arrive ici, erreur
            perror("execve");
            exit(127);
        }
        else
        {
            // -- PARENT --
            // On IGNORE ctrl-C dans le parent tant que le 2e shell est actif
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);

            waitpid(pid, &status, 0);

            // Quand le second shell se termine, on rétablit la gestion
            // du SIGINT pour le parent (s’il doit enchaîner d’autres commandes).
            signal(SIGINT, sigint_handler);
            signal(SIGQUIT, SIG_IGN);
        }
    }
    else
    {
        // comportement normal d’exécution d’une commande externe
        pid = fork();
        if (pid < 0)
            return (perror("fork"), 1);
        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            exec_extern(cmd_arg, data);
        }
        else
        {
        	// Parent : ignore SIGINT pendant l'exécution du fils (probleme cat par exemple)
        	signal(SIGINT, SIG_IGN);
        	signal(SIGQUIT, SIG_IGN);

            waitpid(pid, &status, 0);

            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
                write(1, "\n", 1);

            // Rétablir le handler pour le parent
            signal(SIGINT, sigint_handler);
            signal(SIGQUIT, SIG_IGN);
        }
    }
    return (0);
}


void exec_extern(char **arg, t_data *data)
{
	char *exec_path;
	char **env_paths;
	int i;

	if (arg[0][0] == '/' || (arg[0][0] == '.' && arg[0][1] == '/'))
		execve(arg[0], arg, data->env);
	else
	{
		i = 0;
		env_paths = ft_split(get_env("PATH", data->env), ':');
		if (!env_paths)
			error_exit("Path error", -1, NULL);
		while(env_paths[i])
		{
			exec_path = add_chr('/',env_paths[i]);
			exec_path = ft_str_realoc(exec_path, arg[0]);
			execve(exec_path, arg, data->env);
			i++;
		}
	}
	error_exit(arg[0], 126, (void *)arg);
}
