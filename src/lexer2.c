/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:11 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 04:15:30 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_token	*lexer_collect_dqstring(t_lexer *lexer)
{
	char	*string;
	char	*temp;

	lexer_advance(lexer);
	string = ft_strdup("");
	while (lexer->c != '"')
	{
		temp = lexer_convert_char_to_str(lexer);
		string = ft_strjoin(string, temp);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (token_init(TOKEN_DQSTRING, string));
}

t_token	*lexer_collect_cmd(t_lexer *lexer)
{
	char	*cmd;
	char	*temp;

	cmd = ft_strdup("");
	while (lexer->c && lexer->c != ' ' && lexer->c != '\t' && lexer->c != '<'\
	&& lexer->c != '>' && lexer->c != '|' && lexer->c != '$' && lexer->c != '"'\
	&& lexer->c != '\'')
	{
		temp = lexer_convert_char_to_str(lexer);
		cmd = ft_strjoin(cmd, temp);
		lexer_advance(lexer);
	}
	return (token_init(TOKEN_CMD, cmd));
}

char	*lexer_convert_char_to_str(t_lexer *lexer)
{
	char	*str;

	str = ft_malloc (2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_collect_sqstring(t_lexer *lexer)
{
	char	*string;
	char	*temp;

	lexer_advance(lexer);
	string = ft_strdup("");
	while (ft_strcmp(lexer_convert_char_to_str(lexer), "'"))
	{
		temp = lexer_convert_char_to_str(lexer);
		string = ft_strjoin(string, temp);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (token_init(TOKEN_SQSTRING, string));
}

t_token	*lexer_collect_arg(t_lexer *lexer)
{
	char	*arg;
	char	*temp;

	arg = ft_strdup("");
	while (lexer->c)
	{
		temp = lexer_convert_char_to_str(lexer);
		arg = ft_strjoin(arg, temp);
		lexer_advance(lexer);
	}
	return (token_init(TOKEN_ARG, arg));
}
