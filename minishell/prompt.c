/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:56:39 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/25 23:47:40 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_hostname(char *str)
{
	char	*newline;
	char	*dot;

	newline = ft_strchr(str, '\n');
	if (newline)
		*newline = '\0';
	dot = ft_strchr(str, '.');
	if (dot)
		*dot = '\0';
}

static char	*get_host(void)
{
	int		fd;
	char	*str;
	int		len;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	str = malloc(sizeof(char) * 256);
	if (!str)
		return (close(fd), NULL);
	len = read(fd, str, 255);
	close(fd);
	if (len <= 0)
		return (free(str), NULL);
	str[len] = '\0';
	clean_hostname(str);
	return (str);
}

static char	*shorten_cwd(char *cwd, char *home)
{
	char	*tmp;

	if (cwd && home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		return (tmp);
	}
	return (cwd);
}

static char	*build_user_host(char *user, char *host)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(user, "@");
	res = ft_strjoin(tmp, host);
	free(tmp);
	free(host);
	tmp = ft_strjoin(res, ":");
	free(res);
	res = ft_strjoin(GRN, tmp);
	free(tmp);
	return (res);
}

char	*get_prompt(void)
{
	char	*user;
	char	*host;
	char	*cwd;
	char	*colored;
	char	*tmp;

	user = getenv("USER");
	host = get_host();
	cwd = getcwd(NULL, 0);
	cwd = shorten_cwd(cwd, getenv("HOME"));
	if (!user || !cwd || !host)
		return (free(cwd), free(host), ft_strdup(GRN "minishell > " RESET));
	colored = build_user_host(user, host);
	tmp = ft_strjoin(BLU, cwd);
	free(cwd);
	cwd = ft_strjoin(colored, tmp);
	free(colored);
	free(tmp);
	colored = ft_strjoin(cwd, RESET "$ ");
	free(cwd);
	return (colored);
}
