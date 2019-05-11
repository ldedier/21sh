/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_word_by_index.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:04:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/05/06 15:55:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_word_len(char *s, int index)
{
	int i;

	i = index;
	while (s[i])
	{
		if (ft_isseparator(s[i]))
			return (i - index);
		i++;
	}
	return (i - index);
}

int		process_populate_empty_word(t_word *word)
{
	if (!(word->str = ft_strdup("")))
		return (1);
//	ft_printf("ADDRESS (NONE): %p (%s)\n", word->str, word->str);
	word->len = 0;
	word->utf8_len =  0;
	word->index_byte_offset = 0;
	word->index_char_offset = 0;
	return (0);
}

int		process_populate_word_by_index(t_word *word,
			int nb_words, int parseword, int index)
{
	word->word_index = (parseword ? nb_words : 0);
	if (!word->word_index)
		word->start_index = index;
	word->prev_word_index = nb_words;
	if (word->word_index)
	{
		word->len = get_word_len(word->to_compare, word->start_index);
		if (!(word->str = ft_strndup(&word->to_compare[word->start_index], word->len)))
			return (1);
//		ft_printf("ADDRESS: %p (%s)\n", word->str, word->str);
		word->utf8_len = ft_strlen_utf8(word->str);
	}
	else
		return (process_populate_empty_word(word));
	return (0);
}

void	increment_word(int i, int index, t_word *word, char *str)
{
	word->start_index = i;
	word->index_byte_offset = index - i;
	word->index_char_offset = ft_strnlen_utf8(&str[i], index - i);
}

int		populate_word_by_index(char *s, int index, t_word *word)
{
	int nb_w;
	int parseword;
	int i;

	i = 0;
	parseword = 0;
	nb_w = 0;
	word->str = NULL;
	word->to_compare = s;
	while (s[i])
	{
		if (i == index)
			return (process_populate_word_by_index(word, nb_w, parseword, index));
		if (!ft_isseparator(s[i]) && !parseword)
		{
			increment_word(i, index, word, s);
			parseword = 1;
			nb_w++;
		}
		if (ft_isseparator(s[i]) && parseword)
			parseword = 0;
		i++;
	}
	if (i == index)
		return (process_populate_word_by_index(word, nb_w, parseword, index));
	return (0);
}