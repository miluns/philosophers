NAME = philosophers

FLAGS = -Wall -Werror -Wextra
LIB = philosophers.h

srcs_dir = srcs
objs_dir = objs

src = $(wildcard $(srcs_dir)/*.c)
obj = $(src:$(srcs_dir)/%.c=$(objs_dir)/%.o)

all: $(NAME)

$(NAME): $(obj)
	$(CC) $(FLAGS) $^ -o $@

$(objs_dir)/%.o: $(srcs_dir)/%.c $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(objs_dir)

fclean: clean
	rm -f $(NAME)

re: fclean all
