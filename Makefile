minishell: lib/readline/config.h
	@mkdir -p build
	@(cd build && cmake .. && make --no-print-directory)
	@cp build/minishell minishell

lib/readline/config.h:
	(cd lib/readline && ./configure)

clean:
	rm -fr build
	rm -f lib/readline/config.h

fclean: clean
	rm -f minishell

valgrind: minishell
	valgrind --quiet --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=supp --track-fds=yes ./minishell

norm:
	norminette src lib/environ lib/execute lib/libft lib/parse lib/tokenize

.PHONY: clean fclean minishell valgrind norm
