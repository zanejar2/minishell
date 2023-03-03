/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:29 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 05:09:06 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = ft_malloc(i + j + 1);
	*str = 0;
	ft_strlcat(str, s1, i + 1);
	ft_strlcat(str, s2, i + j + 1);
	return (str);
}

int	ft_strcmp(char	*s1, char	*s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (((unsigned char ) s1[i]) -((unsigned char) s2[i]));
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = ft_strlen(src);
	j = ft_strlen(dest);
	if (size <= j)
		return (size + i);
	k = 0;
	l = j;
	while (src[k] && k < size - l - 1)
	{
		dest[j] = src[k];
		k++;
		j++;
	}
	dest[j] = '\0';
	return (j + (i - k));
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	conds_temp(t_token **temp)
{
	if ((*temp)->e_type == TOKEN_LREDIRECT)
	{
		(*temp)->next->e_type = TOKEN_LREDIRECT;
		(*temp) = (*temp)->next;
	}
	else if ((*temp)->e_type == TOKEN_RREDIRECT)
	{
		(*temp)->next->e_type = TOKEN_RREDIRECT;
		(*temp) = (*temp)->next;
	}
	else if ((*temp)->e_type == TOKEN_DLREDIRECT)
	{
		(*temp)->next->e_type = TOKEN_DLREDIRECT;
		(*temp) = (*temp)->next;
	}
	else if ((*temp)->e_type == TOKEN_DRREDIRECT)
	{
		(*temp)->next->e_type = TOKEN_DRREDIRECT;
		(*temp) = (*temp)->next;
	}
}
