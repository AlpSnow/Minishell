
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
/* void test_access(char *path, char **env_paths)
{
	if (access(path, F_OK) != 0)
		return;
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_tab(env_paths);
		exit(126);
	}
} */
