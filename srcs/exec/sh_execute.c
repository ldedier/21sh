/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/18 17:27:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t g_parent;

void		sh_execute_child(t_context *context)
{
	sh_process_execute_dup_pipes(context);
	execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
	sh_process_execute_close_pipes(context);
	if (sh_verbose_exec())
		ft_dprintf(2, "Execve failed\n");
	exit(FAILURE);
}

int			sh_process_execute(t_context *context)
{
	int		res;

	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	if ((g_parent = fork()) == -1)
		return (FAILURE);
	if (g_parent == 0)
		sh_execute_child(context);
	else
	{
		wait(&res);
		sh_env_vars_update_question_mark(context, res);
		g_parent = 0;
		sh_process_execute_close_pipes(context);
		if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
			return (sh_perror("Could not modify this terminal attributes",
				"sh_init_terminal"));
	}
	return (SUCCESS);
}
