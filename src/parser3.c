#include "../includes/header.h"

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

char	*tab_to_str(char **tab_str)
{
	char	*final_str;
	int		i;

	i = 0;
	final_str = "";
	while (tab_str && tab_str[i])
	{
		if (tab_str[i][0] != '\0')
			final_str = ft_strjoin(final_str, tab_str[i]);
		i++;
	}
	return (final_str);
}

char	*replace_var(char **tab_str, char *var)
{
	int		i;

	i = 0;
	while (tab_str[i])
	{
		if (tab_str[i][0] == '$' && var)
		{
			// free(tab_str[i]);
			tab_str[i] = var;
			break;
		}
		else if (tab_str[i][0] == '$' && !var)
		{
			// free(tab_str[i]);
			tab_str[i] = ft_strdup("");
			break;
		}
		i++;
	}
	return (tab_to_str(tab_str));
}

char	*string_rewriter(char *string, t_env *env)
{
	char	*str;
	char	**var;
	char	**tab_str;
	char	*final; 
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = NULL;
	tab_str = NULL;
	var = ft_malloc(10 * sizeof(char **));
	while (string[i])
	{
		if (string[i] == '$')
		{
			str = get_next_char(str, string[i++]);
			while (string[i] && ft_isalnum(string[i]))
				str = get_next_char(str, string[i++]);
			// printf("%s\n", str);
			var[j] = var_expander(str, env);
			// printf("%s\n", var[j]);
			j++;
		}
		else
			while (string[i] && string[i] != '$')
				str = get_next_char(str, string[i++]);
		tab_str = get_next_str(tab_str, str);
		str = NULL;
	}
	var[j] = NULL;
	// j = 0;
	// while (var[j])
	// {
	// 	printf("var : %s\n", var[j]);
	// 	j++;
	// }
	// while (tab_str[j])
	// {
	// 	printf("tab :%s\n", tab_str[j]);
	// 	j++;
	// }
	// exit(0);
	j = 0;
	while (var[j])
	{
			// printf("var : %s\n", var[j]);
		final = replace_var(tab_str, var[j]);

	// printf("%s\n", final);
		j++;
	}
	
	// exit(0);
	return (final);
}