# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/07/06 12:59:00 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(shell uname),Linux)
NAME		=	philo_linux
OBJDIR		=	./obj_linux
else
NAME		=	philo
OBJDIR		=	./obj
endif
# remove if

SRCDIR		=	.

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                               REMOVE WILDCARD                                #
# **************************************************************************** #

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