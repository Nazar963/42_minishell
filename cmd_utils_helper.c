/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:42:56 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/27 09:15:48 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin_helper_1(char **inputs)
{
	int	n;

	n = 0;
	if (inputs[2])
	{
		perror(" ");
		g_sig.g_exit = 1;
		return ;
	}
	if (inputs[1] == NULL)
		n = is_builtin_helper("~", n);
	else
		n = is_builtin_helper(inputs[1], n);
	if (n < 0)
		g_sig.g_exit = 1;
}

void	pwd_helper(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(NULL, 0);
	getcwd(buffer, sizeof(buffer));
	ft_printf("%s\n", buffer);
	free(buffer);
}

int	full_size_helper(char *str, int i, int j)
{
	j = i + 1;
	while (str[j] && (!(str[j] >= 9 && str[j] <= 13))
		&& str[j] != '$' && str[j] != '\'' && str[j] != '\"')
		j++;
	return (j);
}

void	not_v_helper(char *str, t_x *x)
{
	char	*new;

	if (ft_strnstr(str, "\'", ft_strlen(str)) && strlen(str) > 1)
	{
		new = ft_strtrim(str, "'");
		new_join(x, new);
		new_join(x, " ");
		free (new);
	}
	else
	{
		new_join(x, str);
		new_join(x, " ");
	}
}

void	add_q_s(t_x *x)
{
	if (x->str_split[x->i][0] == '\'' && x->str_split[x->i][1] == '\"'
		&& ft_strlen(x->str_split[x->i]) == 2)
	{
		new_join(x, "\1'\"");
		new_join(x, " ");
	}
	else if (x->str_split[x->i][0] == '\"' && x->str_split[x->i][1] == '\''
		&& ft_strlen(x->str_split[x->i]) == 2)
	{
		new_join(x, "\"\'");
		new_join(x, " ");
	}
	else if (ft_strlen(x->str_split[x->i]) > 1 && x->str_split[x->i][1] == '\'')
	{
		new_join(x, x->str_split[x->i]);
		new_join(x, " ");
	}
	else
	{
		new_join(x, "\1'");
		new_join(x, " ");
	}
}
