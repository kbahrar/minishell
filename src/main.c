/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:08:42 by kbahrar           #+#    #+#             */
/*   Updated: 2019/07/23 19:19:57 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	show_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

static int	commandes(char **env, char **args, t_vars **vars)
{
	if (ft_strcmp(args[0], "exit") == 0)
	{
		free_sh(env, args, vars);
		exit(0);
	}
	else if (ft_strcmp(args[0], "alias") == 0)
		ft_alias(&g_alias, args[1], args[2]);
	else if (ft_strcmp(args[0], "/usr/bin/cd") == 0 ||
	ft_strcmp(args[0], "cd") == 0)
		do_cd(args, env, vars);
	else if (ft_strcmp("setenv", args[0]) == 0)
	{
		if (args[1])
			ft_setenv(args, vars);
		else
			show_env(env);
	}
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		ft_unsetenv(args, vars);
	else
		return (0);
	return (1);
}

static void	child(char **args, char **env, pid_t father)
{
	if (ft_strcmp(args[0], "/usr/bin/env") == 0 ||
	ft_strcmp(args[0], "env") == 0)
		show_env(env);
	else if (ft_strcmp(args[0], "/bin/echo") == 0 ||
	ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (ft_strchr(args[0], '/') == NULL)
		ft_putstr_plus(args[0], ": command not found.\n");
	else
	{
		signal(SIGINT, fun_child);
		father = fork();
		wait(NULL);
		if (father == 0)
			if (execve(args[0], args, env) == -1)
			{
				ft_putstr_fd(args[0], 2);
				if (access(args[0], F_OK) == 0)
					ft_putstr_fd(": Permission denied.\n", 2);
				else
					ft_putstr_fd(": command not found.\n", 2);
				exit(0);
			}
	}
}

int			main(void)
{
	extern char	**environ;
	char		**args;
	t_vars		*vars;
	pid_t		father;
	char		**env;

	vars = ft_vars(environ);
	g_alias = NULL;
	father = 0;
	while (1)
	{
		signal(SIGINT, fun_father);
		env = make_env(vars);
		ft_putstr("\e[7mkb-sh $>\033[0m ");
		if ((args = read_line(env, vars)) != NULL)
			if (commandes(env, args, &vars) == 0)
			{
				args[0] = access_file(env, args[0]);
				child(args, env, father);
			}
		free_sh(env, args, NULL);
	}
}
