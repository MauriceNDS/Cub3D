/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:47:13 by adel-sol          #+#    #+#             */
/*   Updated: 2021/01/05 10:11:58 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int		my_strchr(const char *s, int c, int ret)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (i);
	if (s[i] == '\0' && ret == 0)
		return (-2);
	return (-1);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = malloc(sizeof(*res) * (ft_strlen(s1) + 1))))
		return (0);
	while ((res[i] = s1[i]) != '\0')
		i++;
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		size1;
	int		size2;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!(res = malloc(sizeof(char) * (size1 + size2 + 1))))
		return (NULL);
	i = -1;
	while (++i < size1)
		res[i] = s1[i];
	while (i < size1 + size2)
	{
		res[i] = s2[i - size1];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (!s || !(res = malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	if (start >= ft_strlen(s))
	{
		res[0] = '\0';
		return (res);
	}
	while (i < len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
