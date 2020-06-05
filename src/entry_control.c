#include <ft_ls.h>

t_bool	remove_entry(t_entry **first_entry, t_entry *entry)
{
	if (entry->prev != NULL)
		entry->prev->next = entry->next;
	else
		*first_entry = entry->next;
	if (entry->next != NULL)
		entry->next->prev = entry->prev;
	free(entry->path);
	free(entry->filename);
	free(entry);
	return (true);
}

void	copy_strs(t_entry *entry, char *path, char *name)
{
	char	*str_path;
	char	*str_name;
	size_t	length_path;
	size_t	length_name;

	length_path = ft_strlen(path);
	if ((str_path = (char *)malloc(length_path + 1)) == NULL)
		print_error("Error on malloc", true);
	ft_memcpy(str_path, path, length_path);
	str_path[length_path] = '\0';
	entry->path = str_path;
	length_name = ft_strlen(name);
	if ((str_name = (char *)malloc(length_name + 1)) == NULL)
		print_error("Error on malloc", true);
	ft_memcpy(str_name, name, length_name);
	str_name[length_name] = '\0';
	entry->filename = str_name;
}

static t_bool	add_entry_err(t_context *ctx, char *path, t_entry **first_entry, t_entry *new_entry)
{
	char *err_str;

	ft_asprintf(&err_str, "ft_ls: Cannot access '%s'", path);
	print_errno(ctx, err_str, false);
	free(err_str);
	remove_entry(first_entry, new_entry);
	return (false);
}

t_bool	add_entry_beginning(t_context *ctx, t_entry **first_entry, \
			char *path, char *filename)
{
	t_entry *new_entry;

	if ((new_entry = (t_entry *)ft_memalloc(sizeof(t_entry))) == NULL)
		print_errno(ctx, "ft_ls: Error on malloc", true);
	copy_strs(new_entry, path, filename);
	if (lstat(path, &new_entry->stats) == -1)
		return (add_entry_err(ctx, path, first_entry, new_entry));
	if (*first_entry != NULL)
		(*first_entry)->prev = new_entry;
	new_entry->next = *first_entry;
	*first_entry = new_entry;
	return (true);
}

t_bool	add_entry_end(t_context *ctx, t_entry **first_entry, \
			char *path, char *filename)
{
	t_entry *new_entry;
	t_entry	*cursor;

	if ((new_entry = (t_entry *)ft_memalloc(sizeof(t_entry))) == NULL)
		print_errno(ctx, "ft_ls: Error on malloc", true);
	copy_strs(new_entry, path, filename);
	if (lstat(path, &(new_entry->stats)) == -1)
		return (add_entry_err(ctx, path, first_entry, new_entry));
	if (*first_entry == NULL)
		(*first_entry) = new_entry;
	else
	{
		cursor = *first_entry;
		while (cursor->next != NULL)
			cursor = cursor->next;
		cursor->next = new_entry;
		new_entry->prev = cursor;
	}
	return (true);
}

void	swap_adjacent_entries(t_entry **first_entry, t_entry *one, t_entry *two)
{
	t_entry	*mem_prev;
	t_entry	*mem_next;

	if (*first_entry == one)
		*first_entry = two;
	mem_prev = one->prev;
	mem_next = two->next;
	one->prev = two;
	one->next = two->next;
	two->prev = mem_prev;
	two->next = one;
	if (mem_prev != NULL)
		mem_prev->next = two;
	if (mem_next != NULL)
		mem_next->prev = one;
}
