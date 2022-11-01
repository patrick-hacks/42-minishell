minishell:
	@bash pain.sh
	@cp build/minishell minishell

all: minishell

clean:
	rm -fr build

fclean: clean
	rm -f minishell

re: fclean all

valgrind: minishell
	valgrind --quiet --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=supp --track-fds=yes ./minishell

norm:
	norminette src lib/environ lib/execute lib/libft lib/get_next_line lib/parse lib/tokenize

.PHONY: clean fclean minishell valgrind norm
