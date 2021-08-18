NAME	= philo_bonus

HEADER	=	./philo_bonus.h

LIST	=	main.c parser.c printing.c time.c init.c

OBJS	=	$(LIST:.c=.o)

GCC		= gcc -Wall -Wextra -Werror -g

all	: $(NAME)

$(NAME)	: $(HEADER) $(OBJS)
	$(GCC) $(OBJS) -o $(NAME) -pthread
#	@clear
	@echo Play?

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		: fclean all

.PHONY	: all clean fclean re bonus