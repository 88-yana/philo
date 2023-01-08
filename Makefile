CC = cc
CFLAGS = -Wall -Werror -Wextra -I ./includes/
SRCSDIR = srcs
OBJSDIR = objs
SRCS = $(shell find $(SRCSDIR) -type f -name *.c)
OBJS = $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)
NAME = philo

all: $(OBJSDIR) $(NAME)

test:
	$(MAKE)
	./test.sh

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

.PHONY : all clean fclean re test

