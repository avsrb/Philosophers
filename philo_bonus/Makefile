NAME	= philo_bonus

HEADER	=	./philo_bonus.h

LIST	=	main.c parser.c printing.c time.c init.c

GCC		= gcc -Wall -Wextra -Werror -g
OBJS	=	$(LIST:.c=.o)

%.o:			%.c ${HEADER}
				$(GCC) -c -o $@ $<


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

g 		:
	git add .
	git commit -m "update"
	git push



.PHONY	: all clean fclean re bonus