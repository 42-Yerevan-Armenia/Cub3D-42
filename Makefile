RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RESET		= \033[0;37m
BLUE		= \033[0;36m
SKY			= \033[1;36m

NAME		=	cub

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

TMP = objs

SRCS		=	$(shell find ./src -name "*.c" | grep src | grep '\.c')

OBJS		=	$(SRCS:.c=.o)

# OBJS_DIR = $(shell find ./src -name "*.c" | cut -d'/' -f4 | grep '\.c')
# OBJS = $(patsubst %.c, ./$(TMP)/%.o, $(OBJS_DIR))

CC			=	cc

RM			=	rm -rf

CFLAGS		=	-Wall -Werror -Wextra -Imlx -fsanitize=address

all: $(NAME)

./$(TMP)/%.o: ./src/%.c
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $@ -c $< 
	@echo "$(YELLOW)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

$(NAME): $(TMP) $(OBJS) $(LIBFT) 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ $(NAME) sucessfully created$(RESET)"

$(TMP):
	@mkdir $(TMP)

clean:
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS_DIR)
	@$(RM) $(TMP)
	@echo "$(RED)♨️  clean  🗑$(RESET)"

fclean: clean
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "$(RED)♨️  fclean  🗑$(RESET)"

re:	fclean all

.PHONY: all clean fclean re bonus .c.o
