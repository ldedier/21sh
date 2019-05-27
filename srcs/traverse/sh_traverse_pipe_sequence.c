/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/27 18:50:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int sh_add_pipe_redirections(t_ast_node *from, t_ast_node *to)
{
	int fds[2];

	if (pipe(fds))
		return (ft_perror(SH_ERR1_PIPE, "add_pipe_redirections"));
	
	
	if (sh_add_redirection(OUTPUT, 1, fds[PIPE_IN],
			&from->metadata.command_metadata.redirections))
		return (FAILURE);

	if (sh_add_redirection(INPUT, 0, fds[PIPE_OUT],
			&to->metadata.command_metadata.redirections))
		return (FAILURE);
	ft_dprintf(2, "new pipe : in : %d, out : %d\n", fds[PIPE_IN], fds[PIPE_OUT]);
	return (SUCCESS);
}

static void sh_init_command_redirections_list(t_ast_node *node)
{
	t_list *ptr;
	t_ast_node	*child;

	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		child = ptr->content;
		((t_ast_node *)(child->children->content))->metadata.command_metadata.redirections = NULL;
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
}

static int	sh_process_pipe_redirections(t_ast_node *node)
{
	t_list		*ptr;
	t_ast_node	*from;
	t_ast_node	*to;

	ptr = (t_list *)node->children;
	from = NULL;
	while (ptr != NULL)
	{
		to = ((t_ast_node *)(ptr->content))->children->content;
		if (from != NULL && sh_add_pipe_redirections(from, to))
			return (FAILURE);
		if ((ptr = ptr->next))
			ptr = ptr->next;
		from = to;
	}
	return (SUCCESS);
}

static int sh_traverse_pipe_sequences_redirections(t_ast_node *node,
			t_context *context)
{
	t_ast_node	*from;
	t_ast_node	*simple_command_node;;
	t_list		*ptr;

	sh_init_command_redirections_list(node);
	if (sh_process_pipe_redirections(node))
		return (FAILURE);
	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		from = (t_ast_node *)(ptr->content);
		simple_command_node = from->children->content;
		context->current_command_node = simple_command_node;
		if (g_grammar[from->symbol->id].traverse(from, context) == FAILURE)
			return (FAILURE);
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
	return (SUCCESS);
}

int		sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		return (sh_traverse_pipe_sequences_redirections(node, context));
	else
		return (sh_traverse_tools_browse(node, context));
}
