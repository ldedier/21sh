/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_process_parameter.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 11:27:13 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_expansions_parameter_format(t_expansion *exp, char *format)
{
	char	*head;
	int		i;

	head = exp->expansion;
	i = 0;
	if (*head == '#')
	{
		format[i] = '#';
		i++;
		head++;
	}
	if (!ft_isalpha(*head) && *head != '_')
	{
		if (!ft_chpbrk(head[1], ":-=?+%"))
			return (ft_perror("bad substitution (1)", NULL)); // del (1)
	}
	head++;
	while (ft_isalnum((int)*head) || *head == '_')
		head++;
	if (!ft_chpbrk(head[0], ":-=?+%"))
		return (ft_perror("bad substitution (2)", NULL)); // del (2)
	format[i] = *head;
	i++;
	if (ft_chpbrk(head[0], ":#%") && head[1] && ft_chpbrk(head[1], "-=?+#%"))
	{
		format[i] = head[1];
		i++;
	}
	format[i] = 0;
	return (SUCCESS);
}

char	*sh_expansions_parameter_get_param(t_context *context, t_expansion *exp)
{
	char	*value;
	char	*end;
	char	buf;

	if (!(end = ft_strpbrk(exp->expansion, ":-=?+%#")))
		end = exp->expansion + ft_strlen(exp->expansion);
	buf = *end;
	*end = 0;
	value = sh_vars_get_value(context->env, context->vars, exp->expansion);
	*end = buf;
	return (value);
}

char	*sh_expansions_parameter_get_word(t_context *context, t_expansion *exp, char *format)
{
	char	*start;

	start = ft_strstr(exp->expansion, format);
	if (*format == '#')
		format++;
	start += ft_strlen(format);
	return (start);
	(void)context;
}

int		sh_expansions_parameter_minus(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param)
		exp->res = ft_dy_str_new_str(word);
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			exp->res = ft_dy_str_new_str(word);
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_minus"));
	return (SUCCESS);
}

int		sh_expansions_parameter_equal(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	char	buff;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param)
	{
		param = ft_strstr(exp->expansion,  format);
		buff = *param;
		*param = 0;
		sh_vars_assign_key_val(context->env, context->vars, exp->expansion, word);
		*param = buff;
		exp->res = ft_dy_str_new_str(word);
	}
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
		{
			param = ft_strstr(exp->expansion,  format);
			buff = *param;
			*param = 0;
			sh_vars_assign_key_val(context->env, context->vars, exp->expansion, word);
			*param = buff;
			exp->res = ft_dy_str_new_str(word);
		}
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_"));
	return (SUCCESS);
}

int		sh_expansions_parameter_quest(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param)
		exp->res = ft_dy_str_new_str(word);
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			return (FAILURE);
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		return (FAILURE);
	if (!exp->res)
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_"));
	return (SUCCESS);
}

int		sh_expansions_parameter_plus(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	if (!param)
		exp->res = ft_dy_str_new_str("");
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			exp->res = ft_dy_str_new_str("");
		else
			exp->res = ft_dy_str_new_str(word);
	}
	else
		exp->res = ft_dy_str_new_str(word);
	if (!exp->res)
		return (ft_perror(SH_ERR1_MALLOC, "sh_expansions_"));
	return (SUCCESS);
}

// Need to implement Percent !
int		sh_expansions_percent(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	exp->res = ft_dy_str_new_str("Percent Parameter expansion not implemented yet");
	return (SUCCESS);
}

// Need to implement Hash !
int		sh_expansions_hash(t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;

	param = sh_expansions_parameter_get_param(context, exp);
	word = sh_expansions_parameter_get_word(context, exp, format);
	exp->res = ft_dy_str_new_str("Hash Parameter expansion not implemented yet");
	return (SUCCESS);
}