CC = cc
CFLAGS = -Wall -Werror -Wextra  -I ./includes/
# LFLAGS = -lpthread
SRCSDIR = srcs
OBJSDIR = objs
SRCS = $(shell find $(SRCSDIR) -type f -name *.c)
OBJS = $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)
NAME = philo

all: $(OBJSDIR) $(NAME)

$(NAME): $(OBJS)
	$(CC)  $(OBJS) $(LFLAGS) -o $(NAME)

test:
	$(MAKE)
	./philo 10 300 400 500 600
	# ./philo 0 300 400 500 4
	# ./philo 10 300 400 500 0
	# ./philo 10 300 400 500

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

.PHONY : all clean fclean re test