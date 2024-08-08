/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:29:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/08/08 19:58:06 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_file(t_token *token)
{
	int		fd;
	char	*file_name;
	bool	is_expandable;
	int		default_stdin;

	default_stdin = dup(STDIN_FILENO);
	if (setup_signal_handler(heredoc_signal_handler) != SUCCESS)
		return (signal_error());
	if (initialize_heredoc_file(token, &fd, &file_name,
			&is_expandable) != SUCCESS)
		return (set_exit_status(handle_error("failed to create heredoc")));
	while (42)
		if (write_input_to_heredoc(fd, token->value, is_expandable) == SUCCESS)
			break ;
	if (*get_exit_status() == SIGINT + 128)
	{
		dup2(default_stdin, STDIN_FILENO);
		return (set_exit_status(SIGINT + 128));
	}
	close(fd);
	token->value = file_name;
	return (SUCCESS);
}

int	initialize_heredoc_file(t_token *token, int *fd, char **file_name,
		bool *is_expandable)
{
	int		*heredoc_counter;

	*is_expandable = false;
	heredoc_counter = get_heredoc_counter();
	*file_name = ft_strjoin("/tmp/.heredoc", ft_itoa((*heredoc_counter)++));
	*fd = open(*file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd < 0)
		return (FAILURE);
	if (!ft_strchr(token->value, '\"') && !ft_strchr(token->value, '\''))
		*is_expandable = true;
	token->value = remove_quotes(token->value);
	return (SUCCESS);
}

int	write_input_to_heredoc(int fd, char *end_condition, int is_expandable)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		if (*get_exit_status() != SIGINT + 128)
			ft_fprintf(STDERR_FILENO, "minishell: warning: here-document\
 delimited by end-of-file (wanted '%s')\n", end_condition);
		return (SUCCESS);
	}
	if (ft_strcmp(line, end_condition) == SUCCESS)
		return (SUCCESS);
	if (is_expandable)
		line = expand_vars(line);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (FAILURE);
}

int	delete_heredoc_files(void)
{
	char	*file_name;
	int		*heredoc_counter;

	heredoc_counter = get_heredoc_counter();
	while ((*heredoc_counter) >= 0)
	{
		file_name = ft_strjoin("/tmp/.heredoc", ft_itoa((*heredoc_counter)));
		unlink(file_name);
		if (*heredoc_counter > 0)
			(*heredoc_counter)--;
		else
			break ;
	}
	return (SUCCESS);
}

int	*get_heredoc_counter(void)
{
	static int	counter;

	return (&counter);
}
