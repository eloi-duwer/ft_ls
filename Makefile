SRC_NAME = main.c \
	print_error_funcs.c \
	args_parsing.c \
	sort_funcs.c \
	helpers.c \
	entries/entry_control.c \
	entries/print_entries_funcs.c \
	entries/print_folder.c

NAME = ft_ls

CC = clang

CFLAGS = -Wall -Wextra -Werror -g -I./include -I./libft/include

SRCF = ./src/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

LFT = libft/libft.a

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -g -L./libft -lft -Wall -Wextra -Werror

$(LFT):
	make -C ./libft

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.c)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
