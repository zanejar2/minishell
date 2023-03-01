#include "../includes/header.h"

void test(t_cmd_list *list)
{
	int i;
	while (list)
	{
		i = 0;
		// while (list->token)
		// {
		// 	// if (list->token->e_type == TOKEN_DQSTRING)
		// 	// {
		// 		// i = 0;
		// 		// while (list->token->value[i] != '\0')
		// 		// {	
		// 			// printf("%c ",list->token->value[i]);
		// 			// i++;
		// 		// }
		// 	// }
		// 	printf("TOKEN %d : %s\n", list->token->e_type, list->token->value);
		// 	list->token = list->token->next;
		// }
		// while (list->redirect)
		// {
		// 	printf("redirect %d : %s\n", list->redirect->type, list->redirect->ptr);
		// 	list->redirect = list->redirect->next;
		//  }
		while (list->cdm_line[i])
		{
			printf("cmd : %s\n", list->cdm_line[i]);
			i++;
		}
		// printf("in %d, out %d\n", list->in, list->out);
		// printf("file : %s\n", list->last_file);
		//printf("%s\n", list->redirect->ptr);
		// printf("size : %d\n", list->size);
		// printf("**********************\n");
		list = list->next;
	}
}

t_gb gb;

void *ft_malloc(int size)
{
	void *ptr;

	ptr = malloc (size);
	gb.g_c[gb.index] = ptr;
	gb.index++;
	return (ptr);
}

int main(int ac, char **av, char **env)
{
	char		*line;
	t_lexer		*lexer;
	t_cmd_list	*list;
	t_env		*env_cpy;
	(void)ac;
	(void)av;
	// (void)env;
	env_cpy = env_cpy_maker(env);
	while (1)
	{
		line = readline("MINISHELL : ");
		if (line_errors_checker(line) == 0)
			continue;
		if ((lexer = lexer_init(line)) == NULL)
		{
			ft_error(3);
			continue;
		}
		list = ft_tokenizer(lexer);
		if (token_error_check(list) == 0)
		{
			ft_error(5);
			continue;
		}
		list = redirect_retyper(list);
		list = ft_retokenizer(list);
		list = redirect_list_init(list);
		files_opener(list);
		tokens_num(list);
		expand_variables(list, env_cpy);
		list = cmd_line_maker(list);
		test(list);
		// int i = 0;
		// while (i < 2)
		// {
		// 	free(gb.g_c[i]);
		// 	printf("pointers : %s\n", gb.g_c[i]);
		// 	i++;
		// }
	}
	return (0);
}