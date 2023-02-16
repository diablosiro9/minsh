/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:32:59 by mla-rosa          #+#    #+#             */
/*   Updated: 2023/02/16 14:54:32 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

// Pourquoi refaire un ft_putchar alors que tu l'as déjà fait dans ton libft ?
void ft_putchar(char c)
{
    write(1, &c, 1);
}



// Quasiment parfaitement propre (check malloccc)


// Dans le directory lexer de préférence
// t_list *lexer(t_list *str)
// {
//     t_list *list;
//     char **tab;
// 	char *tp = (char *)str->content;
//     int i = 0;
//     t_list *tmp = malloc(sizeof(t_list) * 100); // Check tes mallocs mon coeuuurrrrr
//     if (!tmp)
//     {
//         printf("malloc error\n");
//         exit(-127);
//     }
//     tab = ft_split(tp);
//     while (tab[i])
//     {
//         list = ft_lstnew(tab[i]);
//         list->next = tmp;
//         tmp = list;
//         i++;
//     }
// 	//printf("TAB VA SUIVRE---->\n");
// 	//afftab(tab);
//     afflist(list, "Lexer");
//     printf("je vois avant tokenizateur\n");
//     tokenizateur(list);
//     //printf("sortie\n");
//     return (list);
// }

/* by mathieu
Le soucis c'est que tu fais un list->next = tmp et apparament ca faisait un peu n'importe quoi
Donc vaut mieux utiliser une fonction que tu as faites comme ft_lstadd qui elle meme te rajoute une node a la fin
ensuite a chaque fois tu realloues list donc tu auras des leaks alors que tu peux directement donner en argument ft_lstnew 
a ton ft_lstadd, ensuite ton tab recupere les espaces. 
*/

int check_name(char *str, t_list *name)
{
    while (name)
    {
        if (ft_strcmp(str, (char *)name->content) == 0)
            return (1);
        name = name->content;
    }
    return (0);
}

int closed_elem(char *str, char c)
{
	int i = 0;
	// int	start = 0;
	// int	end = ft_strlen(str) - 1;
	int flag = 0;
	int counter = 0;
	char *start = ft_strchr(str, c);
	if (start == NULL)
		return (1);
	while (start[i])
	{
		if (counter == 1 && start[i] == c)
		{
			counter = 0;
			flag = 0;
		}
		if (flag == 1 && start[i] == c)
		{
			counter = 1;
			flag = 0;
		}
		if (start[i] == c && counter != 1)
			flag = 1;
		i++;
	}
	return (counter);
}

int checking_closed(char *tp)
{
	if (!tp)
		return (-2);
	int val_test = closed_elem(tp, '"');
	if (val_test == 0)
		return (0);
	val_test = closed_elem(tp, '\'');
	if (val_test == 0)
		return (-1);
	return (val_test);
}

t_list *lexer(t_list *str)
{
    t_list *list;
    int i;
    char **tab = NULL;

    i = 0;
    list = NULL;
    tab = ft_split((char *)str->content);
    while (tab[i])
    {
        ft_lstadd(&list, ft_lstnew(tab[i]));
        i++;
    }
    afflist(list, "Lexer");
    tokenizateur(list);
    return (list);
}

void afftoken(t_token *list, char *name)
{
    (void)name;
    while (list)
    {
        printf("\e[0;31mToken : [%s]\e[0m", list->value);
        printf("\e[0;31mToken : [%d]\n\e[0m", list->t_type);
        list = list->next;
    }
}

int	token_size()
{
	int	i = 0;
	t_data	ptr = g_data;

	if (g_data.token)
	{
		while (g_data.token)
		{
			i++;
			g_data.token = g_data.token->next;
		}
	}
	g_data = ptr;
	return (i);
}

void	checking_solo_name(t_token *tmp)
{
	if (token_size() == 1)
	{
		if (tmp->t_type == 4 || tmp->t_type == 5 || tmp->t_type == 6 
				|| tmp->t_type == 1 || tmp->t_type == 2 )
		{
			if (ft_strlen(tmp->value) < 2)
			{
				if (tmp->t_type == 6)
					printf("Us_Bash: $: command not found\n");
				else if (tmp->t_type == 1 || tmp->t_type == 2)
				{
					printf("Us_Bash2: syntax error near unexpected token 'newline'\n");
				}
				return ;
			}
		}
	}
}

