#include "../includes/header.h"

int redirect_files_check(t_cmd_list *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list->token;
		while (temp)
		{
			if (temp->e_type == TOKEN_LREDIRECT || \
			temp->e_type == TOKEN_RREDIRECT || \
			temp->e_type == TOKEN_DLREDIRECT || \
			temp->e_type == TOKEN_DRREDIRECT)
			{
				if (!temp->next || (temp->next->e_type != TOKEN_ARG &&\
				temp->next->e_type != TOKEN_CMD))
					return (0);
			}
			temp = temp->next;
		}
		list = list->next;
	}
	return (1);
}

int token_error_check(t_cmd_list *list)
{
	if (redirect_files_check(list) == 0)
		return (0);
	return (1);
}