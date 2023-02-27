#include "../includes/header.h"

t_token *token_init(int type, char *value)
{
	t_token *token;

	token = malloc (sizeof(t_token));
	if (token == NULL)
		return (0);
	token->e_type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}