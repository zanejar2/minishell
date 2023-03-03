/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:18 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 05:07:40 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_cmd_list	*ft_tokenizer(t_lexer *lexer)
{
	t_token		*token;
	t_cmd_list	*list;
	t_cmd_list	*head;

	list = list_new();
	head = list;
	token = lexer_get_token(lexer);
	while (token != (void *)0)
	{
		if (ft_strcmp(token->value, "|") == 0)
		{
			list->next = list_new();
			list = list->next;
			token = lexer_get_token(lexer);
		}
		token_add_back(&list->token, token);
		token = lexer_get_token(lexer);
	}
	return (head);
}

t_cmd_list	*ft_retokenizer(t_cmd_list *list)
{
	t_cmd_list	*head;
	t_token		*temp;

	head = list;
	while (list)
	{
		temp = list->token;
		while (temp)
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
				break ;
			}
			temp = temp->next;
		}
		list = list->next;
	}
	return (head);
}

t_cmd_list	*redirect_retyper(t_cmd_list *list)
{
	t_token		*temp;
	t_cmd_list	*head;

	head = list;
	while (list)
	{
		temp = list->token;
		while (temp)
		{
			conds_temp(&temp);
			temp = temp->next;
		}
		list = list->next;
	}
	list = head;
	return (list);
}

t_redirect	*redirect_list_maker(t_cmd_list *list)
{
	t_redirect	*redirect;
	t_redirect	*head;
	t_token		*temp;
	int			flag;

	temp = list->token;
	redirect = ft_malloc (sizeof(t_redirect));
	flag = 0;
	while (temp)
	{
		while (temp && cond_temp(temp))
		{
			redirect->next = redirect_new(temp);
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

t_cmd_list	*redirect_list_init(t_cmd_list *list)
{
	t_cmd_list	*head;

	head = list;
	while (list)
	{
		list->redirect = redirect_list_maker(list);
		list = list->next;
	}
	list = head;
	return (list);
}
