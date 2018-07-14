# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/07 16:24:07 by tgreil            #+#    #+#              #
#    Updated: 2018/07/14 00:31:42 by tgreil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c			\
			env.c			\
			prompt.c		\
			cmd_exec.c

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
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

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
