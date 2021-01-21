/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:09:47 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/21 20:14:20 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	first_pass_print_files(t_context *ctx)
{
	t_entry	*cursor;
	t_entry	*next;
	int		max_len;
	int		nb_blocks;

	cursor = ctx->entries;
	nb_blocks = sum_entries_infos(ctx, cursor, true, &max_len);
	while (cursor != NULL)
	{
		if (!is_folder(ctx, cursor))
		{
			next = cursor->next;
			print_entry(ctx, cursor, max_len);
			remove_entry(&ctx->entries, cursor);
			cursor = next;
			ctx->printed_something = true;
		}
		else
			cursor = cursor->next;
	}
	if (ctx->printed_something && !ctx->long_format)
		ft_printf("\n");
	if (ctx->printed_something && ctx->entries != NULL)
		ft_printf("\n");
}

int			main(int argc, char **argv)
{
	t_context	ctx;

	ft_bzero(&ctx, sizeof(ctx));
	ctx.comp_func = &sort_by_name;
	ctx.today = time(NULL);
	parse_args(argc, argv, &ctx);
	sort_entries(&ctx, &ctx.entries);
	first_pass_print_files(&ctx);
	if (ctx.entries != NULL && ctx.entries->next == NULL)
		ctx.only_one_folder = true;
	print_folders(&ctx);
	return (ctx.return_code);
}
