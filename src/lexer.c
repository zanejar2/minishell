/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:09 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 02:58:10 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_lexer	*lexer_init(char *content)
{
	t_lexer	*lexer;

	lexer = ft_malloc(sizeof(t_lexer));
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content))
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
}

t_token	*lexer_get_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content) && \
	lexer->c != '\n')
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespaces(lexer);
		if (lexer->c == '\'')
			return (lexer_collect_sqstring(lexer));
		if (lexer->c == '"')
			return (lexer_collect_dqstring(lexer));
		if (lexer->c == '$')
			return (lexer_collect_var(lexer));
		if (lexer->c == '|')
			return (lexer_collect_pipe(lexer));
		if (lexer->c == '<')
			return (lexer_collect_lredirect(lexer));
		if (lexer->c == '>')
			return (lexer_collect_rredirect(lexer));
		if (ft_isprint(lexer->c))
			return (lexer_collect_cmd(lexer));
		lexer_advance(lexer);
	}
	return (0);
}

t_token	*lexer_advance_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}
