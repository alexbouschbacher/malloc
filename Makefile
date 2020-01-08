SRCS	=	tools.c \
			free.c \
			malloc.c \
			realloc.c

OBJS	=	$(SRCS:.o=.c)

CFLAGS	=	-I./include -W -Wall -Wextra -fPIC

LFLAGS	=	-shared -lpthread

CC	=	gcc

NAME	=	libmy_malloc.so

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	fclean re clean all
