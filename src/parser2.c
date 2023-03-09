/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:20 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 01:12:41 by zanejar          ###   ########.fr       */
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
		list->lst_fl_type = -1;
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

int	quotes_finder(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}

int	export_norm(t_token *token)
{
	if (ft_strcmp(token->value, "export") == 0 \
	&& token->next && token->next->next \
	&& token->next->next->e_type == 2 \
	&& quotes_finder(token->next->value))
		return (1);
	return (0);
}

void	cmd_line_maker(t_cmd_list *list)
{
	g_b.head = list;
	while (list)
	{
		g_b.temp = list->token;
		g_b.i = 0;
		list->cdm_line = ft_malloc (sizeof(char *) * list->size);
		while (g_b.temp)
		{
			g_b.exp = NULL;
			if (g_b.temp->e_type >= 0 && g_b.temp->e_type <= 4)
			{
				list->cdm_line[g_b.i++] = g_b.temp->value;
				if (export_norm(g_b.temp))
				{
g_b.exp = ft_strjoin(g_b.temp->next->value, g_b.temp->next->next->value);
					g_b.temp = g_b.temp->next;
				}
			}
			g_b.temp = g_b.temp->next;
			if (g_b.exp != NULL && g_b.temp)
				g_b.temp->value = g_b.exp;
		}
		list->cdm_line[g_b.i] = NULL;
		list = list->next;
	}
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
