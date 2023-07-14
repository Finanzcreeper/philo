CC = cc
CFLAGS = -g3
CFULLFLAGS = -Wall -Werror -Wextra
MAKEFLAGS = --no-print-directory
SRC = 	creator.c\
		grim_reaper.c\
		thinkies_guy.c\
		utils.c
OBJ = $(SRC:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFULLFLAGS) $(CFLAGS) $(OBJ) -o $(NAME)

e : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

testing :
	$(CC) $(OBJ) $(CFLAGS)

clean :
	@rm -f $(OBJ)  2>/dev/null

fclean : clean
	@rm -f $(NAME) 2>/dev/null

re : clean $(NAME)

.PHONY: re clean testing e 
