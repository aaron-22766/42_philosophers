# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/05/09 12:31:10 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCDIR		=	.
OBJDIR		=	./obj

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                               REMOVE WILDCARD                                #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -pthread -fsanitize=thread -g
LDFLAGS		=	-fsanitize=thread

RM			=	rm
RMFLAGS		=	-rf

SOCRATES	=	https://github.com/nesvoboda/socrates
SOCRATESDIR	=	./socrates

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

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

$(SOCRATESDIR):
	git clone $(SOCRATES) $(SOCRATESDIR); (cd $(SOCRATESDIR) && python3 -m pip install -r requirements.txt --user)

test: $(NAME) $(SOCRATESDIR)
	python3 $(SOCRATESDIR)/socrates.py ..

.PHONY: all clean fclean re
