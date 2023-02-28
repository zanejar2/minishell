#include "../includes/header.h"

void files_opener(t_cmd_list *list)
{
	t_cmd_list *head;

	head = list;
	while (list)
	{
		list->in = 0;
		list->out = 1;
		list->last_file = NULL;
		while (list->redirect)
		{
			if (list->redirect->type == TOKEN_LREDIRECT)
			{
				list->in = open(list->redirect->ptr, O_RDONLY, 0666);
				if (list->in < 0)
				{	
					ft_error(2);
					break;
				}
				list->last_file = list->redirect->ptr;
			}
			else if (list->redirect->type == TOKEN_RREDIRECT)
			{
				list->out = open(list->redirect->ptr, O_CREAT | O_RDWR | O_TRUNC, 0666);
				if (list->out < 0)
				{	
					ft_error(2);
					break;
				}
				list->last_file = list->redirect->ptr;
			}
			else if (list->redirect->type == TOKEN_DRREDIRECT)
			{
				list->out = open(list->redirect->ptr, O_CREAT | O_APPEND | O_RDWR, 0666);
				if (list->out < 0)
				{	
					ft_error(2);
					break;
				}
				list->last_file = list->redirect->ptr;
			}
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

void tokens_num(t_cmd_list *list)
{
    int         i;
    t_cmd_list  *head;
    t_token     *temp;

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

t_cmd_list *cmd_line_maker(t_cmd_list *list)
{
	t_cmd_list	*head;
	t_token	*temp;
	int		i;

	head = list;
	while (list)
	{
		temp = list->token;
		i = 0;
		list->cdm_line = malloc (sizeof(char *) * list->size);
		while (list->token)
		{
			if (list->token->e_type == TOKEN_ARG || list->token->e_type == TOKEN_CMD\
			|| list->token->e_type == TOKEN_DQSTRING || list->token->e_type == TOKEN_SQSTRING\
			||list->token->e_type == TOKEN_VAR)
			{	
				list->cdm_line[i] = list->token->value;
				i++;
			}
			list->token = list->token->next;
		}
		list->token = temp;
		list->cdm_line[i] = NULL;
		list = list->next;
	}
	return (head);
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
		while (env->next)
		{
			if (ft_strcmp(env->var, var) == 0)
			{
				var = env->value;
				return (var);
			}
			env = env->next;
		}
	}
	return (ft_strdup(""));
}

void	expand_variables(t_cmd_list *list, t_env *env)
{
	char		*var;
	t_cmd_list	*head;
	t_token		*temp;
	int			i;

	head = list;
	var = ft_malloc (100);
	while(list)
	{
		temp = list->token;
		while (list->token)
		{
			if (list->token->e_type == TOKEN_VAR)
				list->token->value = var_expander(list->token->value, env);
			else if (list->token->e_type == TOKEN_DQSTRING)
			{
				i = 0;
				while (list->token->value[i])
				{
					list->token->value = string_rewriter(list->token->value, env);
					i++;
				}
				// i = 0;
				// while (list->token->value[i] != '\0')
				// {
				// 	printf("%c ", list->token->value[i]);
				// 	i++;
				// }
				// exit(0);
				// printf("%c %s\n", list->token->value[i], list->token->value);
				// exit(0);
				// while (list->token->value[i])
				// {
				// 	if (list->token->value[i] == '$')
				// 	{
				// 	// printf("ok\n");
				// 		// printf("%c\n", list->token->value[i]);
				// 		// if (!list->token->value[i + 1])
				// 		// 	break;
				// 		var[0] = '$';
				// 		j = 1;
				// 		i++;
				// 		while (list->token->value[i] && list->token->value[i] != ' ')
				// 		{
				// 			var[j] = list->token->value[i];
				// 			j++;
				// 			i++;
				// 		}
				// 		var[j] = '\0';
				// 		var = var_expander(var, env);
				// 		// printf("%s\n", var);
				// 		// printf("%s\n", list->token->value);
				// 		list->token->value = string_rewriter(list->token->value, var);
				// 		// printf("%s\n", list->token->value);
				// 		// exit(0);
				// 		// printf("ok\n");
				// 	}
				// 	else
				// 		i++;
				// // }
			}
			list->token = list->token->next;
		}
		list->token = temp;
		list = list->next;
	}
	list = head;
}