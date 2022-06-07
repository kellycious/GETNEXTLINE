/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khuynh <khuynh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:30:31 by khuynh            #+#    #+#             */
/*   Updated: 2022/05/20 15:52:26 by khuynh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* 1.check que le fichier est bien lisible, et nb d'octets lu n'est pas nul
   2. stocker la ligne lue, join les lignes entre elle 
   3. malloc it 
   4. free la memoire deja renvoyee pour ne garder que les lignes suivantes
   bonus: 4096 is a default size buffer
		use [fd] so it can read multiple fd at once */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (0);
	str[fd] = linereader(str[fd], fd);
	if (!str[fd])
		return (0);
	line = linecpy(str[fd]);
	str[fd] = savenfree(str[fd]);
	if (line[0] == '\0')
	{
		free(str[fd]);
		free(line);
		return (0);
	}
	return (line);
}

// lire le fichier

char	*linereader(char *str, int fd)
{
	char	*reader;
	int		nbytrd;

	reader = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!reader)
		return (0);
	nbytrd = 1;
	while (nbytrd != 0 && !ft_strchr(str, '\n'))
	{
		nbytrd = read(fd, reader, BUFFER_SIZE);
		if (nbytrd == -1)
		{
			free(reader);
			return (0);
		}
		reader[nbytrd] = '\0';
		str = ft_strjoin(str, reader);
	}
	free(reader);
	return (str);
}

// +2 pour le carac nul + le \n

char	*linecpy(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	s = malloc(sizeof(char) * (i + 2));
	if (!s)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

//malloc en enlevant bien le str deja renvoye pour ne garder que ce qu'il reste

char	*savenfree(char *str)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	save = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!save)
		return (0);
	i++;
	j = 0;
	while (str[i])
	{
		save[j++] = str[i++];
	}
	save[j] = '\0';
	free(str);
	return (save);
}
