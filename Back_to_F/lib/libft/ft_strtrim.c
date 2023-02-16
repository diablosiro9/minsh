/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:15:58 by mla-rosa          #+#    #+#             */
/*   Updated: 2021/11/29 12:12:46 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		idx[2];
	char	*dst;

	if (!s1 || !set)
		return (NULL);
	idx[0] = 0;
	while (s1[idx[0]] && ft_is_set(s1[idx[0]], set))
		idx[0]++;
	idx[1] = ft_strlen(s1) - 1;
	while (idx[1] > idx[0] && ft_is_set(s1[idx[1]], set))
		idx[1]--;
	if (!set || ft_strlen(s1) < ft_strlen(set))
		return (ft_strdup(s1));
	dst = malloc(sizeof(char) * (idx[1] - idx[0] + 2));
	if (!dst)
	{
		free(dst);
		return (NULL);
	}
	i = 0;
	while (idx[0] <= idx[1])
		dst[i++] = s1[idx[0]++];
	dst[i] = '\0';
	return (dst);
}
