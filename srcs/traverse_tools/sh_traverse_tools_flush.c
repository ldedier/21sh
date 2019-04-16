/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_flush.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:40:06 by jmartel           #+#    #+#             */
/*   Updated: 2019/04/16 17:13:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_traverse_tools_flush(t_context *context)
{
	int		ret;

	if (!context->params->tbl[0])
		return (SUCCESS);
	ret = execute_command(context);
	sh_traverse_tools_reset_params(context);
	return (ret);
}
