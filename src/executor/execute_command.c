/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:47:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/08/28 17:07:20 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_tree_node *cmd_node)
{
	int	pid;
	int	exit_status;

	exit_status = 0;
	if (cmd_node->tokens)
		expand_tokens(cmd_node);
	if (cmd_node->tokens == NULL)
		return (SUCCESS);
	if (is_builtin(cmd_node->tokens))
		return (execute_builtin(cmd_node->tokens));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(handle_error("fork"));
		setup_fork_signal_handlers(pid);
		if (pid == 0)
			run_command_in_child_process(cmd_node->tokens);
		wait_child_status(pid, &exit_status);
		return (exit_status);
	}
}

void	run_command_in_child_process(t_token *tokens)
{
	char	**cmd_and_args;
	char	*cmd_path;
	int		exit_status;

	cmd_path = get_cmd_path(tokens);
	cmd_and_args = get_cmd_and_args(tokens);
	if (execve(cmd_path, cmd_and_args, __environ) == -1)
	{
		exit_status = throw_error(cmd_path);
		free_env();
		ft_free_memory();
		exit(exit_status);
	}
}

char	*get_cmd_path(t_token *tokens)
{
	char	*cmd_path;

	if (ft_strcmp(tokens->value, ".") == 0)
		exit(!!write(STDERR_FILENO, ".: filename argument required\n", 30));
	else if (*(tokens->value) == '\0')
		cmd_path = tokens->value;
	else if (ft_strchr(tokens->value, '/'))
	{
		cmd_path = tokens->value;
		tokens->value = ft_strrchr(tokens->value, '/') + 1;
	}
	else
		cmd_path = search_in_path(tokens);
	return (cmd_path);
}

char	*search_in_path(t_token *tokens)
{
	char	*cmd_path;
	char	*path_env;
	char	**paths;
	int		i;

	path_env = getenv("PATH");
	if (!path_env)
		return (tokens->value);
	paths = ft_split(path_env, ':');
	if (!paths)
		exit(!!write(STDERR_FILENO, "minishell: failed to retrieve PATH\
 directories\n", 47));
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, tokens->value);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	ft_fprintf(STDERR_FILENO, "%s: command not found\n", tokens->value);
	free_env();
	ft_free_memory();
	exit(127);
}

char	**get_cmd_and_args(t_token *tokens)
{
	t_token	*current;
	char	**cmd_and_args;
	int		i;

	cmd_and_args = ft_dalloc(sizeof(char *), (token_lst_get_size(tokens) + 1));
	if (!cmd_and_args)
		handle_error("failed to allocate memory");
	i = 0;
	current = tokens;
	while (current)
	{
		cmd_and_args[i++] = current->value;
		current = current->next;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}
