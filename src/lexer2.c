#include "../includes/header.h"

t_token	*lexer_collect_dqstring(t_lexer *lexer)
{
	char *string;
	char *temp;

	lexer_advance(lexer);
	string = malloc(1);
	if (string == NULL)
		ft_error(3);
	string[0] = '\0';
	while(lexer->c != '"')
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
	char *cmd;
	char *temp;

	cmd = malloc(1);
	if (cmd == NULL)
		ft_error(3);
	cmd[0] = '\0';
	while(lexer->c && lexer->c != ' ' && lexer->c != '\t' && lexer->c != '<'\
	&& lexer->c != '>' && lexer->c != '|' && lexer->c != '$')
	{
		temp = lexer_convert_char_to_str(lexer);
		cmd = ft_strjoin(cmd, temp);
		lexer_advance(lexer);
	}
	return (token_init(TOKEN_CMD, cmd));
}

char	*lexer_convert_char_to_str(t_lexer *lexer)
{
	char *str;
	str = malloc (2);
	if (str == NULL)
		return (0);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token *lexer_collect_sqstring(t_lexer *lexer)
{
	char *string;
	char *temp;

	lexer_advance(lexer);
	string = malloc(1);
	if (string == NULL)
		ft_error(3);
	string[0] = '\0';
	while(ft_strncmp(lexer_convert_char_to_str(lexer), "'", 1))
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
	char *arg;
	char *temp;

	arg = malloc(1);
	if (arg == NULL)
		ft_error(3);
	arg[0] = '\0';
	while(lexer->c)
	{
		temp = lexer_convert_char_to_str(lexer);
		arg = ft_strjoin(arg, temp);
		lexer_advance(lexer);
	}
	return (token_init(TOKEN_ARG, arg));
}