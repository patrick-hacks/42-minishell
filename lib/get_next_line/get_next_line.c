/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:34:24 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/30 23:34:39 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "lib/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*strjoin(char *str1, char *str2, int str2len)
{
	int		str1len;
	char	*new_str;

	if (!str1)
	{
		str1 = (char *)malloc(1 * sizeof(char));
		str1[0] = '\0';
	}
	str1len = ft_strlen(str1);
	new_str = malloc(str1len + str2len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str1, str1len);
	ft_memcpy(new_str + str1len, str2, str2len);
	new_str[str1len + str2len] = '\0';
	free(str1);
	return (new_str);
}

static char	*get_line(char *data)
{
	int		i;
	char	*str;

	i = 0;
	if (!data[i])
		return (NULL);
	while (data[i] && data[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '\n')
	{
		str[i] = data[i];
		i++;
	}
	if (data[i] == '\n')
	{
		str[i] = data[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*save_rest(char *data)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (!data[i])
	{
		free(data);
		return (NULL);
	}
	str = malloc((ft_strlen(data) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (data[i])
		str[j++] = data[i++];
	str[j] = '\0';
	free(data);
	return (str);
}

static char	*read_until_new_line(int fd, char *data)
{
	char	*buff;
	int		read_count;

	buff = malloc((BUFFER_SIZE) * sizeof(char));
	if (!buff)
		return (NULL);
	read_count = 1;
	while (!data || (!ft_strchr(data, '\n') && read_count != 0))
	{
		read_count = read(fd, buff, BUFFER_SIZE);
		if (read_count == -1)
		{
			free(buff);
			return (NULL);
		}
		data = strjoin(data, buff, read_count);
	}
	free(buff);
	return (data);
}

char	*get_next_line(int fd)
{
	static char	*data[1030];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	data[fd] = read_until_new_line(fd, data[fd]);
	if (!data[fd])
		return (NULL);
	line = get_line(data[fd]);
	data[fd] = save_rest(data[fd]);
	return (line);
}
