/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:23 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/04 02:37:14 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_token	*token_init(int type, char *value)
{
	t_token	*token;

	token = ft_malloc (sizeof(t_token));
	token->e_type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	more_opener1(t_cmd_list **list)
{
	(*list)->in = open((*list)->redirect->ptr, O_RDONLY, 0666);
	if ((*list)->in < 0)
	{	
		ft_error(FILE_OPENING_ERROR);
		return ;
	}
	(*list)->last_file = (*list)->redirect->ptr;
	(*list)->lst_fl_type = TOKEN_LREDIRECT;
}

void	more_opener2(t_cmd_list **list)
{
	(*list)->out = open((*list)->redirect->ptr, \
	O_CREAT | O_RDWR | O_TRUNC, 0666);
	if ((*list)->out < 0)
	{	
		ft_error(FILE_OPENING_ERROR);
		return ;
	}
	(*list)->last_file = (*list)->redirect->ptr;
	(*list)->lst_fl_type = TOKEN_RREDIRECT;
}

void	more_opener3(t_cmd_list **list)
{
	(*list)->out = open((*list)->redirect->ptr, \
	O_CREAT | O_APPEND | O_RDWR, 0666);
	if ((*list)->out < 0)
	{
		ft_error(FILE_OPENING_ERROR);
		return ;
	}
	(*list)->last_file = (*list)->redirect->ptr;
	(*list)->lst_fl_type = TOKEN_DRREDIRECT;
}

void	real_opener(t_cmd_list **list)
{
	if ((*list)->redirect->type == TOKEN_LREDIRECT)
		more_opener1(list);
	else if ((*list)->redirect->type == TOKEN_RREDIRECT)
		more_opener2(list);
	else if ((*list)->redirect->type == TOKEN_DRREDIRECT)
		more_opener3(list);
}
