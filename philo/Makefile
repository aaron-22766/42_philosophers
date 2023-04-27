# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/04/27 08:42:22 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCDIR		=	./src
OBJDIR		=	./obj

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                               REMOVE WILDCARD                                #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm
RMFLAGS		=	-rf

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(OBJDIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

.PHONY: all clean fclean re 
