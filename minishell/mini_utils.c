/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:59:45 by lmarck            #+#    #+#             */
/*   Updated: 2025/03/26 23:35:13 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
int	ft_atoi_with_validation(const char *nptr, int *is_valid)
{
	int		i;
	int		sign;
	long	result;
	i = 0;
	sign = 1;
	result = 0;
	*is_valid = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			sign = sign * -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i++] - 48);
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && (-1 * result) < INT_MIN))
			return (*is_valid = 0, 0);
	}
	if (nptr[i] != '\0')
		*is_valid = 0;
	return (sign * result);
}
int	count_line(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		i++;
	return(i);
}
char	*add_chr(unsigned char buf, char *str)
{
	char	*nstr;
	int		i;

	i = 0;
	nstr = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (!nstr)
		return (NULL);
	while (str[i])
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = buf;
	nstr[i + 1] = 0;
	free(str);
	return (nstr);
}
