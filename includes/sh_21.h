/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_21.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:26 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 17:13:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_21_H
# define SH_21_H

#include "libft.h"
#include <stdio.h> //todel

# define SH_LEXER_AUTO_LEN	5

# define end	-1
# define error	-2
# define DEBUG_BUFFER	50

typedef struct		s_automate
{
	int				status;
	int				(*automate)(int status, char c);
}					t_automate;

typedef enum		e_tokenlist
{
	UNKNOWN = -1,
	SPACE,
	WHILE,
	GREAT,
	LESS,
	WORD,
}					t_tokenlist;

typedef enum		e_test_token_id
{
	T_A,
	T_B,
	END_OF_INPUT, 
	EPS, //end of terminals
	S2,
	X,//end of non terminals
	NB_SYMBOLS
}					t_test_token_id;

typedef struct		u_token_union
{
	int				ival;
	double			fval;
	char			*str;
}					t_token_union;

typedef enum		e_token_type
{
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_STR
}					t_token_type;

typedef struct		s_token
{
	t_token_type	token_type;
	t_token_union	token_union;
	t_test_token_id	token_id;
}					t_token;

# define NB_TERMS	S2
# define NB_NOTERMS	NB_SYMBOLS - NB_TERMS

typedef struct		s_symbol
{
	t_list			*productions;
	int				id;
	char			first_sets[NB_TERMS];
	char			follow_sets[NB_TERMS];
	char			debug[DEBUG_BUFFER];
	char			relevant;
	char			replacing;
}					t_symbol;

typedef struct		s_production
{
	int				index;
	t_symbol		*from;
	t_list			*symbols;
}					t_production;

typedef struct		s_state
{
	t_list			*transitions;
	t_list			*items;
	int				index;
}					t_state;

typedef struct		s_transition
{
	t_symbol		*symbol;
	t_state			*state;
}					t_transition;

typedef struct		s_item
{
	t_production	*production;
	t_list			*progress;
	t_symbol		*lookahead;
	char			parsed;
}					t_item;

typedef struct		s_cfg
{
	t_symbol		start_symbol;
	t_symbol		symbols[NB_SYMBOLS];
}					t_cfg;

typedef enum		e_action_enum
{
	ERROR,
	ACCEPT,
	SHIFT,
	REDUCE
}					t_action_enum;

typedef union		u_action_union
{
	t_state			*state;
	t_production	*production;
}					t_action_union;

typedef struct		s_action
{
	t_action_enum	action_enum;
	t_action_union	action_union;
}					t_action;

typedef struct			s_ast_node
{
	t_token				*token;
	struct s_ast_node	*parent;
	t_list				*children;
}						t_ast_node;

typedef struct			s_ast_builder
{
	t_ast_node			*node;
	t_symbol			*symbol;
}						t_ast_builder;

typedef struct		s_lr_parser
{
	t_list			*states;
	t_action		**lr_tables;
	t_cfg			cfg;
	t_list			*tokens;
	t_list			*stack;
	t_ast_node		*root;
}					t_lr_parser;

/*
** lexer.c
*/
int			ft_isseparator(char c);
int			sh_lexer(char *input);

/*
** lexer_automates.c
*/
int			sh_lexer_auto_while(int status, char c);
int			sh_lexer_auto_less(int status, char c);
int			sh_lexer_auto_great(int status, char c);
int			sh_lexer_auto_word(int status, char c);
int			sh_lexer_auto_space(int status, char c);

/*
** lexer_automates_tools.c
*/
void		sh_lexer_automate_init(t_automate automates[]);
void		sh_lexer_automate_run(t_automate automates[], char c);
int			sh_lexer_automate_check(t_automate automates[]);
void		sh_lexer_automate_show_status(t_automate automates[], char c);
void		sh_lexer_show_token(int token);


/*
** parser.c
*/
int			sh_process_test(void);
int			sh_parse_token_list(t_lr_parser *parser);
int			sh_is_term(t_symbol *symbol);
/*
** first_sets.c
*/
void		sh_init_first_sets(char first_sets[NB_TERMS]);
int			sh_compute_first_sets(t_cfg *cfg);
int			sh_compute_first_sets_str(t_cfg *cfg, char first_sets[NB_TERMS], t_list *w);
void		sh_process_transitive_first_set_2(char first_sets[NB_TERMS], int index);
void		sh_process_transitive_first_sets_2(char first_sets[NB_TERMS], t_symbol *prod_symbol);
/*
** follow_sets.c
*/
int     sh_compute_follow_sets(t_cfg *cfg);

/*
** debug.c
*/
void  	sh_print_symbol_list(t_list *symbols);
void  	sh_print_pda(t_list *symbols);
void	sh_print_symbol(t_symbol *symbol);
void	sh_print_token_list(t_list *list);
void	print_non_terminals_productions(t_cfg *cfg);
void	print_first_sets(t_cfg *cfg);
void	print_follow_sets(t_cfg *cfg);
void	sh_process_print_set(t_cfg *cfg, char sets[NB_TERMS]);
void	print_ll_table(t_cfg *cfg);
void	print_cfg(t_cfg *cfg);
void	sh_print_lr_table(t_lr_parser *parser);
void	sh_print_automata(t_lr_parser *parser, int depth);
void	sh_print_parser(t_lr_parser *parser, int depth);
void	sh_print_state(t_state *state, int depth);
void    sh_print_parser_state(t_lr_parser *parser);
void	sh_print_token(t_token *token);
void	sh_print_production(t_production *production);
void	sh_print_ast_builder(t_ast_builder *ast_builder);
void	sh_print_ast_parser(t_lr_parser *parser);

/*
** lr_parse.c
*/
int		sh_lr_parse(t_lr_parser *parser);

/*
** compute_lr_automata.c
*/
int     sh_compute_lr_automata(t_lr_parser *parser);
t_state	*sh_compute_first_state(t_lr_parser *parser);
int		sh_compute_closure(t_state *state, t_lr_parser *parser);
int		sh_compute_transitions(t_state *state, t_lr_parser *parser);

/*
** state.c
*/
t_state		*sh_new_state(void);
void		sh_free_state(t_state *state);
t_item		*sh_new_item(t_production *production, t_symbol *lookahead);

/*
** compute_lr_tables.c
*/
int     sh_compute_lr_tables(t_lr_parser *parser);

/*
** init_cfg.c
*/
int		init_context_free_grammar(t_cfg *cfg);


int		init_parsing(t_lr_parser *parser);

/*
** traverse.c
*/
int		sh_traverse(t_ast_node *node);
#endif
