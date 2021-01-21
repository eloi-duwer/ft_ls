/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_folder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:32:18 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/21 20:20:16 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		print_entries_in_folder(t_context *ctx, t_entry *entry)
{
	t_entry *cursor;
	t_entry	*next;

	cursor = entry->files;
	while (cursor != NULL)
	{
		print_entry(ctx, cursor, entry->max_length);
		next = cursor->next;
		if (ctx->recursive && file_type(cursor, FOLDER_MASK) && \
			ft_strcmp(cursor->filename, ".") != 0 && \
				ft_strcmp(cursor->filename, "..") != 0)
			add_entry_beginning(ctx, &ctx->entries, cursor->path, \
				cursor->filename);
		remove_entry(&entry->files, cursor);
		cursor = next;
	}
}

static void		do_print_folder(t_context *ctx, t_entry *entry, \
	bool print_folder_name, DIR *dir)
{
	char		*str;
	t_dirent	*direntry;

	if (print_folder_name)
		ft_printf("%s:\n", entry->path);
	while ((direntry = readdir(dir)) != NULL)
	{
		if (ctx->all || ft_strncmp(direntry->d_name, ".", 1) != 0)
		{
			if ((str = join_filename(entry->path, direntry->d_name)) \
				!= NULL)
				add_entry_end(ctx, &entry->files, str, direntry->d_name);
			free(str);
		}
	}
	sort_entries(ctx, &entry->files);
	entry->nb_blocks = sum_entries_infos(ctx, entry->files, false, \
		&entry->max_length);
	if (ctx->long_format)
		ft_printf("total %d\n", entry->nb_blocks);
	print_entries_in_folder(ctx, entry);
	if (!ctx->long_format)
		ft_printf("\n");
	closedir(dir);
}

static void		print_folder(t_context *ctx, \
				t_entry *entry, bool print_folder_name)
{
	DIR			*dir;
	char		*str;

	if ((dir = opendir(entry->path)) == NULL)
	{
		ft_asprintf(&str, "ft_ls: Cannot open folder %s", entry->path);
		print_errno(ctx, str, false);
		free(str);
	}
	else
		do_print_folder(ctx, entry, print_folder_name, dir);
	remove_entry(&ctx->entries, entry);
}

void			print_folders(t_context *ctx)
{
	if (ctx->entries != NULL)
	{
		print_folder(ctx, ctx->entries, ctx->recursive || \
			!ctx->only_one_folder || ctx->printed_something);
		sort_entries(ctx, &ctx->entries);
	}
	while (ctx->entries != NULL)
	{
		ft_printf("\n");
		print_folder(ctx, ctx->entries, true);
		sort_entries(ctx, &ctx->entries);
	}
}
