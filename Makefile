minishell:
	@mkdir -p build
	@(cd build && cmake .. && make --no-print-directory)
	@cp build/minishell minishell

clean:
	rm -fr build

fclean: clean
	rm -f minishell

supp:
	@echo "{\n ignore_libreadline_libs\n Memcheck:Leak\n ...\n obj:*/libreadline.so.*\n}" > supp

valgrind: minishell supp
	valgrind --quiet --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=supp --track-fds=yes ./minishell

norm:
	norminette src lib/environ lib/execute lib/libft lib/parse lib/tokenize

.PHONY: clean fclean minishell valgrind norm
