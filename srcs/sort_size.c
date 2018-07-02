/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:09:47 by tcollard          #+#    #+#             */
/*   Updated: 2018/04/26 15:28:14 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	swap(t_info **tmp1, t_info **tmp2, t_info **lst)
{
	((*tmp1)->prev != NULL) ? (*tmp1)->prev->next = *tmp2 : 0;
	((*tmp2)->next != NULL) ? (*tmp2)->next->prev = *tmp1 : 0;
	(*tmp1)->next = (*tmp2)->next;
	(*tmp2)->next = *tmp1;
	(*tmp2)->prev = (*tmp1)->prev;
	(*tmp1)->prev = *tmp2;
	((*tmp2)->prev == NULL) ? *lst = *tmp2 : 0;
	*tmp1 = *lst;
	*tmp2 = (*tmp1)->next;
	return (1);
}

static int	final_size(t_info **lst)
{
	t_info	*tmp1;
	t_info	*tmp2;
	int		ret;

	ret = 0;
	if (!(*lst) || (*lst)->next == NULL)
		return (ret);
	tmp1 = *lst;
	tmp2 = tmp1->next;
	while (tmp2 != NULL)
		if (tmp1->size < tmp2->size || (tmp1->size == tmp2->size &&
			ft_strcmp(tmp1->name, tmp2->name) >= 0))
			ret = swap(&tmp1, &tmp2, lst);
		else
		{
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	return (ret);
}

static void	swap_comb(t_info **tmp1, t_info **tmp2, t_info **lst)
{
	t_info	*tmp;

	tmp = (*tmp2)->next;
	(*tmp2)->next = (*tmp1)->next;
	(*tmp1)->next->prev = *tmp2;
	(*tmp1)->next = tmp;
	(tmp != NULL) ? (*tmp1)->next->prev = *tmp1 : 0;
	tmp = (*tmp2)->prev;
	(*tmp2)->prev = (*tmp1)->prev;
	((*tmp1)->prev != NULL) ? (*tmp1)->prev->next = *tmp2 : 0;
	(*tmp1)->prev = tmp;
	(*tmp1)->prev->next = *tmp1;
	tmp = *tmp2;
	*tmp2 = *tmp1;
	*tmp1 = tmp;
	((*tmp1)->prev == NULL) ? *lst = *tmp1 : 0;
}

static int	comb_sort(t_info **lst, t_info *tmp1, t_info *tmp2)
{
	int		ret;

	ret = 0;
	while (tmp2 != NULL)
	{
		if (tmp1->size < tmp2->size && tmp1->next == tmp2)
			ret = swap(&tmp1, &tmp2, lst);
		else if (tmp1->size < tmp2->size)
		{
			swap_comb(&tmp1, &tmp2, lst);
			ret = 1;
		}
		else
		{
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}
	return (ret);
}

void		sort_size(t_info **lst)
{
	t_info	*tmp;
	int		gap;
	int		size_lst;
	int		i;
	int		ret;

	ret = 0;
	if (!(*lst) || (*lst)->next == NULL)
		return ;
	tmp = *lst;
	size_lst = lst_length(lst);
	gap = size_lst;
	while (gap > 1 || ret == 1)
	{
		i = 0;
		tmp = *lst;
		if ((gap = gap / 1.25) < 1)
			gap = 1;
		while (i++ < gap)
			tmp = tmp->next;
		(gap != 1) ? ret = comb_sort(lst, *lst, tmp) : 0;
		(gap == 1) ? ret = final_size(lst) : 0;
	}
}
