
#include"minishell.h"

int is_build_in(char *name)//verifie si un argument est une fonctions built in et renvoie son ID
{
	if (!ft_strcmp("exit", name))
		return (1);
	// a completer au fur et a mesure
	else
		return (0);
}

void built_in_exec(char **arg, t_data *data)//execute les fonctions build in si elle doit l'etre,
{
	if (!strcmp("exit", arg[0]))
		bi_exit(arg, data);
}

int exec_command(char **cmd_arg, t_data *data)
{
	pid_t	pid;

	if(is_build_in(cmd_arg[0]))
		built_in_exec(cmd_arg, data);
	else
	{
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			return(1);
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);   // la commande doit pouvoir être interrompue
			signal(SIGQUIT, SIG_DFL);  // idem pour CTRL+
			execvp(cmd_arg[0], &cmd_arg[0]); // !!A remplacer par execvpe
			perror("command not found");
			exit(1);
		}
	}
	return (0);
}
