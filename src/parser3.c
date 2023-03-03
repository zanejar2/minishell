/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:21 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 09:36:13 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*get_next_char(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!str)
	{
		str = ft_malloc (sizeof(char) * 2);
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
	new_str = ft_malloc((ft_strlen(str) + 2) * sizeof(char));
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	return (new_str);
}

char	**get_next_str(char **tab_str, char *str)
{
	int		i;
	char	**new_tab;

	i = 0;
	if (!tab_str)
	{
		tab_str = ft_malloc(2 * sizeof(char *));
		tab_str[0] = str;
		tab_str[1] = NULL;
		return (tab_str);
	}
	new_tab = ft_malloc((tdm(tab_str) + 2) * sizeof(char *));
	while (tab_str[i])
	{
		new_tab[i] = tab_str[i];
		i++;
	}
	new_tab[i++] = str;
	new_tab[i] = NULL;
	return (new_tab);
}

char	*replace_var(char **tab_str, char *var, char *old_var)
{
	int		i;

	i = 0;
	while (tab_str[i])
	{
		if (!ft_strcmp(tab_str[i], old_var) && var)
		{
			tab_str[i] = var;
			break ;
		}
		else if (!ft_strcmp(tab_str[i], old_var) && !var)
		{
			tab_str[i] = "";
			break ;
		}
		i++;
	}
	return (tab_to_str(tab_str));
}

char	**inside_str_re(char *string, t_env *env, char **old_var, char **var)
{
	char	*str;
	char	**tab_str;

	g_b.i = 0;
	g_b.j = 0;
	str = NULL;
	tab_str = NULL;
	while (string[g_b.i])
	{
		if (string[g_b.i] == '$')
		{
			str = get_next_char(str, string[g_b.i++]);
			while (string[g_b.i] && ft_isalnum(string[g_b.i]))
				str = get_next_char(str, string[g_b.i++]);
			old_var[g_b.j] = str;
			var[g_b.j] = var_expander(str, env);
			g_b.j++;
		}
		else
			while (string[g_b.i] && string[g_b.i] != '$')
				str = get_next_char(str, string[g_b.i++]);
		tab_str = get_next_str(tab_str, str);
		str = NULL;
	}
	return (tab_str);
}

char	*string_rewriter(char *string, t_env *env)
{
	char	*str;
	char	**var;
	char	**old_var;
	char	**tab_str;
	char	*final;

	str = NULL;
	var = ft_malloc((ft_strlen(string) + 1) * sizeof(char *));
	old_var = ft_malloc((ft_strlen(string) + 1) * sizeof(char *));
	tab_str = inside_str_re(string, env, old_var, var);
	var[g_b.j] = NULL;
	old_var[g_b.j] = NULL;
	g_b.j = 0;
	final = string;
	while (var[g_b.j])
	{
		final = replace_var(tab_str, var[g_b.j], old_var[g_b.j]);
		g_b.j++;
	}
	return (final);
}
