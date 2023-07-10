# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/07/10 16:39:59 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCDIR		=	.
OBJDIR		=	./obj

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

CC			=	cc
TSAN		=	#-fsanitize=thread
CFLAGS		=	-Wall -Werror -Wextra -pthread -g $(TSAN)

RM			=	rm
RMFLAGS		=	-rf

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(TSAN)

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