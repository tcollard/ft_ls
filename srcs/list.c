/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:06:17 by tcollard          #+#    #+#             */
/*   Updated: 2018/05/31 18:17:48 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	init_lst(t_info **lst)
{
	(*lst)->time = NULL;
	(*lst)->user = NULL;
	(*lst)->grp = NULL;
	(*lst)->next = NULL;
	(*lst)->prev = NULL;
}

void	del_lst(t_info **lst)
{
	t_info	*tmp;
	t_info	*save;

	tmp = *lst;
	save = *lst;
	while (tmp != NULL)
	{
		*lst = tmp->next;
		free(tmp->time);
		free(tmp->user);
		free(tmp->grp);
		free(tmp);
		tmp = *lst;
	}
}

int		lst_length(t_info **lst)
{
	int		i;
	t_info	*tmp;

	i = 0;
	tmp = *lst;
	if (!(*lst))
		return (0);
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i += 1;
	}
	return (i);
}

void	get_link_files(char *path, int option[11])
{
	DIR				*dirp;
	struct dirent	*data;
	t_info			*lst;
	char			tmp[PATH_MAX];

	lst = NULL;
	data = NULL;
	if (!(dirp = opendir(path)))
		return (perror("ls :"));
	while ((data = readdir(dirp)))
	{
		get_path(tmp, path, data);
		info_file(tmp, &lst, data->d_type, option);
	}
	display(&lst, option);
	(closedir(dirp) == -1) ? (perror("ls:")) : 0;
	del_lst(&lst);
}
