/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:00 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 01:13:12 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	test(t_cmd_list *list)
{
	t_cmd_list	*head;
	int			i;
	head = list;
	while (list)
	{
		i = 0;
		// while (list->token)
		// {
		// 	// if (list->token->e_type == TOKEN_DQSTRING)
		// 	// {
		// 	// 	i = 0;
		// 	// 	while (list->token->value[i] != '\0')
		// 	// 	{	
		// 	// 		printf("%c ",list->token->value[i]);
		// 	// 		i++;
		// 	// 	}
		// 	// }
		// 	printf("TOKEN %d : %s\n", list->token->e_type, list->token->value);
		// 	list->token = list->token->next;
		// }
		// while (list->redirect)
		// {
			// printf("redirect %d : %s\n",\
			// list->redirect->type, list->redirect->ptr);
		// 	list->redirect = list->redirect->next;
		//  }
		while (list->cdm_line[i])
		{
			printf("cmd : %s\n", list->cdm_line[i]);
			i++;
		}
		printf("in %d, out %d\n", list->in, list->out);
		printf("file : %s, type : %d\n", list->last_file, list->lst_fl_type);
		// // printf("size : %d\n", list->size);
		printf("**********************\n");
		list = list->next;
	}
	list = head;
}

void	ft_error(int errno)
{
	if (errno == 5)
		write(2, "Syntax error\n", 14);
	else if (errno == 2)
		write(2, "File opening failure\n", 21);
}

void	*ft_malloc(int size)
{
	void	*ptr;

	ptr = malloc (size);
	g_b.g_c[g_b.index] = ptr;
	g_b.index++;
	return (ptr);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_lexer		*lexer;
	t_cmd_list	*list;
	t_env		*env_cpy;

	(void)ac;
	(void)av;
	env_cpy = env_cpy_maker(env);
	while (1)
	{
		line = readline("MYSHELL : ");
		if (line_errors_checker(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		lexer = lexer_init(line);
		list = ft_tokenizer(lexer);
		if (token_error_check(list) == 0)
			continue ;
		list = redirect_retyper(list);
		list = ft_retokenizer(list);
		list = redirect_list_init(list);
		files_opener(list);
		tokens_num(list);
		expand_variables(list, env_cpy);
		cmd_line_maker(list);
		test(list);
	}
	return (0);
}
