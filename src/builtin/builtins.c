/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:52:37 by pehenri2          #+#    #+#             */
/*   Updated: 2024/08/28 17:08:20 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_token *tokens)
{
	if (!ft_strcmp(tokens->value, "cd") || !ft_strcmp(tokens->value, "echo")
		|| !ft_strcmp(tokens->value, "env") || !ft_strcmp(tokens->value, "exit")
		|| !ft_strcmp(tokens->value, "export") || !ft_strcmp(tokens->value,
			"pwd") || !ft_strcmp(tokens->value, "unset"))
		return (true);
	return (false);
}

int	execute_builtin(t_token *tokens)
{
	if (!ft_strcmp(tokens->value, "cd"))
		return (execute_cd(tokens));
	if (!ft_strcmp(tokens->value, "echo"))
		return (execute_echo(tokens));
	if (!ft_strcmp(tokens->value, "env"))
		return (execute_env(tokens));
	if (!ft_strcmp(tokens->value, "exit"))
		return (execute_exit(tokens));
	if (!ft_strcmp(tokens->value, "export"))
		return (execute_export(tokens));
	if (!ft_strcmp(tokens->value, "pwd"))
		return (execute_pwd());
	if (!ft_strcmp(tokens->value, "unset"))
		return (execute_unset(tokens));
	return (handle_error("error executing builtin"));
}
