#include "../includes/header.h"

t_cmd_list *ft_tokenizer(t_lexer *lexer)
{
	t_token		*token;
	t_cmd_list	*list;
	t_cmd_list	*head;

	if ((list = list_new()) == NULL)
	{
		ft_error(5);
		return (0);
	}
	head = list;
	while ((token = lexer_get_token(lexer)) != (void*)0)
	{
		if (ft_strncmp(token->value, "|", ft_strlen(token->value)) == 0)
		{
			if ((list->next = list_new()) == NULL)
			{
				ft_error(5);
				return (0);
			}
			list = list->next;
			token = lexer_get_token(lexer);
		}
		token_add_back(&list->token, token);
	}
	return (head);
}

t_cmd_list *ft_retokenizer(t_cmd_list *list)
{
	t_cmd_list	*head;
	t_token		*temp;

	head = list;
	while (list)
	{
		temp = list->token;
		while(temp)
		{
			if (temp->e_type == TOKEN_CMD)
			{
				temp = temp->next;
				while (temp)
				{
					if (temp->e_type == TOKEN_CMD)
						temp->e_type = TOKEN_ARG;
					temp = temp->next;
				}
				break;
			}
			temp = temp->next;
		}
		list = list->next;
	}
	list = head;
	return (list);
}

t_cmd_list *redirect_retyper(t_cmd_list *list)
{
    t_token     *temp;
    t_cmd_list  *head;

    head = list;
    while (list)
    {
        temp = list->token;
        while(temp)
        {
            if (temp->e_type == TOKEN_LREDIRECT)
            {
                temp->next->e_type = TOKEN_LREDIRECT;
                temp = temp->next;
            }
            else if (temp->e_type == TOKEN_RREDIRECT)
            {
                temp->next->e_type = TOKEN_RREDIRECT;
                temp = temp->next;
            }
            else if (temp->e_type == TOKEN_DLREDIRECT)
            {
                temp->next->e_type = TOKEN_DLREDIRECT;
                temp = temp->next;
            }
            else if (temp->e_type == TOKEN_DRREDIRECT)
            {
                temp->next->e_type = TOKEN_DRREDIRECT;
                temp = temp->next;
            }
            temp = temp->next;
        }
        list = list->next;
    }
    list = head;
    return (list);
}

t_redirect *redirect_list_maker(t_cmd_list *list)
{
	t_redirect	*redirect;
	t_redirect	*head;
	t_token		*temp;
	int 		flag;
	
	temp = list->token;
	redirect = malloc (sizeof(t_redirect));
	if (redirect == NULL)
	{
		ft_error(5);
		return (0);
	}
	flag = 0;
	while (temp)
	{
		while (temp &&\
			(temp->e_type == TOKEN_LREDIRECT || \
			temp->e_type == TOKEN_RREDIRECT || \
			temp->e_type == TOKEN_DLREDIRECT || \
			temp->e_type == TOKEN_DRREDIRECT) && (temp->value[0] != '<' &&\
			temp->value[0] != '>'))
		{
			if ((redirect->next = redirect_new(temp)) == NULL)
			{
				ft_error(5);
				return (0);
			}
			redirect = redirect->next;
			if (flag == 0)
				head = redirect;
			flag = 1;
			temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
	if (flag == 0)
		return (0);
	return (head);
}

t_cmd_list *redirect_list_init(t_cmd_list *list)
{
	t_cmd_list *head;

	head = list;
	while (list)
	{
		list->redirect = redirect_list_maker(list);
		list = list->next;
	}
	list = head;
	return (list);
}
