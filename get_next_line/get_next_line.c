/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouzalm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:33:04 by tbouzalm          #+#    #+#             */
/*   Updated: 2022/08/18 16:33:12 by tbouzalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*get_next_line(int fd)
{
	if (fd < 0)
		return (NULL);
	char	*ret = malloc(99999);
	if (!ret)
		return (NULL);
	int	r, rd = 0;
	r = read(fd, ret + rd, 1);
	rd += r;
	while (r != 0 && ret[rd - 1] != '\n')
	{
		r = read(fd, ret + rd, 1);
		rd += r;
		if (r == -1)
		{
			free(ret);
			return (NULL);
		}
	}
	ret[rd] = '\0';
	if (!ret || !*ret)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