void	*manage_double();

void	*solo_command()
{
	//CRASH SI LE SEUL TOKEN RECU EST UNE REDIR RREDIR PIPE OU OPTION
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() == 1 && tmp->t_type != 3)
	{
		checking_solo_name(tmp);
		g_data.token = tmp;
	}
	// else
	// {
	// 	printf("Liste de tokens superieur à 1 ou seul un Token_Word\n");
	// 	if (manage_double() == NULL)
	// 	{
	// 		printf("noooon\n");
	// 		return (NULL);
	// 	}
	// }
	// SI SEUL TOKEN EST UN WORD, PEUT ETRE UN FILE OU UNE COMMANDE (CMD PEUT ETRE EXEC SEULE COMME ECHO)
		// DOLLAR PEUT AUSSI, DQUOTE SQUOTE AUSSI 
	printf("fin\n");
	return ((void *)g_data.token->value);
}

void	*manage_double()
{
	t_token	*tmp;

	tmp = g_data.token;
	if (token_size() > 1)
	{
		while (tmp)
		{
			if (tmp->t_type == 0 && tmp->next->t_type == 0)
			{
				printf("Us_Bash: syntax error near unexpected token '|'\n");
				return (NULL);
			}
			tmp = tmp->next;
		}
	}
	return ((void *)g_data.token->value);
}

void	*find_all_dollars()
{
	t_token	*tmp = g_data.token;

	if (tmp)
	{
		while (tmp)
		{
			if (tmp->t_type == 6)
			{
				if (ft_strlen(tmp->value) > 1)
				{
					tmp->value = search_env_content(g_data.env, tmp->value);
					//printf("tmp->value -- %s\n", tmp->value);
					// if (tmp->value == NULL && tmp->next == NULL) //si return null et que dautres '$' apparaissent apres, tu fais quoi ? 
					// 	return (NULL);
				}
				else
					printf("Us_Bash: $: command not found\n");
			}
			tmp = tmp->next;
		}
	}
	return ((void *)g_data.token->value);
}

int	ft_check_c(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int	count_char_c(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			count++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	return (count);
}

char	*ft_alloc_str(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
void	free_tab(char **cmd);

char	**ft_oldsplit(char const *s, char c)
{
	int		i;
	int		nb_c;
	char	**dst;

	i = 0;
	if (s == NULL)
		return (NULL);
	nb_c = count_char_c(s, c);
	dst = (char **)malloc(sizeof(char *) * (nb_c + 1));
	if (dst == NULL)
		return (NULL);
	nb_c = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			dst[nb_c] = ft_alloc_str((s + i), c);
			nb_c++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	dst[nb_c] = NULL;
	return (dst);
}


char	*ft_strjoin_bis(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (size));
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

// char	*get_env_bis(char *path, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], path, ft_strlen(path)))
// 			return (env[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*get_path(char **env, char *cmd)
// {
// 	int		i;
// 	char	*tmp1;
// 	char	*tmp2;
// 	char	**path;

// 	i = 0;
// 	if (access(cmd, X_OK) == 0)
// 		return (ft_strdup(cmd));
// 	path = ft_oldsplit(get_env_bis("PATH=", env) + 5, ':');
// 	if (path == NULL)
// 		return (NULL);
// 	while (path[i])
// 	{
// 		tmp1 = ft_strjoin_bis(path[i], "/");
// 		tmp2 = ft_strjoin_bis(tmp1, cmd);
// 		free(tmp1);
// 		if (access(tmp2, X_OK) == 0)
// 		{
// 			free_tab(path);
// 			return (tmp2);
// 		}
// 		free(tmp2);
// 		i++;
// 	}
// 	free_tab(path);
// 	return (NULL);
// }

void	free_tab(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i] != NULL)
		free(cmd[i++]);
	free(cmd);
}

