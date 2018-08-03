# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/07 16:24:07 by tgreil            #+#    #+#              #
#*   Updated: 2018/08/03 14:02:45 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c					\
			error.c					\
			env.c					\
			prompt.c				\
			cmd_exec.c 				\
			cmd_parser.c			\
			cmd_parser_replace.c	\
			exec_cmd.c				\
			forkator.c				\
			builtin_search.c		\
			builtin_echo.c			\
			builtin_env.c			\
			builtin_setenv.c		\
			builtin_unsetenv.c		\
			builtin_cd.c			\
			builtin_cd_envmodifier.c

OBJS	= $(addprefix srcs/, $(SRCS:.c=.o))

LIBS	= -Llibft/ -lft

PROJECT = minishell_project

NAME	= minishell

RM	= rm -f

CC	= gcc

MAKELIB	= make -C libft/

LIB	= libft/libft.a

CFLAGS	= -W -Wall -Wextra -Werror
CFLAGS	+= -Iincludes/ -Ilibft/includes/

LDFLAGS	=  $(LIBS)

$(PROJECT):	$(LIB) $(NAME)

$(NAME): 	$(OBJS) Makefile
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -fsanitize=address

$(LIB):
	$(MAKELIB)

all:	$(PROJECT)

clean:
	$(RM) $(OBJS)
	$(MAKELIB) clean

fclean:
	$(RM) $(OBJS)
	$(MAKELIB) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	re fclean clean all $(PROJECT)
