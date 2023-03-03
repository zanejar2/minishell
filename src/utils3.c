/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:27 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 04:16:48 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*ft_strcpy(char	*dest, char	const *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char	*src)
{
	int		a;
	char	*buf;

	a = ft_strlen(src);
	buf = ft_malloc(sizeof(char) * (a + 1));
	ft_strcpy(buf, src);
	return (buf);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcount(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s == '\0')
				return (count);
		}
		i = ft_wordlen(s, c);
		s += i;
		count++;
	}
	return (count);
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
	jar = ft_malloc((count + 1) * sizeof(char *));
	i = -1;
	while (++i < count)
	{
		while (*s == c)
			s++;
		len = ft_wordlen(s, c);
		jar[i] = ft_malloc((len + 1) * sizeof(char));
		ft_strlcpy(jar[i], s, len + 1);
		s += len;
	}
	jar[i] = 0;
	return (jar);
}
