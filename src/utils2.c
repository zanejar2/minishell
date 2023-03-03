/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:25 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 09:35:58 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_env	*env_list_maker(char	**str)
{
	t_env	*env;

	env = ft_malloc (sizeof(t_env));
	env->var = str[0];
	env->value = str[1];
	env->next = NULL;
	return (env);
}

void	env_add_back(t_env **list, t_env *node)
{
	t_env	*head;

	head = *list;
	if (head == NULL)
	{
		*list = node;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = node;
	node->next = NULL;
}

t_env	*env_cpy_maker(char **env)
{
	t_env	*env_cpy;
	char	**tmp;
	int		i;

	env_cpy = NULL;
	if (!env)
	{
		env_cpy->var = ft_strdup("");
		env_cpy->value = ft_strdup("");
		env_cpy->next = NULL;
		return (env_cpy);
	}
	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		env_add_back(&env_cpy, env_list_maker(tmp));
		i++;
	}
	return (env_cpy);
}

int	tdm(char **arr)
{
	int	a;

	if (arr[0] == NULL)
		return (0);
	a = 0;
	while (arr[a] != NULL)
		a++;
	return (a);
}

char	*tab_to_str(char **tab_str)
{
	char	*final_str;
	int		i;

	i = 0;
	final_str = ft_strdup("");
	while (tab_str && tab_str[i])
	{
		if (tab_str[i][0] != '\0')
			final_str = ft_strjoin(final_str, tab_str[i]);
		i++;
	}
	return (final_str);
}
