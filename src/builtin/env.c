/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:29:57 by pehenri2          #+#    #+#             */
/*   Updated: 2024/08/28 16:59:32 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_token *tokens)
{
	int		i;
	char	**env;

	env = *get_my_env();
	if (tokens->next)
		return (!!write(STDERR_FILENO, "env: too many arguments", 23));
	i = -1;
	while (env[++i])
	{
		if (env[i][0] && ft_strchr(env[i], '='))
			ft_fprintf(STDOUT_FILENO, "%s\n", env[i]);
	}
	return (SUCCESS);
}
