NAME	= philo_bonus

HEADER	=	./philo_bonus.h

LIST	=	main.c parser.c printing.c time.c init.c

CC		= gcc 

CFLAGS	= -Wall -Wextra -Werror -I.

OBJS	=	$(LIST:.c=.o)

.PHONY	: all clean fclean re bonus

all	: $(NAME)

$(OBJS)	: $(HEADER)

$(NAME)	: $(HEADER) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread
#	@clear
	@echo Play?

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		: fclean all