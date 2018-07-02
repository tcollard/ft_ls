/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 10:20:56 by tcollard          #+#    #+#             */
/*   Updated: 2018/04/26 15:27:49 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	padding_multi(t_info **lst, t_padding *pad, int option[11])
{
	t_info	*tmp;

	tmp = *lst;
	init_padding(pad);
	if (option[9] == 0)
		while (tmp != NULL && tmp->type != DT_DIR)
		{
			fill_padding(tmp, pad);
			tmp = tmp->next;
		}
	else
		while (tmp != NULL)
		{
			fill_padding(tmp, pad);
			tmp = tmp->next;
		}
}

void	init_padding(t_padding *pad)
{
	pad->link = 0;
	pad->user = 0;
	pad->grp = 0;
	pad->size = 0;
	pad->total = 0;
}

void	fill_padding(t_info *lst, t_padding *pad)
{
	t_padding	new;

	new.link = ft_count_digit(lst->link);
	new.user = ft_strlen(lst->user);
	new.grp = ft_strlen(lst->grp);
	if (lst->type == DT_BLK || lst->type == DT_CHR)
		new.size = 8;
	else
		new.size = ft_count_digit(lst->size);
	(new.link > pad->link) ? pad->link = new.link : 0;
	(new.user > pad->user) ? pad->user = new.user : 0;
	(new.grp > pad->grp) ? pad->grp = new.grp : 0;
	(new.size > pad->size) ? pad->size = new.size : 0;
	pad->total += lst->blocks;
}
