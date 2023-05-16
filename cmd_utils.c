/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:47:41 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/10 09:36:11 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_input(char *eof, int *file)
{
	char	*str;
	int		len;
	int		fd;

	len = ft_strlen(eof);
	fd = open(".heredoc", O_WRONLY | O_CREAT, 0777);
	while (1)
	{
		write(1, "heredoc>", 9);
		str = get_next_line(0);
		if (ft_strncmp(str, eof, len) == 0)
			break ;
		write(fd, str, ft_strlen(str));
	}
	close(fd);
	*file = open(".heredoc", O_RDONLY);
}

char	*find_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	path = env[i];
	path += 5;
	return (path);
}

char	*find_cmd(char *cmd, char **env)
{
	char	**path_list;
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	path_list = ft_split(find_path(env), ':');
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		free(tmp);
		i++;
	}
	while (--i >= 0)
		free(path_list[i]);
	free(path_list);
	perror(" ");
	return (NULL);
}

int	is_builtin_helper(char *str, int n)
{
	char	*user;
	char	*path;
	char	*fin;

	if (ft_strnstr(str, "~", ft_strlen(str)) && ft_strlen(str) == 1)
	{
		user = getenv("USER");
		path = ft_strdup("/home/");
		fin = ft_strjoin(path, user);
		n = chdir(fin);
		free(path);
		free(fin);
	}
	else
		n = chdir(str);
	if (n < 0)
		perror("");
	return (n);
}

bool	is_builtin(char **inputs, t_x *x, t_flags flag)
{
	if (is_any(inputs) == true)
	{
		inputs = handle_redirect(inputs, flag, false);
		if (!inputs)
			return (true);
	}
	if (ft_strcmp(inputs[0], "cd") == 0)
		is_builtin_helper_1(inputs);
	else if (ft_strcmp(inputs[0], "pwd") == 0)
		pwd_helper();
	else if (ft_strcmp(inputs[0], "echo") == 0)
		echo(inputs);
	else if (ft_strcmp(inputs[0], "env") == 0)
		l_env(x->envp);
	else if (ft_strcmp(inputs[0], "export") == 0)
		export(inputs, &x);
	else if (ft_strcmp(inputs[0], "unset") == 0)
		unset(inputs, &x);
	else if (ft_strcmp(inputs[0], "exit") == 0)
		ft_exit(inputs, &x);
	else
		return (false);
	free_split(inputs);
	reset_io(flag.stdin, flag.stdout);
	return (true);
}
