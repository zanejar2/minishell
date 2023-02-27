#include "../includes/header.h"

t_token *token_list_last(t_token *token)
{
	if (token)
		while (token->next)
			token = token->next;
	return (token);
}

void token_add_back(t_token **token, t_token *new)
{
	if (!*token)
		*token = new;
	else
		token_list_last(*token)->next = new;
}

t_cmd_list	*list_new(void)
{
	t_cmd_list	*new;

	new = malloc(sizeof(t_cmd_list));
	if (new == NULL)
	{
		ft_error(5);
		return (0);
	}
	new->next = NULL;
	new->token = NULL;
	return (new);
}

t_redirect *redirect_new(t_token *token)
{
	t_redirect *new;

	new = malloc(sizeof(t_redirect));
	if (new == NULL)
	{
		ft_error(5);
		return (0);
	}
	new->ptr = token->value;
	new->type = token->e_type;
	new->next = NULL;
	return (new);
}