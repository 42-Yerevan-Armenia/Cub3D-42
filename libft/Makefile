BLUE	= \033[0;36m

NAME = libft.a

GNL = libgnl.a

CC	=	cc

CFLAGS = -I../includes  -Wall -Wextra -Werror #-fsanitize=address

SRCS = $(wildcard *.c)

GNL_SRCS = $(wildcard get_next_line/*.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

GNL_OBJS = $(patsubst %.c, %.o, $(GNL_SRCS))

RM = rm -f

AR = ar rcs

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@echo "$(BLUE)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

all: $(NAME) $(GNL)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(RM) $(OBJS) $(BONUS_OBJS)
	
$(GNL): $(GNL_OBJS)
	@$(AR) $(GNL) $(GNL_OBJS)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus
