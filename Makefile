CC     = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS   = -lncurses
SRC = main.c args.c executor.c display.c utils.c error.c help.c keyboard.c
NAME   = mywatch2

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all
