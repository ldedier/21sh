/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vars.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:35:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/14 13:31:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# define VERBOSE_AST		0x0001
# define VERBOSE_LEXER		0x0002
# define VERBOSE_EXEC		0x0004
# define VERBOSE_PIPE		0x0008

/*
** sh_variables.c
*/
int		sh_variables_assignment(t_dy_tab *vars, char *assignment);

/*
** sh_vars_tools_1.c
*/
int		sh_vars_key_exist(t_dy_tab *vars, char *key);
int		sh_vars_get_index(t_dy_tab *vars, char *key);
char	*sh_vars_get_value(t_dy_tab *env, t_dy_tab *vars, char *key);

/*
** sh_vars_tools_2.c
*/
int		sh_vars_mod_key(t_dy_tab *vars, char *key, char *value);
int		sh_vars_add_key(t_dy_tab *vars, char *key, char *value);
int		sh_vars_assignment(t_dy_tab *env, t_dy_tab *vars, char *assignment);
int		sh_vars_assign_key_val(t_dy_tab *env, t_dy_tab *vars, char *key, char *value);

/*
** sh_verbose.c
*/
int		sh_verbose_update(t_shell *shell);
int		sh_verbose_ast(void);
int		sh_verbose_lexer(void);
int		sh_verbose_exec(void);
int		sh_verbose_pipe(void);

#endif