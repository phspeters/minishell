/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:03:10 by pehenri2          #+#    #+#             */
/*   Updated: 2024/09/11 20:32:13 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_token *tokens)
{
	long	status;

	status = 0;
	if (tokens->next)
	{
		status = ft_atol(tokens->next->value);
		if (validate_argument(tokens->next->value)
			|| *(tokens->next->value) == '\0')
		{
			ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				tokens->next->value);
			cleanup_and_exit(SYNTAX_ERROR);
		}
		if (tokens->next->next)
		{
			write(STDERR_FILENO, "exit: too many arguments\n", 25);
			cleanup_and_exit(EXIT_FAILURE);
		}
	}
	if (status)
		cleanup_and_exit(status % 256);
	cleanup_and_exit(*get_exit_status());
	return (SUCCESS);
}

int	validate_argument(char *arg)
{
	int		i;
	char	sign;

	i = 0;
	sign = '+';
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = arg[i];
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FAILURE);
		i++;
	}
	if (check_limits(arg, sign) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_limits(char *arg, char sign)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	if (ft_strlen(arg) > 19)
		return (FAILURE);
	if (ft_strlen(arg) < 19)
		return (SUCCESS);
	if ((ft_strcmp(arg, "9223372036854775807") > 0 && sign == '+')
		|| (ft_strcmp(arg, "9223372036854775808") > 0 && sign == '-'))
		return (FAILURE);
	return (SUCCESS);
}
