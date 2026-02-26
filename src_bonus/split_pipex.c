/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:03:36 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/26 12:05:22 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_split(char **split, int count)
{
	while (count--)
		free(split[count]);
	free(split);
	exit(1);
}

static int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str[0] || !str)
		return (0);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
		{
			if (str[i] == 34 || str[i] == 39)
			{
				i++;
				while (str[i] != 34 && str[i] != 39 && str[i])
					i++;
			}
			i++;
		}
	}
	return (count);
}

static int	get_words(const char *str, char c)
{
	int	j;

	j = 0;
	while (str[j] != c && str[j])
	{
		if (str[j] == 34 || str[j] == 39)
		{
			j++;
			while (str[j] != 34 && str[j] != 39 && str[j])
				j++;
		}
		j++;
	}
	return (j);
}

static char	**do_split(char **split, const char *str, char c)
{
	int	words;
	int	i;
	int	j;

	i = 0;
	words = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] == c && str[i])
			i++;
		j = get_words(&str[i], c);
		split[words] = ft_calloc(sizeof(char), j + 1);
		if (!split[words])
			free_split(split, words);
		ft_strlcpy(split[words], (char *)&str[i], j + 1);
		i += j;
		words++;
		if (words == count_words(str, c))
			break ;
	}
	split[words] = NULL;
	return (split);
}

char	**split_pipex(char *str, const char sep)
{
	char	**split;
	int		words;

	if (!str)
		return (NULL);
	words = count_words(str, sep);
	split = ft_calloc(sizeof(char *), words + 1);
	if (split == NULL)
		return (0);
	if (!str[0] || words == 0)
		return (split);
	return (do_split(split, str, sep));
}

/*int	main(int argc, char *argv[])
{
	(void)argc;
	int i = 0;
	char **split;

	printf("words = %i\n", count_words(argv[1], argv[2][0]));
	split = ft_split(argv[1], argv[2][0]);
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}*/