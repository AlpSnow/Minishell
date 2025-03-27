/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:58:58 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/25 19:04:51 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_data
{
	char **env;

}	t_data;

typedef struct s_tok
{
	char *str;
	int type;
}	t_tok;

# include <stdio.h>          // printf, perror
# include <stdlib.h>         // malloc, free, exit, getenv
# include <unistd.h>         // read, write, close, access, fork, getcwd, chdir, unlink, execve, isatty, ttyname, ...
# include <fcntl.h>          // open
# include <sys/types.h>      // fork, open
//# include <sys/stat.h>       // open, stat, lstat, fstat
//# include <dirent.h>         // opendir, readdir, closedir
//# include <string.h>         // strerror
# include <sys/wait.h>       // wait, waitpid, wait3, wait4
# include <signal.h>
//# include <sys/ioctl.h>      // ioctl
//# include <termios.h>        // tcsetattr, tcgetattr
//# include <curses.h>         // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
//# include <term.h>           // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h> // readline
# include <readline/history.h>  // add_history
# include <stddef.h>
# include "./libft/libft.h"
# include <limits.h>

# ifndef COLORS_H
#  define COLORS_H

#  define RED "\033[31m" //a mettre en debut de chaine pour lui donner une couleur
#  define GRN "\033[32m"
#  define YEL "\033[33m"
#  define BLU "\033[34m"
#  define MAG "\033[35m"
#  define CYN "\033[36m"
#  define WHT "\033[37m"

#  define RESET "\033[0m"    //a mettre a la fin pour reset la couleur exemple: printf(GRN" coquille >$ "RESET); pour imprimer en vert

# endif

//Messages d'erreurs :
# define ERROR_ARGC RED "Error: This program does not take any \
arguments." RESET "\n"
# define ERROR_ENV RED "Error: Failed to copy environment \
variables." RESET "\n"



char	*get_prompt(void);//donne une string de ce type: "~minishell/minishell coquille >$" ou minishell est le repertoire courant
int		ft_atoi_with_validation(const char *nptr, int *is_valid);
void	free_tab(char **tab);//free un tableau de string
void mini_exit(int ret, t_data *data);//free puis exit proprement le programme
int	count_line(char **tab);//compte le nombre de lignes d'un tableau nul terminated
void built_in_exec(char **arg, t_data *data);//execute les fonctions build in si elles doivent l'etre,
int is_build_in(char *name);//verifie si un argument est une fonctions built in et renvoie son ID
int exec_command(char **arg, t_data *data);//prends en argument une commande et ses argument et les executes

//Built-in functions

void bi_exit(char **arg, t_data *data);

#endif
