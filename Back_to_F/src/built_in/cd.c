/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:34:36 by dojannin          #+#    #+#             */
/*   Updated: 2023/02/18 15:33:16 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

/*
	echo et l’option -n
◦ cd uniquement avec un chemin relatif ou absolu
◦ pwd sans aucune option
◦ export sans aucune option
◦ unset sans aucune option
◦ env sans aucune option ni argument
◦ exit sans aucune option
*/


// SI LANCEMENT DU MINISHELL ON VIRE JUSTE AVANT LANCEMENT L'ENV AVEC UN UNSET, LE MINISHELL DOIT SE TROUVER OU CREER UN ENV,
// UN PWD, OU UN OLD_PWD, ET UN HOME POUR TENIR LA ROUTE, AINSI QUE DES PATH. Fixer avant l'env

//ECHO SEC ➜ 
//  Back_to_F git:(main) ✗ echo test | cat -e
// test$
// ➜  Back_to_F git:(main) ✗ echo -n test | cat -e
// test%                              

void	ft_exit(int nb)
{
	//Limite de 255 comme valeur de retour, apres faire des modulos pour "fit" par rapport a 255 (un cas tricky a veri aupres de max)
	if (!nb)
	{	
		printf("exit\n");
		exit(1);
	}
	else
	{
		if (nb > 255)
			exit(nb % 255);
		else
			exit(nb);
	}
}

void	ft_cd(char *path)
{
	if (chdir(path) != 0)
        perror("Erreur execve");
}

void	ft_pwd(void)
{
	char	pwd[1000];
	char	*tmp = NULL;
	
	tmp = getcwd(pwd, sizeof(pwd));
	if (tmp == NULL)
		return ;
	printf(" PATH DIRECTORY-- %s\n", tmp);
	return ;
}

unsigned int	starter_env(char *s)
{
	unsigned int	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}


char *ft_sub(char const *s, unsigned int start, size_t len)
{
    char *str = NULL;
    size_t i;

    i = 0;
    // if (!s)
    //     return (NULL);
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    while (i < len)
    {
        str[i] = s[start + i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

t_env	*ft_envnew(char *name, char *content, int i)
{
	(void)i;
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
	
}

void	ft_envadd(t_env **lst, t_env *new)
{
	t_env	*tmp = NULL;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (*lst)
		tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}


t_env *get_env(char **env)
{
    int i = 0;
    t_env *list = NULL;
    
    // list = malloc(sizeof(t_env *) * 1000);
    // if (!list)
    // {
    //     printf("malloc error\n");
    //     exit(-127);
    // }
    while (env[i])
    {
		// list = ft_envnew(ft_sub(env[i], 0, ft_strchr(env[i], '=') - env[i]), \
		// ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i])), i);
        ft_envadd(&list, ft_envnew(ft_sub(env[i], 0, ft_strchr(env[i], '=') - env[i]), \
		ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i])), i));
		// list[i].content =  ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i]));
		// list[i].next = NULL;
		i++;
    }
	list->num_vars = i;
    return (list);
}

void	ft_env(char	*s)
{
	t_env	*tmp = NULL;

	tmp = g_data.env;
	if (tmp != NULL)
	{
		if (s == NULL)
		{
			while (tmp != NULL)
			{
				printf("%s%s\n", tmp->name, tmp->content);
				tmp = tmp->next;
			}
		}
		else
		{
			while (tmp != NULL)
			{
				if (ft_strncmp(s, tmp->content, ft_strlen(s)) == 0)
				{
					printf("%s\n", tmp->content);
					return ;
				}
				else
				{
					if (tmp->next != NULL)
						tmp = tmp->next;
				}
			}
		}
	}
}


t_env *delete_node(t_env* head, int position) {
    if (head == NULL) {
        // la liste est vide
        return head;
    }
    // supprime le premier élément
    if (position == 0) {
       	t_env* new_head = head->next;
        free(head);
        return new_head;
    }
    // supprime un élément dans la liste
    t_env* current = head;
    for (int i = 0; current != NULL && i < position - 1; i++) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        // la position est en dehors de la liste
        return head;
    }
    t_env* next_node = current->next->next;
    free(current->next);
    current->next = next_node;
    return head;
}

void	ft_unset(char *name)
{
	char	*path = NULL;
	t_env	*tmp = g_data.env;
	t_env	*head = tmp;
	int		i = 0;

	if (!name)
		return ;
	printf("la \n");
	printf("name == %s\n", name);
	path = search_env_content(g_data.env, name);
	if (path == NULL)
		return ;
	if (path != NULL)
	{
		while (strcmp(tmp->name, name) != 0 && tmp)
		{
			tmp = tmp->next;
			i++;
		}
		if (strcmp(tmp->name, name) == 0)
			delete_node(g_data.env, i);
	}
	tmp = head;
}

/* Obtenir l'env grace a la struct global et le print dans un tmp. Parcourir jusquau bout. 
	Cette fonction doit etre lance avant l'exec generale (builtin tricky)
		->Si possible obtenir les cmd des le debut, identifier les redir, gerer les fd pour l'entree, 
		identifier le reste des builtins tricky et return en fonction
		Sinon lancer pleinement l'exec avec les param need (redir determinee (INT), cmd (CHAR **), fd[0])
			->fd[0] correspond au file d'entree, redir a notre sortie, 
	Dans la fonction exec on reverifie les builtins, puis les path de la dite cmd,\
	dup2(fd, stdin_fileno), dup redir stdout si elle est valablem un tmp prendra le path de cmd[0]
	Execv tout ca dans un fork, close les fd et redir, waitpid, return;
*/

// void	check_exec()
// {
// 	t_token	*tmp = NULL;
	
// 	tmp = g_data.token;
// }