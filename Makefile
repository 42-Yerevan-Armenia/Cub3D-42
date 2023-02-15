RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
SKY		= \033[1;36m

NAME = cub3d

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FT_FPRINTF_DIR = ft_fprintf
FT_FPRINTF = $(FT_FPRINTF_DIR)/libftfprintf.a

TMP = objs

CC = cc

CFLAGS =  -Imlx -I./include #-fsanitize=address  #  # #-g -ggdb3-Wall -Wextra -Werror

LINKER =  -lmlx -framework OpenGL -framework Appkit -L ./libft -lgnl -lft -L ./ft_fprintf -lftfprintf #-Lft_fprintf #-Llibft # ./readline-arakhurs/lib

SRCS = $(wildcard ./src/*.c)

OBJS = $(patsubst ./src/%.c, ./$(TMP)/%.o, $(SRCS))

RM = rm -fr

HEADER = $(wildcard ./include/*)

./$(TMP)/%.o: ./src/%.c $(HEADER)
	@$(CC) $(CFLAGS) -o $@ -c $< 
	@echo "$(YELLOW)💡created ➡️  $(SKY)$(notdir $@)$(RESET)"

all: $(NAME)

$(NAME): $(TMP) $(OBJS) $(LIBFT) $(FT_FPRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME)

$(TMP):
	@mkdir $(TMP)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ $(NAME) sucessfully created$(RESET)"

$(FT_FPRINTF):
	@make --no-print-directory -C $(FT_FPRINTF_DIR)
	@echo "$(GREEN)✅ $(NAME) sucessfully created$(RESET)"

clean:
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@make --no-print-directory clean -C $(FT_FPRINTF_DIR)
	@$(RM) $(OBJS_DIR)
	$(RM) $(TMP)
	@echo "$(RED)♨️  clean  🗑$(RESET)"

fclean: clean
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@make --no-print-directory fclean -C $(FT_FPRINTF_DIR)
	@$(RM) $(NAME)
	@echo "$(RED)♨️  fclean  🗑$(RESET)"

re:	fclean all

.PHONY: all clean fclean re bonus .c.o
