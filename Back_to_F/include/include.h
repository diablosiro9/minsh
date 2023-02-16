/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:33:27 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/02/14 12:19:50 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"

typedef struct s_env
{
	char			*name;
	char			*content;
	int				num_vars;
	struct s_env	*next;
}
t_env;


// enum struct
typedef struct s_token
{ 
	enum s_type
	{
		PIPE,
		REDIR,
		RREDIR, //infile
		WORD,
		QUOTE,
		SQUOTE,
		DOLLAR,
		OPTION,
		COMMAND
	} t_type;
	char *value;
	struct s_token	*next;
} t_token;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct t_data {
	t_list	*list;
	t_env	*env;
	t_token	*token;
}	t_data;

t_data		g_data;





//------------------------------------exec.c------------------------------------

int   ft_exec(t_list *str);
//------------------------------------utils.c------------------------------------
t_list	*ft_lstnew(void *content);
t_list *ft_lstadd(t_list **alst, t_list *new);
int ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
char *ft_strsub(char const *s, unsigned int start, size_t len);
void ft_putstr(char *str);
int	ft_strcmp(char *s1, char *s2);
char **ft_split (char *str);
void afftab(char **tab);
void afflist(t_list *list, char *name);
void init_type( int type, char *value);
t_token *tokenizateur(t_list *list);
void ft_putchar(char c);
char	*search_env_content(t_env *env, char *name);
int	checking_str(char *ref, char *find);
void	*split_cmd_file();
//------------------------------------- main.c -------------------------------------
t_env *get_env(char **env);
t_list *lexer(t_list *str);
int main(int ac, char **av, char **env);
//-------------------------------------- cd.c --------------------------------------
void	ft_env(char	*s);
void	ft_unset();
void	ft_pwd();
void	ft_exit(int nb);

#endif
