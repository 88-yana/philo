CC = cc
CFLAGS = -Wall -Werror -Wextra  -I ./includes/
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

PHILO_HEADERS = ./includes/

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJSDIR):
	mkdir $(shell find $(SRCSDIR) -type d | sed 's/^$(SRCSDIR)/$(OBJSDIR)/g')

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJSDIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
