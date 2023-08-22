/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabeel <knabeel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:25:26 by knabeel           #+#    #+#             */
/*   Updated: 2022/10/03 17:45:09 by knabeel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *string, int find)
{
	int		i;

	i = 0;
	if (string == NULL)
		return (NULL);
	if (string[i] == (char)find)
		return ((char *)&string[ft_strlen(string)]);
	while (string[i])
	{
		if (string[i] == (char)find)
			return ((char *)&string[i]);
		i++;
	}
	return (0);
}

char	*ft_str_init(void)
{
	char	*str;

	str = (char *)malloc(1 * sizeof(char));
	str[0] = 0;
	return (str);
}

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_str_init();
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = 0;
	free(s1);
	return (str);
}
// int main(void)
// {
// 	char b[] = "";
// 	char a[] = "hello";
// 	char *g;
// 	g = ft_strjoin(b,a);
// 	printf("%s", g);
// }
// char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	int		len;
// 	char	*copy;

// 	i = 0;
// 	len = ft_strlen(s1);
// 	copy = (char *)malloc(sizeof(char) * len + 1);
// 	if (copy == NULL)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		copy[i] = s1[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }