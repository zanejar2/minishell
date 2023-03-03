/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:24 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 05:09:47 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_token	*token_list_last(t_token *token)
{
	if (token)
		while (token->next)
			token = token->next;
	return (token);
}

void	token_add_back(t_token **token, t_token *new)
{
	if (!*token)
		*token = new;
	else
		token_list_last(*token)->next = new;
}

t_cmd_list	*list_new(void)
{
	t_cmd_list	*new;

	new = ft_malloc(sizeof(t_cmd_list));
	new->next = NULL;
	new->token = NULL;
	return (new);
}

t_redirect	*redirect_new(t_token *token)
{
	t_redirect	*new;

	new = ft_malloc(sizeof(t_redirect));
	new->ptr = token->value;
	new->type = token->e_type;
	new->next = NULL;
	return (new);
}

int	cond_temp(t_token	*temp)
{
	if ((temp->e_type == TOKEN_LREDIRECT || \
		temp->e_type == TOKEN_RREDIRECT || \
		temp->e_type == TOKEN_DLREDIRECT || \
		temp->e_type == TOKEN_DRREDIRECT) && \
		(temp->value[0] != '<' && \
		temp->value[0] != '>'))
		return (1);
	return (0);
}
