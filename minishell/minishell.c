/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:00:39 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/13 19:17:26 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	char	*input_line;
	char	**input_tab;
	int		status;

	(void)argv;
	if (argc != 1)
		return (write (1, ERROR_ARGC, 58), 1);

	//faire environnement ici :
	(void)envp;

	while (1)
	{
		input_line = readline(get_prompt()); //affiche le prompt et attends la commande de l'utilisateur
		input_tab = ft_split(input_line, ' '); //separe les arguments dans un tableau tab[0] = executable ensuite les arguments.
		if (fork() == 0) //cree un process enfant dans lequel on pourras executer le programme
			execvp(input_tab[0], &input_tab[0]); //execute le programme en lui donnant les arguments(echo etc..)
		wait(&status); //le processus parent (celui de notre minishell attend la fin du processus enfant(execution du programme en commande) pour continuer
	}
	return	(0);
}

char	*get_prompt() //donne un prompte avec le repertoire courant et le parents comme dans zsh() c'est pas obligatoire donc pas besoin de faire exactement comme bash
{
	char	*pwd;
	int		i;
	int		j;
	int		l;
	char	*prompt;

	pwd = getcwd(NULL, 0); //attribue le meme resultat que pwd dans le shell
	l = ft_strlen(pwd);
	i = l;
	j = 2;
	while (j && i)
	{
		if (pwd[i] == '/')
			j--;
		if (j)
			i--;
		else
			i++;
	}
	prompt = ft_calloc(l - i + 2, sizeof(char));
	prompt = ft_strjoin("~", &pwd[i]);
	prompt = ft_strjoin(prompt, GRN" coquille >$ "RESET);
	free(pwd);
	return (prompt);
}
