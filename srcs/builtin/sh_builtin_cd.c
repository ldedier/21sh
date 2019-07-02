/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/02 13:33:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_cd_rule7(t_context *context, char **curpath, char flags)
{
	char	*pwd;

	if (flags & CD_OPT_LOGIC)
	{
		if (**curpath != '/')
		{
			pwd = sh_builtin_pwd_logical(context->env, context->fd[FD_ERR]);
			if (!pwd)
			{
				free(*curpath);
				return (ERROR);
			}
			free(*curpath);
			if (!(*curpath = ft_strjoin_path(pwd, *curpath)))
				return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_rule7"));
		}
	}
	return (SUCCESS);
}

static int	sh_builtin_cd_rule8_2(char **curpath)
{
	int		len;
	char	*find;

	while ((find = ft_strstr(*curpath, ".")))
	{
		if (find[1] == '/')
			ft_strdelchars(find, 0, 2);
		else
			ft_strdelchars(find, 0, 1);
	}
	while ((find = ft_strstr(*curpath, "//")))
		ft_strdelchars(find, 0, 1);
	len = ft_strlen(*curpath);
	if (len > 1 && (*curpath)[len - 1] == '/')
		(*curpath)[len - 1] = '\0';
	return (SUCCESS);
}

static int	sh_builtin_cd_rule8_1(char **curpath)
{
	char	*find;
	char	*end;
	char	*start;

	while ((find = ft_strstr(*curpath, "..")))
	{
		end = find + 2;
		if (find == *curpath || find - 1 == *curpath)
			start = find;
		else
		{
			find[-1] = 0;
			start = ft_strrchr(*curpath, '/');
			find[-1] = '/';
			if (start == *curpath)
				start++;
		}
		ft_strdelchars(start, 0, end - start);
	}
	return (sh_builtin_cd_rule8_2(curpath));
}

static int		sh_builtin_cd_update_pwd(t_context *context, int flags, char *curpath) // Use curdir as pwd??
{
	char		*pwd;
	char		*old_pwd;

	if (flags & CD_OPT_LOGIC)
		pwd = curpath;
	else
		pwd = sh_builtin_pwd_physical(context->fd[FD_ERR]);
	if (!pwd)
		return (ERROR);
	old_pwd = sh_vars_get_value(context->env, NULL, "PWD");
	if (old_pwd)
		if (sh_vars_assign_key_val(context->env, NULL, "OLDPWD", old_pwd) != SUCCESS)
			return (FAILURE);
	if (sh_vars_assign_key_val(context->env, NULL, "PWD", pwd) != SUCCESS)
		return (FAILURE);
	// free(pwd);
	return (SUCCESS);
	flags = 0;
}

int		sh_builtin_cd(t_context *context)
{
	char	*param;
	char	*curpath;
	char	flags;
	int		i;
	int		ret;

	i = 1;
	curpath = NULL;
	if ((ret = sh_builtin_cd_parser(context, &i, &flags, &curpath)))
		return (ret);
	param = context->params->tbl[i];
	if ((ret = sh_builtin_cd_pre_rules(context, param, &curpath)))
		return (ret);
	if (ft_strequ(param, "-"))
		param[0] = 0;
	if (!(flags & CD_OPT_PHYSIC))
	{
		sh_builtin_cd_rule7(context, &curpath, flags);
		sh_builtin_cd_rule8_1(&curpath);
	}
	ret = sh_builtin_cd_rule10(context, curpath, flags, param);
	free(curpath);
	return (ret);
}
