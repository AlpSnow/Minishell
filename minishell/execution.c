
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

	if (is_build_in(cmd_arg[0]))
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
			exec_extern(cmd_arg, data);
			perror("command not found");
			exit(1);
		}
	}
	return (0);
}
int exec_extern(char **arg, t_data *data)
{
	char *exec_path;
	char **env_paths;
	int i;

	if (arg[0][0] == '/' || (arg[0][0] == '.' && arg[0][1] == '/'))
		execve(arg[0], arg, data->env);
	else
	{
		i = 0;
		env_paths = ft_split(getenv("PATH"), ':');
		if (!env_paths)
			return (0);
		while(env_paths[i])
		{
			exec_path = add_chr('/',env_paths[i]);
			exec_path = ft_strjoin(exec_path, arg[0]);
			//access ? flag ?
			//strlcopy
			//free path
			execve(exec_path, arg, data->env);
			i++;
		}
	}
	free_tab(env_paths);
	return(0);
}
