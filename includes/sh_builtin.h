/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/28 13:13:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTIN_H
# define SH_BUILTIN_H

# define NB_BUILTINS	11

# define CD_OPT_LOGIC	0x01
# define CD_OPT_PHYSIC	0x02
# define CD_OPT_HYPHEN	0x04

typedef struct		s_binary_stats
{
	int				max_path_len;
	int				max_name_len;
	int				max_hits_str_len;
}					t_binary_stats;

typedef	int	(*t_builtin)(t_context *);

typedef struct		s_builtin_container
{
	char			*name;
	t_builtin		builtin;
}					t_builtin_container;

/*
********************************************************************************
*/

/*
** sh_builtin.c
*/
t_builtin_container	*get_builtins(void);
t_builtin			sh_builtin_find(t_context *context);

/*
** sh_builtin_cd.c
*/
int					sh_builtin_cd(t_context *context);

/*
** sh_builtin_hash_tools.c
*/
void				process_builtin_hash_suppr_all(t_shell *shell);

/*
** sh_builtin_setenv.c
*/
int					sh_builtin_setenv_process (
	char *entry, t_dy_tab *env, t_context *context);
int					sh_builtin_setenv(t_context *context);

/*
** sh_builtin_echo.c
*/
int					sh_builtin_echo(t_context *context);

/*
** sh_builtin_cd.save
*/
int					sh_builtin_cd(t_context *context);

/*
** sh_builtin_set.c
*/
int					sh_builtin_set(t_context *context);

/*
** sh_builtin_unsetenv.c
*/
int					sh_builtin_unsetenv(t_context *context);

/*
** sh_builtin_exit.c
*/
int					sh_builtin_exit(t_context *context);

/*
** sh_builtin_cd_tools.c
*/
int					end_with_char(char *str, char c);
char				*get_path_from_request(char *old_pwd, char *path);

/*
** sh_builtin_hash_stats.c
*/
void				update_hash_stats(
	t_hash_table *table, t_binary_stats *stats);

/*
** sh_builtin_pwd.c
*/
char				*sh_builtin_pwd_physical(int fd_err);
char				*sh_builtin_pwd_logical(t_dy_tab *env, int fd_err);
int					sh_builtin_pwd(t_context *context);

/*
** sh_builtin_hash.c
*/
int					sh_builtin_hash(t_context *context);

/*
** sh_builtin_where.c
*/
int					sh_builtin_where(t_context *context);

/*
** sh_builtin_verbose.c
*/
int					sh_builtin_verbose(t_context *context);

/*
** sh_builtin_env.c
*/
int					sh_builtin_env(t_context *context);

#endif
