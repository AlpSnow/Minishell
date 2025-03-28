
#include"minishell.h"

int	bi_export(char **arg, t_data *data)
{
	int	i;
	int	error;

	error = 0;
	if (arg[1] == NULL)
		print_export(sort_tab(dup_tab(data->env)));
	else
	{
		i = 1;
		while (arg[i])
		{
			if (!is_valid_var_name(arg[i]))
			{
				put_error(arg[0], arg[i], W_ID);
				error++;
			}
			else
			{
				data->env = ft_add_line(data->env, arg[i]);
			}
			i++;
		}
	}
	return (ft_is_zero(error));
}

void	print_export(char** tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tab[i], 1);
		write(1, "\n", 1);
		i++;
	}
	free(tab);
}

int	is_valid_var_name(char *arg)
{
	int	i;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	**ft_add_line(char **tab, char *line)
{
	char **ntab;
	int i;

	i = 0;
	ntab = ft_calloc(count_line(tab) + 2, sizeof(char*));
	if (!ntab)
		return (NULL);
	while (tab[i])
	{
		ntab[i] = tab[i];
		i++;
	}
	ntab[i] = ft_strdup(line);
	free(tab);
	return (ntab);
}
/* char **add_var(char *arg, char **env)
{
	char **nenv;
	int i;

	i = count_line(env);
	nenv =
	if(!nenv)
		exit(MALLOC_FAIL);

	return (nenv);
} */
