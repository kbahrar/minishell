/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:15:22 by kbahrar           #+#    #+#             */
/*   Updated: 2019/07/23 19:59:21 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct		s_vars
{
	char			*nom;
	char			*valeur;
	struct s_vars	*next;
}					t_vars;

typedef struct		s_alias
{
	char			*cmd;
	char			*valeur;
	struct s_alias	*next;
}					t_alias;

void				ft_alias(t_alias **alias, char *cmd, char *vl);
t_alias				*g_alias;
char				**make_env(t_vars *vars);
char				*access_file(char **env, char *file);
char				**read_line(char **env, t_vars *vars);
void				do_cd(char **args, char **env, t_vars **vars);
void				free_paths(char **paths);
t_vars				*ft_vars(char **env);
char				*home_path(char *path, char **env);
char				**sh_split(char *line);
void				ft_setenv(char **args, t_vars **vars);
void				ft_unsetenv(char **args, t_vars **vars);
void				free_list(t_vars **vars);
void				free_sh(char **env, char **args, t_vars **vars);
void				ft_echo(char **args);
void				fun_father(int sign);
void				fun_child(int sign);
char				*path_home(char *path, char **env);
char				*var_dol(char *var, t_vars *vars);

#endif
