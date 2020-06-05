#include <ft_ls.h>

int		main(int argc, char **argv)
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
