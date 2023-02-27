#include "../includes/header.h"

t_token	*lexer_collect_var(t_lexer *lexer)
{
	char	*var;
	char	*temp;

	var = malloc (1);
	if (var == NULL)
		ft_error(3);
	var[0] = '\0';
	temp = lexer_convert_char_to_str(lexer);
	var = ft_strjoin(var, temp);
	lexer_advance(lexer);
	while ((ft_isalnum(lexer->c) || lexer->c == '_') && lexer->c != '$')
	{
		temp = lexer_convert_char_to_str(lexer);
		var = ft_strjoin(var, temp);
		lexer_advance(lexer);
	}
	return (token_init(TOKEN_VAR, var));
}

t_token	*lexer_collect_pipe(t_lexer *lexer)
{
	char *pipe;

	pipe = lexer_convert_char_to_str(lexer);
	if (pipe == 0)
		ft_error(3);
	lexer_advance(lexer);
	return (token_init(TOKEN_PIPE, pipe));
}

t_token	*lexer_collect_lredirect(t_lexer *lexer)
{
	char *lredirect;

	lredirect = lexer_convert_char_to_str(lexer);
	if (lredirect == 0)
		ft_error(3);
	lexer_advance(lexer);
	if (lexer->c == '<')
	{
		lredirect = ft_strjoin(lredirect, lexer_convert_char_to_str(lexer));
		lexer_advance(lexer);
		return (token_init(TOKEN_DLREDIRECT, lredirect));
	}
	return (token_init(TOKEN_LREDIRECT, lredirect));
}

t_token	*lexer_collect_rredirect(t_lexer *lexer)
{
	char *rredirect;

	rredirect = lexer_convert_char_to_str(lexer);
	if (rredirect == 0)
		ft_error(3);
	lexer_advance(lexer);
	if (lexer->c == '>')
	{
		rredirect = ft_strjoin(rredirect, lexer_convert_char_to_str(lexer));
		lexer_advance(lexer);
		return (token_init(TOKEN_DRREDIRECT, rredirect));
	}
	return (token_init(TOKEN_RREDIRECT, rredirect));
}
