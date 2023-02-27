#include "../includes/header.h"

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(char const *s, char a, char b)
{
	int	count;
	int	i;

	count = 0;
	while (*s)
	{
		while (*s == a || *s == b)
		{
			s++;
			if (*s == '\0')
				return (count);
		}
		i = ft_wordlen(s, a);
		s += i;
		count++;
	}
	return (count);
}

char	**new_split(char *s, char c)
{
	int		count;
	int		len;
	int		i;
	char	**jar;

	if (!s)
		return (0);
	count = ft_wordcount(s, c);
	jar = (char **)malloc((count + 1) * sizeof(char *));
	if (jar == NULL)
		return (0);
	i = -1;
	while (++i < count)
	{
		while (*s == c)
			s++;
		len = ft_wordlen(s, c);
		jar[i] = (char *)malloc((len + 1) * sizeof(char));
		if (jar[i] == NULL)
			return (0);
		ft_strlcpy(jar[i], s, len + 1);
		s += len;
	}
	jar[i] = 0;
	return (jar);
}

char	*string_rewriter(char *string, char *var, char *old_var)
{
	char	*new_str;
	char	**string_list;
	int		i;

	string_list = ft_split(string, ' ');
	i = 0;
	while(string_list[i])
	{
		if (!ft_strcmp(string_list[i], old_var))
			string_list[i] = var;
		i++;
	}
	// printf("%s\n", string_list[0]);
	i = 0;
	while (string_list[i + 1])
	{
		// printf("ok\n");
		new_str = ft_strjoin(string_list[i], string_list[i + 1]);
		i++;
	}
	// printf("%s\n", new_str);
	return (new_str);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		len;
	int		i;
	char	**jar;

	if (!s)
		return (0);
	count = ft_wordcount(s, c);
	jar = (char **)malloc((count + 1) * sizeof(char *));
	if (jar == NULL)
		return (0);
	i = -1;
	while (++i < count)
	{
		while (*s == c)
			s++;
		len = ft_wordlen(s, c);
		jar[i] = (char *)malloc((len + 1) * sizeof(char));
		if (jar[i] == NULL)
			return (0);
		ft_strlcpy(jar[i], s, len + 1);
		s += len;
	}
	jar[i] = 0;
	return (jar);
}