/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:03:33 by tcollard          #+#    #+#             */
/*   Updated: 2018/04/26 15:26:01 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	fill_display_2(t_info *lst, char *str, t_padding pad)
{
	char	*nb;

	if (lst->type == DT_BLK || lst->type == DT_CHR)
		str = ft_strcat(str, "3u, %3u %s %s\n\0");
	else
	{
		nb = ft_itoa(pad.size);
		str = ft_strcat(str, nb);
		free(nb);
		if (lst->type != DT_LNK || lst->lnk_path[0] == '\0')
			str = ft_strcat(str, "li %s %s\n\0");
		else
			str = ft_strcat(str, "li %s %s -> %s\n\0");
	}
}

static void	add_attribut(t_info *lst, char *str)
{
	acl_t	acl;

	acl = NULL;
	if (listxattr(lst->full_path, 0, 0, XATTR_NOFOLLOW) > 0)
		str[10] = '@';
	else if ((acl = acl_get_file(lst->full_path, ACL_TYPE_EXTENDED)) != NULL)
		str[10] = '+';
	else
		str[10] = ' ';
	acl_free(acl);
}

void		add_mode(t_info *lst, char *str)
{
	(lst->type == DT_BLK) ? str[0] = 'b' : 0;
	(lst->type == DT_CHR) ? str[0] = 'c' : 0;
	(lst->type == DT_DIR) ? str[0] = 'd' : 0;
	(lst->type == DT_FIFO) ? str[0] = 'p' : 0;
	(lst->type == DT_LNK) ? str[0] = 'l' : 0;
	(lst->type == DT_REG) ? str[0] = '-' : 0;
	(lst->type == DT_SOCK) ? str[0] = 's' : 0;
	(lst->mode & S_IRUSR) ? str[1] = 'r' : 0;
	(lst->mode & S_IWUSR) ? str[2] = 'w' : 0;
	(lst->mode & S_IXUSR) ? str[3] = 'x' : 0;
	((lst->mode & S_ISUID) && (lst->mode & S_IXUSR)) ? str[3] = 's' : 0;
	((lst->mode & S_ISUID) && !(lst->mode & S_IXUSR)) ? str[3] = 'S' : 0;
	(lst->mode & S_IRGRP) ? str[4] = 'r' : 0;
	(lst->mode & S_IWGRP) ? str[5] = 'w' : 0;
	(lst->mode & S_IXGRP) ? str[6] = 'x' : 0;
	((lst->mode & S_ISGID) && (lst->mode & S_IXGRP)) ? str[6] = 's' : 0;
	((lst->mode & S_ISGID) && !(lst->mode & S_IXGRP)) ? str[6] = 'S' : 0;
	(lst->mode & S_IROTH) ? str[7] = 'r' : 0;
	(lst->mode & S_IWOTH) ? str[8] = 'w' : 0;
	(lst->mode & S_IXOTH) ? str[9] = 'x' : 0;
	((lst->mode & S_ISVTX) && (lst->mode & S_IXOTH)) ? str[9] = 't' : 0;
	((lst->mode & S_ISVTX) && !(lst->mode & S_IXOTH)) ? str[9] = 'T' : 0;
	add_attribut(lst, str);
}

void		fill_display(t_info *lst, char *str, t_padding pad, int option[11])
{
	char	*nb;

	nb = ft_itoa(pad.link);
	str = ft_strcat(str, " %");
	str = ft_strcat(str, nb);
	free(nb);
	if (option[8] == 0)
	{
		str = ft_strcat(str, "hu %-");
		nb = ft_itoa(pad.user);
		str = ft_strcat(str, nb);
		free(nb);
		str = ft_strcat(str, "s  %-");
	}
	else
		ft_strcat(str, "hu %-");
	nb = ft_itoa(pad.grp);
	str = ft_strcat(str, nb);
	free(nb);
	str = ft_strcat(str, "s  %");
	fill_display_2(lst, str, pad);
}
