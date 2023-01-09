CC = cc
CFLAGS = -Wall -Werror -Wextra -I ./includes/
SRCSDIR = srcs
OBJSDIR = objs
SRCS = srcs/init/check_args.c \
	srcs/init/init_vars.c \
	srcs/lib/ft_atoi.c \
	srcs/lib/ft_isdigit.c \
	srcs/lib/ft_strlen.c \
	srcs/main/main.c \
	srcs/simulate/log.c \
	srcs/simulate/monitor.c \
	srcs/simulate/philo.c \
	srcs/simulate/time.c \
	srcs/simulate/utils.c

OBJS = $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)
NAME = philo

all: $(OBJSDIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)


$(OBJSDIR):
	mkdir $(shell find $(SRCSDIR) -type d | sed 's/^$(SRCSDIR)/$(OBJSDIR)/g')

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) -rf $(OBJSDIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re

