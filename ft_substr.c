/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprivite <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:46:25 by sprivite          #+#    #+#             */
/*   Updated: 2024/01/16 14:46:27 by sprivite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if ((int)(len + start) > ft_strlen(s))
		len = ft_strlen(s) - (size_t)start;
	ret = (char *)ft_calloc(sizeof(char), (len + 1));
	if (ret == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= (size_t)start && j < len && s[i])
		{
			ret[j++] = s[i];
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
