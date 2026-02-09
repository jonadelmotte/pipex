/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:44:04 by jdelmott          #+#    #+#             */
/*   Updated: 2026/01/28 11:33:57 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**split_free(char **split, int k)
{
	while (k--)
		free(split[k]);
	free(split);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != '\0' && s[i] != c) && (s[i + 1] == '\0' || s[i + 1] == c))
			count++;
		i++;
	}
	return (count - 1);
}

static void	remplissage(char *split, char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		split[i] = (char)s[i];
		i++;
	}
	split[i] = '\0';
}

static char	**mathilda(char **split, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	split[count_words(s, c) + 1] = NULL;
	while (k <= count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		split[k] = ft_calloc(sizeof(char), (j + 1));
		if (split[k] == NULL)
			return (split_free(split, k));
		remplissage(split[k], &s[i], c);
		i += j;
		j = 0;
		k++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;

	words = count_words(s, c);
	split = (char **)ft_calloc(sizeof(char *), (words + 2));
	if (split == NULL)
		return (0);
	if (!s[0])
		return (split);
	return (mathilda(split, s, c));
}
