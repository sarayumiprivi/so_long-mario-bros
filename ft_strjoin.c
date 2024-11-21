/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprivite <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:47:44 by sprivite          #+#    #+#             */
/*   Updated: 2024/01/17 15:54:23 by sprivite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	end;
	unsigned int	len2;
	char			*ret;
	unsigned int	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	len2 = ft_strlen(s2);
	end = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (end + len2 + 1));
	if (ret == NULL)
		return (NULL);
	while (i < end)
	{
		ret[i] = s1[i];
		i++;
	}
	while (i < end + len2)
	{
		ret[i] = s2[i - end];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
