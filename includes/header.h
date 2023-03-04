/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:58:35 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/05 00:28:20 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include<stdio.h>
# include<unistd.h>
# include<string.h>
# include<stdlib.h>
# include<limits.h>
# include<fcntl.h>
# include<readline/readline.h>
# include<readline/history.h>
# define SYNTAX_ERROR 5
# define FILE_OPENING_ERROR 2

typedef struct s_token
{
	enum
	{
		TOKEN_CMD,
		TOKEN_ARG,
		TOKEN_DQSTRING,
		TOKEN_SQSTRING,
		TOKEN_VAR,
		TOKEN_PIPE,
		TOKEN_LREDIRECT,
		TOKEN_RREDIRECT,
		TOKEN_DLREDIRECT,
		TOKEN_DRREDIRECT,
	}				e_type;
	char			*value;
	struct s_token	*next;
}				t_token;

typedef struct s_lexer
{
	char			c;
	char			*content;
	unsigned int	i;
}				t_lexer;

typedef struct s_redirect
{
	char				*ptr;
	int					type;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_cmd_list
{
	t_token					*token;
	int						size;
	char					**cdm_line;
	t_redirect				*redirect;
	char					*last_file;
	char					lst_fl_type;
	int						in;
	int						out;
	struct s_cmd_list		*next;
}				t_cmd_list;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_gb
{
	void	*g_c[1000000];
	int		index;
	int		i;
	int		j;
	int		flag;
	int		d;
	int		s;
}				t_gb;

t_gb	g_b;

void		*ft_malloc(int size);

void		lexer_advance(t_lexer *lexer);
void		lexer_skip_whitespaces(t_lexer *lexer);
char		*lexer_convert_char_to_str(t_lexer *lexer);
t_lexer		*lexer_init(char *content);
t_token		*lexer_get_token(t_lexer *lexer);
t_token		*lexer_collect_dqstring(t_lexer *lexer);
t_token		*lexer_collect_sqstring(t_lexer *lexer);
t_token		*lexer_collect_cmd(t_lexer *lexer);
t_token		*lexer_advance_token(t_lexer *lexer, t_token *token);
t_token		*token_init(int type, char *value);
t_token		*lexer_collect_flags(t_lexer *lexer);
t_token		*lexer_collect_var(t_lexer *lexer);
t_token		*lexer_collect_pipe(t_lexer *lexer);
t_token		*lexer_collect_lredirect(t_lexer *lexer);
t_token		*lexer_collect_rredirect(t_lexer *lexer);
t_token		*lexer_collect_arg(t_lexer *lexer);

void		ft_error(int errno);
int			line_errors_checker(char *line);
int			quotes_check(char *line, int i, int d, int s);
int			vars_init(char *line);
int			pipe_check(char *line);
int			redirect_doubles_check(char *line);
int			redirect_files_check(t_cmd_list *list);
int			token_error_check(t_cmd_list *list);
int			cmd_cheker(t_cmd_list *list);

t_cmd_list	*ft_tokenizer(t_lexer *lexer);
t_cmd_list	*ft_retokenizer(t_cmd_list *list);
t_cmd_list	*redirect_retyper(t_cmd_list *list);
t_redirect	*redirect_list_maker(t_cmd_list *list);
t_cmd_list	*redirect_list_init(t_cmd_list *list);
int			cond_temp(t_token	*temp);
void		conds_temp(t_token **temp);

void		token_add_back(t_token **token, t_token *new);
t_cmd_list	*list_new(void);
t_token		*list_last(t_token *token);
t_redirect	*redirect_new(t_token *token);
t_cmd_list	*cmd_line_maker(t_cmd_list *list);
void		tokens_num(t_cmd_list *list);

void		files_opener(t_cmd_list *list);
void		real_opener(t_cmd_list **list);

void		expand_variables(t_cmd_list *list, t_env *env);
char		*var_expander(char *var, t_env *env);

t_env		*env_cpy_maker(char **env);
void		env_add_back(t_env **list, t_env *node);
t_env		*env_list_maker(char	**str);

int			tdm(char **arr);
char		**get_next_str(char **tab_str, char *str);
char		*tab_to_str(char **tab_str);
char		*replace_var(char **tab_str, char *var, char *old_var);
char		*string_rewriter(char *string, t_env *env);

char		*ft_strdup(const char	*src);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(char	*s1, char	*s2);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_isalnum(int x);
int			ft_isalpha(int x);
int			ft_isdigit(int x);
int			ft_isprint(int x);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif