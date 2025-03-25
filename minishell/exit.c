
#include"minishell.h"

void bi_exit(char **arg, t_data *data) //
{
	int v;
	int i;
	int ret;

	i = 0;
	if (count_line(arg) > 2)
	{
		write (2, "minishell: exit: too many arguments\n", 37);
		mini_exit(1, data);
	}
	while (arg[++i])
	{
		ret = ft_atoi_with_validation(arg[i], &v);
		if (!v)
		{
			write (2, "minishell: exit: ", 18);
			ft_putstr_fd(arg[1], 2);
			write (2, ": numeric argument required\n", 29);
			mini_exit(2, data);
		}
	}
	if (arg[1] && v)
		mini_exit(ret % 256, data);
	else
		mini_exit(0, data);
}

void mini_exit(int ret, t_data *data)
{
	write(1, "exit\n", 5);
	free_tab(data->env);
	exit(ret);
}
