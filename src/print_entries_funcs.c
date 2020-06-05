#include <ft_ls.h>

t_bool		is_folder(t_context *ctx, t_entry *entry)
{
	t_stat	stats;
	char	*str;

	if (stat(entry->path, &stats) == -1)
	{
		ft_asprintf(&str, "ft_ls: Can't stat file %s", entry->path);
		print_errno(ctx, str, false);
		free(str);
		return (false);
	}
	if ((stats.st_mode & S_IFMT) == FOLDER_MASK)
		return (true);
	return (false);
}

static char	*make_time_string(t_context *ctx, t_entry *entry)
{
	char	**splitted;
	char	*ret;
	
	if ((splitted = ft_strsplit(ctime(&entry->stats.st_mtime), ' ')) == NULL)
		return (NULL);
	if ((ctx->today > entry->stats.st_mtime && \
		ctx->today - entry->stats.st_mtime > 3600 * 24 * 30 * 6)
		|| entry->stats.st_mtime - ctx->today > 3600)
		ft_asprintf(&ret, "%.3s %2s %5.4s", \
			splitted[1], splitted[2], splitted[4]);
	else
		ft_asprintf(&ret, "%.3s %2s %.5s", \
			splitted[1], splitted[2], splitted[3]);
	ft_free_string_list(splitted);
	return ret;
}

static void	add_soft_link(t_context *ctx, t_entry *entry)
{
	char	*str;

	if ((str = (char *)malloc(entry->stats.st_size + 1)) != NULL)
	{
		if (readlink(entry->path, str, entry->stats.st_size) == -1)
		{
			free(str);
			ft_asprintf(&str, "ft_ls: Can't read link %s", entry->path);
			print_errno(ctx, str, false);
			free(str);
			return ;
		}
		str[entry->stats.st_size] = '\0';
		ft_printf(" -> %s", str);
		free(str);
	}
	else
		print_errno(ctx, "ft_ls: Can't malloc", false);
}

static void	print_entry(t_context *ctx, t_entry *entry, int max_len)
{
	char		right_string[11];
	t_passwd	*user_name;
	t_group		*group_name;
	char		*time_string;

	
	if (ctx->long_format == true)
	{
		make_rights_string(entry, right_string);
		user_name = getpwuid(entry->stats.st_uid);
		if (user_name == NULL)
			print_errno(ctx, "ft_ls: Can't get username infos", true);
		group_name = getgrgid(entry->stats.st_gid);
		if (group_name == NULL)
			print_errno(ctx, "ft_ls: Can't get group infos", true);
		time_string = make_time_string(ctx, entry);
		ft_printf("%s %d %s %s %*d %s %s", right_string, entry->stats.st_nlink, \
			user_name->pw_name, group_name->gr_name, \
			max_len, entry->stats.st_size, time_string, entry->filename);
		if (right_string[0] == 'l')
			add_soft_link(ctx, entry);
		ft_printf("\n");
		free(time_string);
	}
	else
		ft_printf("%s  ", entry->filename);
}

void		sum_entries_infos(t_context *ctx, t_entry *entry, t_bool only_files, \
				int *out_max_size, int *out_nb_blocks)
{
	char	*buf;
	int		len;

	*out_max_size = 0;
	*out_nb_blocks = 0;
	while (entry != NULL)
	{
		if (!only_files || !is_folder(ctx, entry))
		{
			if ((len = ft_asprintf(&buf, "%ld", entry->stats.st_size)) \
				> *out_max_size)
				*out_max_size = len;
			free(buf);
			*out_nb_blocks += entry->stats.st_blocks;
		}
		entry = entry->next;
	}
}

void		print_folder(t_context *ctx, \
				t_entry *entry, t_bool print_folder_name)
{
	DIR			*dir;
	char		*str;
	t_dirent	*direntry;
	t_entry		*cursor;
	t_entry		*next;

	if ((dir = opendir(entry->path)) == NULL)
	{
		ft_asprintf(&str, "ft_ls: Cannot open folder %s", entry->path);
		print_errno(ctx, str, false);
		free(str);
	}
	else
	{
		if (print_folder_name)
			ft_printf("%s:\n", entry->path);
		while ((direntry = readdir(dir)) != NULL)
		{
			if (ctx->all || ft_strncmp(direntry->d_name, ".", 1) != 0)
			{
				if ((str = join_filename(entry->path, direntry->d_name)) != NULL)
					add_entry_end(ctx, &entry->files, str, direntry->d_name);
				free(str);
			}
		}
		sort_entries(ctx, &entry->files);
		sum_entries_infos(ctx, entry->files, false, \
			&entry->max_length, &entry->nb_blocks);
		if (ctx->long_format)
			ft_printf("total %d\n", entry->nb_blocks);
		cursor = entry->files;
		while (cursor != NULL)
		{
			print_entry(ctx, cursor, entry->max_length);
			next = cursor->next;
			if (ctx->recursive && file_type(cursor, FOLDER_MASK) && \
				ft_strcmp(cursor->filename,  ".") != 0 && ft_strcmp(cursor->filename, "..") != 0)
				add_entry_beginning(ctx, &ctx->entries, cursor->path, cursor->filename);
			remove_entry(&entry->files, cursor);
			cursor = next;
		}
		if (!ctx->long_format)
			ft_printf("\n");
		closedir(dir);
	}
	remove_entry(&ctx->entries, entry);
}

void		first_pass_print_files(t_context *ctx)
{
	t_entry	*cursor;
	t_entry	*next;
	int		max_len;
	int		nb_blocks;

	cursor = ctx->entries;
	sum_entries_infos(ctx, cursor, true, &max_len, &nb_blocks);
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

void		print_folders(t_context *ctx)
{
	if (ctx->entries != NULL)
	{
		print_folder(ctx, ctx->entries, ctx->recursive || !ctx->only_one_folder || ctx->printed_something);
		sort_entries(ctx, &ctx->entries);
	}
	while (ctx->entries != NULL)
	{
		ft_printf("\n");
		print_folder(ctx, ctx->entries, true);
		sort_entries(ctx, &ctx->entries);
	}
}
