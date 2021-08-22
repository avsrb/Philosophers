NAME	= philo

HEADER	=	./philo.h

LIST	=	main.c parser.c printing.c time.c init.c

OBJS	=	$(LIST:.c=.o)

CC		= gcc 
CFLAGS	= -Wall -Wextra -Werror -I.

.PHONY	: all clean fclean re bonus

all	: $(NAME)

$(NAME)	: $(HEADER) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread
#	@clear
	@echo Play?

$(OBJS)	: $(HEADER)

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		: fclean all