/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:57:03 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/03 02:57:25 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	ft_error(int errno)
{
	if (errno == 5)
		write(2, "Syntax error\n", 14);
	else if (errno == 3)
		write(2, "Allocation error\n", 18);
	else if (errno == 2)
		write(2, "File opening failure\n", 21);
}

int	pipe_check(char *line)
{
	int	i;
	int	flag;

	i = 0;
	while (line[i])
	{
		flag = 0;
		if (line[0] == '|')
			return (0);
		if (line[i] == '|')
		{	
			i++;
			if (line[i] == '\0')
				return (0);
			while (line[i] && line[i] != '|')
			{	
				if (ft_isprint(line[i]) && line[i] != ' ' && line[i] != '\t')
					flag = 1;
				i++;
			}
			i--;
			if (flag == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	redirect_doubles_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '>')
			return (0);
		else if (line[i] == '>' && line[i + 1] == '<')
			return (0);
		if ((line[i] == '<' || line[i] == '>') && \
		(line[i + 1] == '<' || line[i + 1] == '>'))
		{	
			if (line[i + 2] == '<' || line[i + 2] == '>')
				return (0);
		}
		i++;
	}
	return (1);
}

int	quotes_check(char *line)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{	
			d++;
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i])
				d++;
		}
		else if (line[i] == '\'')
		{	
			s++;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i])
				s++;
		}
		i++;
	}
	if (d % 2 != 0 || s % 2 != 0)
		return (0);
	return (1);
}

int	line_errors_checker(char *line)
{
	if (ft_strcmp(line, "") == 0)
		return (0);
	if (quotes_check(line) == 0)
	{	
		ft_error(5);
		return (0);
	}
	if (redirect_doubles_check(line) == 0)
	{	
		ft_error(5);
		return (0);
	}
	if (pipe_check(line) == 0)
	{
		ft_error(5);
		return (0);
	}
	return (1);
}
