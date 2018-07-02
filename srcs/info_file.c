/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:05:27 by tcollard          #+#    #+#             */
/*   Updated: 2018/06/01 13:38:31 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	modif_time(long int st_time, t_info **lst)
{
	char	*str;
	int		i;

	i = 12;
	str = ft_strdup(ctime(&st_time));
	((*lst)->time != NULL) ? free((*lst)->time) : 0;
	if ((time(0) - st_time) > 16070400 || (time(0) - st_time) < -16070400)
	{
		ft_memmove(str, str + 4, 7);
		if (st_time < 253402300740)
			ft_memmove(str + 7, str + 19, 5);
		else
		{
			str[8] = '\0';
			ft_strcat(str, "10000");
			i += 1;
		}
	}
	else
		ft_memmove(str, str + 4, 12);
	str[i] = 0;
	(*lst)->time = ft_strdup(str);
	free(str);
}

void		info_file(char *path, t_info **lst, unsigned char type,
			int option[11])
{
	int			i;
	t_info		*tmp;
	struct stat	buf;

	i = ft_strlen(path);
	while (i >= 0)
		if (path[i] == '/' && i != 0)
			break ;
		else
			i -= 1;
	if ((option[2] == 0 && path[i + 1] == '.' && option[9] == 0) || (!(tmp =
					(t_info *)malloc(sizeof(t_info)))))
		return ;
	init_lst(&tmp);
	((i + 1) != (int)ft_strlen(path)) ? ft_strcpy(tmp->name,
	(&path[i + 1])) : ft_strcpy(tmp->name, path);
	ft_strcpy(tmp->full_path, path);
	tmp->type = type;
	i = 0;
	(lstat(path, &buf) == -1) ? i = fill_lstruct(tmp, path, option) :
		fill_struct(buf, tmp, option);
	(tmp->type == DT_LNK && i != 1) ? i = fill_lstruct(tmp, path, option) : 0;
	(i != -1) ? sort_alpha(lst, &tmp, option) : free(tmp);
}

static void	fill_init_struct(t_info *lst, struct stat buf, int option[11])
{
	struct passwd	*id;
	struct group	*gr;
	long int		time;

	id = NULL;
	gr = NULL;
	time = 0;
	lst->mode = buf.st_mode;
	lst->link = buf.st_nlink;
	lst->size = buf.st_size;
	if (!(id = getpwuid(buf.st_uid)))
		lst->user = ft_itoa(buf.st_uid);
	else
		lst->user = ft_strdup(id->pw_name);
	if (!(gr = getgrgid(buf.st_gid)))
		lst->grp = ft_itoa(buf.st_gid);
	else
		lst->grp = ft_strdup(gr->gr_name);
	if (option[6] == 0)
		time = buf.st_mtime;
	else
		time = buf.st_atime;
	modif_time(time, &lst);
	lst->i_time = time;
	lst->blocks = buf.st_blocks;
}

int			fill_lstruct(t_info *lst, char *path, int option[11])
{
	struct stat		buf;
	char			new_path[PATH_MAX];
	ssize_t			size;

	if (lstat(path, &buf) == -1)
		return (-1);
	size = 0;
	(lst->user != NULL) ? free(lst->user) : 0;
	(lst->grp != NULL) ? free(lst->grp) : 0;
	fill_init_struct(lst, buf, option);
	ft_bzero(new_path, PATH_MAX);
	lst->type = style(buf);
	size = readlink(path, new_path, PATH_MAX);
	if (size == -1)
	{
		ft_error(2, path, 0);
		ft_bzero(lst->name, PATH_MAX);
		ft_strcat(lst->name, path);
	}
	else
		ft_strncpy(lst->lnk_path, new_path, size);
	return (0);
}

void		fill_struct(struct stat buf, t_info *lst, int option[11])
{
	(lst->type == 0) ? lst->type = style(buf) : 0;
	lst->time = NULL;
	lst->rdev = buf.st_rdev;
	lst->next = NULL;
	lst->prev = NULL;
	fill_init_struct(lst, buf, option);
}
