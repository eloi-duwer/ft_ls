/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:10:29 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/21 19:10:31 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		sort_by_name(t_entry *one, t_entry *two)
{
	if (one == NULL || two == NULL)
		return (0);
	return (ft_strcmp(one->filename, two->filename));
}

int		sort_by_date(t_entry *one, t_entry *two)
{
	if (one == NULL || two == NULL)
		return (0);
	if (two->stats.st_mtim.tv_sec == one->stats.st_mtim.tv_sec)
		return ((int)(two->stats.st_mtim.tv_nsec - one->stats.st_mtim.tv_nsec));
	return ((int)(two->stats.st_mtim.tv_sec - one->stats.st_mtim.tv_sec));
}

void	sort_entries(t_context *ctx, t_entry **first_entry)
{
	t_entry	*cursor;
	int		res;

	cursor = *first_entry;
	while (cursor != NULL && cursor->next != NULL \
		&& cursor->next->sorted == false)
	{
		res = ctx->comp_func(cursor, cursor->next);
		if ((ctx->sort_reverse == false && res > 0) \
			|| (ctx->sort_reverse == true && res < 0))
		{
			swap_adjacent_entries(first_entry, cursor, cursor->next);
			cursor = *first_entry;
		}
		else
			cursor = cursor->next;
	}
	cursor = *first_entry;
	while (cursor != NULL && cursor->sorted == false)
	{
		cursor->sorted = true;
		cursor = cursor->next;
	}
}
