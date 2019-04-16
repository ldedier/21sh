/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:43:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/14 17:11:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	print_buffer(unsigned char buffer[READ_BUFF_SIZE])
{
	int i;

	i = 0;
	while (i < READ_BUFF_SIZE)
	{
		ft_printf("\nbuffer[%d]: %d (%.8b)", i, buffer[i], buffer[i]);
		i++;
	}
}

int		process_escape_sequence(t_command_line *command_line,
		unsigned char buffer[READ_BUFF_SIZE])
{
	if (buffer[1] == 91 && buffer[2] == 67)
		process_right(command_line);
	else if (buffer[1] == 91 && buffer[2] == 68)
		process_left(command_line);
	else if (buffer[1] == 91 && buffer[2] == 51)
		process_suppr(command_line);
	return (0);
}

void	process_keys(t_shell *shell, t_command_line *command_line,
				unsigned char *buffer)
{
	(void)shell;
	if (buffer[0] == 27)
		process_escape_sequence(command_line, buffer);
	else if (buffer[0] == 12)
		process_clear(command_line->dy_str);
	else if (buffer[0] == 127)
		process_delete(command_line);
	else if (buffer[0] == 3)
	{
		get_down_from_command(command_line);
		g_glob.cursor = 0;
		command_line->dy_str->current_size = 0;
		command_line->current_index = 0;
		ft_bzero(g_glob.command_line.dy_str->str,
			g_glob.command_line.dy_str->max_size);
		command_line->nb_chars = 0;
		render_command_line(g_glob.command_line.dy_str, 0);
	}
}

int		process_keys_ret(t_shell *shell, t_command_line *command_line,
			unsigned char *buffer)
{
	if (buffer[0] == 10) // enter
	{
		get_down_from_command(command_line);
		command_line->dy_str->current_size = 0;
		return (0);
	}
	else if (buffer[0] == 4) //ctrl D
	{
		if (command_line->dy_str->current_size == 0)
		{
			ft_dprintf(0, "exit\n");
			shell->running = 0;
			return (CTRL_D);
		}
	}
//	else if (buffer[0] == 9 && process_tab(shell, command_line) != SUCCESS)
//		return (FAILURE);
	return (4);
}

int		get_keys(t_shell *shell, t_command_line *command_line)
{
	unsigned char	buffer[READ_BUFF_SIZE];
	int				ret;

	ft_bzero(buffer, READ_BUFF_SIZE);
	while (1)
	{
		ret = read(0, buffer, READ_BUFF_SIZE);
		if (is_printable_utf8(buffer, ret))
		{
			if (sh_add_to_command(command_line, buffer, ret))
				return (1);
			render_command_line(command_line->dy_str, 1);
		}
		process_keys(shell, command_line, buffer);
		ret = process_keys_ret(shell, command_line, buffer);
		if (ret == CTRL_D || ret == 0 || ret == FAILURE)
			return (ret);
		ft_bzero(buffer, READ_BUFF_SIZE);
	}
}