void	*split_cmd_file()
{
	t_token	*tmp = g_data.token;
	char	*path;
	char	**tab_path;
	char	*tmp1;
	char	*tmp2;
	int		i = 0;

	if (tmp)
	{
		while (tmp)
		{
			//printf("al\n");
			if (tmp->t_type == 3)
			{
				if (ft_strlen(tmp->value) > 1)
				{
					//printf("tmp->value == %s\n", tmp->value);
					path = search_env_content(g_data.env, "$PATH");
					printf("sorti\n");
					tab_path = ft_oldsplit(path, ':');
					path = tmp->value;
					//printf("path == %s\n", path);
					i = 0;
					while (tab_path[i])
					{
						tmp1 = ft_strjoin_bis(tab_path[i], "/");
						tmp2 = ft_strjoin_bis(tmp1, path);
						free(tmp1);
						if (access(tmp2, X_OK) == 0)
						{
							//printf("ACCESS RETURN 0\n");
							free_tab(tab_path);
							tmp->t_type = COMMAND;
							tmp->value = tmp2;
							//printf("AVANT LENVOIE == %s\n", tmp2);
							//ft_exec(tmp2);// je la recup ici pour le moment car tu me fais deja le acces
							//et y a donc le path complet vers la commande a executer
							return (tmp2);
						}
						free(tmp2);
						i++;
					}
					free_tab(tab_path);
					// if (tmp->value == NULL && tmp->next == NULL) //si return null et que dautres '$' apparaissent apres, tu fais quoi ? 
					// 	return (NULL);
				}
			}
			tmp = tmp->next;
		}
	}
	printf("fin split cmd file\n");
	return ((void *)g_data.token->value);
}

void	*parsor(t_list *str)
{
	// t_list	*list = NULL;
	// int		i = 0;
	afflist(str, "PARSOR");
	if (find_all_dollars() == NULL)
		return (NULL);
	if (solo_command() == NULL)
		return (NULL);
	else if (manage_double() == NULL)
		return (NULL);
	afftoken(g_data.token, "G_DATA_TOKEN");
	//printf("fin parsor\n");
	split_cmd_file();
	afftoken(g_data.token, "G_DATA_TOKEN");
	//printf("g_data.token->value == %s\n", g_data.token->value);
	//printf("fin parsor\n");
	
	// REATTRIBUTION DUNE NOUVELLE LISTE DE TOKEN SANS LES TRUCS INUTILES (SI DOUBLE OPTION, RENVOIE SANS LE SECOND);

	// SI UN TOKEN WORD OK, SI UN Token_Pipe, UN Token_Option, UN Token_Redir, OU UN Token_Rredir, sans rien, ERROR
		// NE PEUT AVOIR QUE LES TOKEN WORD, DQUOTE/SQUOTE, DOLLARS EN SOLO, les autres need something
	// REGLE NUMERO DEUX, CHECKER SI CHAQUE Token_Word EST UNE COMMANDE OU UN FICHIER D'ENTREE OU SORTIE
		//Reattrib une 
	// return (str);
	return (NULL);
}

void	delete_token(t_token **l)
{
	t_token	*tmp;

	tmp = (*l);
	while ((*l) != NULL)
	{
		tmp = (*l);
		(*l) = (*l)->next;
		free(tmp);
	}
	free(*l);
}

int main(int ac, char **av, char **env)
{
	t_list	*history = NULL;
    t_list *str = NULL;
	history = ft_lstnew(NULL);
    g_data.env = get_env(env);
    (void)ac;
    (void)av;
	printf("tu sors\n");
    while (42)
	{
		// g_data.token = (t_token *)malloc(sizeof(t_token));
	 	ft_putstr("minishell>");
        str = ft_lstnew(get_next_line(0));
		ft_lstadd(&history, str);
		if (checking_closed((char *)str->content) != 0 && checking_closed((char *)str->content) != -1)
 	    {  
			str = lexer(str);
			parsor(str);
			//printf("la str == %s\n", (char *)str->content);
			ft_exec(str); //il devrait etre la mais d'ici je get pas la commande je la get pour le moment depuis le split_cmd_file.
		}
		delete_token(&g_data.token);
	}
    return (0);
}
