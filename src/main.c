/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:52 by pehenri2          #+#    #+#             */
/*   Updated: 2024/09/11 20:27:45 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char					*line;
	t_token					*list;
	t_tree_node				*root;

	init_environment_variables();
	setup_terminal_properties();
	while (42)
	{
		line = init_and_wait_input(&list);
		if (!line)
			break ;
		else if (*line != '\0')
		{
			add_history(line);
			if (lexer(line, &list) == SUCCESS)
			{
				if (parser(list, &root) == SUCCESS)
					set_exit_status(executor(root));
			}
		}
		reset_for_next_iteration(line);
	}
	return (cleanup_and_exit(SUCCESS));
}

void	setup_terminal_properties(void)
{
	static struct termios	term;
	static int				term_saved = 0;

	if (term_saved)
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	else
	{
		tcgetattr(STDIN_FILENO, &term);
		term_saved = 1;
	}
}

char	*init_and_wait_input(t_token **list)
{
	char	*line;

	if (setup_signal_handler(main_signal_handler) != SUCCESS)
	{
		free_env();
		ft_free_memory();
		exit(signal_error());
	}
	*list = NULL;
	line = readline("minishell> ");
	return (line);
}

void	reset_for_next_iteration(char *line)
{
	setup_terminal_properties();
	free(line);
	(void)line;
	delete_heredoc_files();
	ft_free_memory();
}

int	cleanup_and_exit(int status)
{
	free_env();
	delete_heredoc_files();
	ft_free_memory();
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	rl_clear_history();
	exit(status);
}
