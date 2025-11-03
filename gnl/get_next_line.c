/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:57:34 by kizuna            #+#    #+#             */
/*   Updated: 2025/03/09 19:03:43 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline;
	char	*remaining;
	int		line_len;
	int		remaining_len;

	if (!*buffer || !**buffer)
		return (NULL);
	newline = ft_strchr(*buffer, '\n');
	if (newline)
	{
		line_len = newline - *buffer + 1;
		line = (char *)malloc((line_len + 1) * sizeof(char));
		if (!line)
			return (NULL);
		line[line_len] = '\0';
		remaining_len = ft_strlen(newline + 1);
		if (remaining_len > 0)
		{
			remaining = (char *)malloc((remaining_len + 1) * sizeof(char));
			if (!remaining)
			{
				free(line);
				return (NULL);
			}
			remaining[remaining_len] = '\0';
		}
		else
			remaining = NULL;
		line_len = 0;
		while ((*buffer)[line_len] != '\n')
		{
			line[line_len] = (*buffer)[line_len];
			line_len++;
		}
		line[line_len] = '\n';
		if (remaining)
		{
			line_len = 0;
			while (newline[line_len + 1])
			{
				remaining[line_len] = newline[line_len + 1];
				line_len++;
			}
		}
		free(*buffer);
		*buffer = remaining;
	}
	else
	{
		line = *buffer;
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*buf;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(1 * sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		buffer = ft_strjoin(buffer, buf);
		if (!buffer)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	if (bytes < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (bytes == 0 && !buffer[0])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (extract_line(&buffer));
}
