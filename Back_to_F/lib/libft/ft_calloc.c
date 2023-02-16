/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:15:08 by mla-rosa          #+#    #+#             */
/*   Updated: 2022/09/26 18:22:07 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		*str;
	size_t	n;

	n = count * size;
	if (n == 1 && count != 1)
		return (NULL);
	str = malloc(n);
	if (!(str))
		return (0);
	ft_bzero(str, n);
	return ((void *)str);
}
