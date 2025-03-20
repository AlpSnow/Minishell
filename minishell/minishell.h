/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:58:58 by mwallis           #+#    #+#             */
/*   Updated: 2025/03/20 19:58:01 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>          // printf, perror
# include <stdlib.h>         // malloc, free, exit, getenv
# include <unistd.h>         // read, write, close, access, fork, getcwd, chdir, unlink, execve, isatty, ttyname, ...
//# include <fcntl.h>          // open
# include <sys/types.h>      // fork, open
//# include <sys/stat.h>       // open, stat, lstat, fstat
//# include <dirent.h>         // opendir, readdir, closedir
//# include <string.h>         // strerror
# include <sys/wait.h>       // wait, waitpid, wait3, wait4
//# include <signal.h>         // signal, kill, sigaction, sigemptyset, sigaddset
//# include <sys/ioctl.h>      // ioctl
//# include <termios.h>        // tcsetattr, tcgetattr
//# include <curses.h>         // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
//# include <term.h>           // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h> // readline
# include <readline/history.h>  // add_history
# include <stddef.h>
# include "./libft/libft.h"

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
#define ERROR_ARGC RED "Error: This program does not take any \
arguments." RESET "\n"



char	*get_prompt(void);//donne une string de ce type: "~minishell/minishell coquille >$" ou minishell est le repertoire courant

#endif
