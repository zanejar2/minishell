/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:20 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 07:32:19 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	files_opener(t_cmd_list *list)
{
	t_cmd_list	*head;

	head = list;
	while (list)
	{
		list->in = 0;
		list->out = 1;
		list->last_file = NULL;
		while (list->redirect)
		{
			real_opener(&list);
			if (list->in != 0 && list->redirect->next != NULL)
				close (list->in);
			if (list->out != 1 && list->redirect->next != NULL)
				close (list->out);
			list->redirect = list->redirect->next;
		}
		list = list->next;
	}
	list = head;
}

void	tokens_num(t_cmd_list *list)
{
	int			i;
	t_cmd_list	*head;
	t_token		*temp;

	head = list;
	while (list)
	{
		temp = list->token;
		i = 1;
		while (list->token)
		{
			i++;
			list->token = list->token->next;
		}
		list->size = i;
		list->token = temp;
		list = list->next;
	}
	list = head;
}

t_cmd_list	*cmd_line_maker(t_cmd_list *list)
{
	t_cmd_list	*head;
	t_token		*temp;
	int			i;

	head = list;
	while (list)
	{
		temp = list->token;
		i = 0;
		list->cdm_line = ft_malloc (sizeof(char *) * list->size);
		while (list->token)
		{
			if (list->token->e_type == TOKEN_ARG || \
			list->token->e_type == TOKEN_CMD \
			|| list->token->e_type == TOKEN_DQSTRING || \
			list->token->e_type == TOKEN_SQSTRING \
			||list->token->e_type == TOKEN_VAR)
				list->cdm_line[i++] = list->token->value;
			list->token = list->token->next;
		}
		list->token = temp;
		list->cdm_line[i] = NULL;
		list = list->next;
	}
	return (head);
}

char	*var_expander(char *var, t_env *env)
{
	if (var != NULL)
	{
		if (!ft_strcmp(var, "$"))
			return (var);
		var++;
		if (ft_isdigit(*var))
		{
			var++;
			return (var);
		}
		while (env)
		{
			if (ft_strcmp(env->var, var) == 0)
			{
				var = env->value;
				return (var);
			}
			env = env->next;
		}
	}
	return ("");
}

void	expand_variables(t_cmd_list *list, t_env *env)
{
	t_cmd_list	*head;
	t_token		*temp;

	head = list;
	while (list)
	{
		temp = list->token;
		while (list->token)
		{
			if (list->token->e_type == TOKEN_VAR)
				list->token->value = var_expander(list->token->value, env);
			else if (list->token->e_type == TOKEN_DQSTRING)
				list->token->value = string_rewriter(list->token->value, env);
			list->token = list->token->next;
		}
		list->token = temp;
		list = list->next;
	}
	list = head;
}
