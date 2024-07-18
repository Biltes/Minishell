# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 11:19:45 by pevieira          #+#    #+#              #
#    Updated: 2024/07/18 11:19:49 by pevieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	src/built-ins/exit.c \
		src/built-ins/echo.c \
		src/built-ins/pwd.c \
		src/built-ins/execute_commands.c \
		src/built-ins/unset.c \
		src/built-ins/cd.c \
		src/built-ins/env.c \
		src/built-ins/chdir.c \
		src/built-ins/export.c \
		src/built-ins/exit_errors2.c \
		src/parser/lexer_2.c \
		src/parser/token_init.c \
		src/parser/ast_1.c \
		src/parser/parser_2.c \
		src/parser/lexer_1.c \
		src/parser/ast_2.c \
		src/parser/verify_input.c \
		src/parser/parser_1.c \
		src/envp/env_utils.c \
		src/envp/env_init.c \
		src/envp/envp.c \
		src/free_and_errors/exit_errors_2.c \
		src/free_and_errors/exit_errors_1.c \
		src/free_and_errors/exit_errors_3.c \
		src/executor/check.c \
		src/executor/here_doc.c \
		src/executor/cmd_exec.c \
		src/executor/main_exec.c \
		src/executor/cmd_redir.c \
		src/main.c \
		src/signals/signals.c \
		src/expand/arg_expander.c \
		src/expand/expand.c \
		src/expand/arg_transform.c \

OBJDIR = obj
OBJS = $(patsubst src/%,${OBJDIR}/%,${SRC:.c=.o})

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
INCLUDE = -I include
MAKE = make -C
LIBFT_PATH = libft
LFLAGS = -L ${LIBFT_PATH} -lft -lreadline

${OBJDIR}/%.o: src/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${NAME}: ${OBJS}
	${MAKE} ${LIBFT_PATH}
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} ${LFLAGS} -o ${NAME}

all:	${NAME}

clean:
	${MAKE} ${LIBFT_PATH} clean
	${RM} -r ${OBJDIR}

fclean: clean
	${MAKE} ${LIBFT_PATH} fclean
	${RM} ${NAME}

re: fclean all

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all -s --log-file=output.log ./minishell

readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

.PHONY: all clean fclean re
