/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vars_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 22:15:48 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/10 12:31:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vars_key_exist:
**	Look if a variable, identified by its key, exists in a t_dy_tab
**	return:
**		SUCESS or FAILURE
*/
int		sh_vars_key_exist(t_dy_tab *vars, char *key)
{
	int		i;
	int		j;
	char	**tbl;

	i = 0;
	tbl = (char**)vars->tbl;
	while (tbl[i])
	{
		j = 0;
		while (tbl[i][j] && key[j] && tbl[i][j] == key[j])
			j++;
		if (tbl[i][j] == '=' && key[j] == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

/*
** sh_vars_get_index:
**	Look if a variable, identified by its key, exists in a t_dy_tab
**	return:
**		Index of in the tab, or -1 if it does not exists
*/
int		sh_vars_get_index(t_dy_tab *vars, char *key)
{
	int		i;
	int		j;
	char	**tbl;

	i = 0;
	tbl = (char**)vars->tbl;
	while (tbl[i])
	{
		j = 0;
		while (tbl[i][j] && key[j] && tbl[i][j] == key[j])
			j++;
		if (tbl[i][j] == '=' && key[j] == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*
** sh_vars_get_value:
**	Look for the value of an entry in environment and variables dynamic tables,
**	identified by it's key
**	It is possible to look only one table, by sending NULL in the other param
**	return:
**		NULL if key does not exists
**		Address of the begining of the value
*/
char	*sh_vars_get_value(t_dy_tab *env, t_dy_tab *vars, char *key)
{
	int		index;
	char	**tbl;

	if (!env)
	{
		if ((index = sh_vars_get_index(vars, key)) == -1)
			return (NULL);
	}
	else if (!vars)
	{
		if ((index = sh_vars_get_index(env, key)) == -1)
			return (NULL);		
	}
	else
	{
		if ((index = sh_vars_get_index(env, key)) == -1)
			if ((index = sh_vars_get_index(vars, key)) == -1)
				return (NULL);
	}
	tbl = (char**)vars->tbl;
	return (ft_strchr(tbl[index], '=') + 1);
}