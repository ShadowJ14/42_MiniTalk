NAME_SERVER	= server
NAME_CLIENT	= client
SRC = $(shell find src -type f -name "*.c")
LIB = $(shell find libs -type f -name "*.a")
INCLUDE = $(addprefix -I, includes)
OBJS = $(SRC:.c=.o)
OBJS_CLIENT	= $(filter-out src/server.o, $(OBJS))
OBJS_SERVER	= $(filter-out src/client.o, $(OBJS))
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: libft $(NAME_SERVER) $(NAME_CLIENT)

libft:
	$(MAKE) -C libs/libft
	$(MAKE) bonus -C libs/libft

$(NAME_SERVER): libft $(OBJS_SERVER)
		@$(CC) -o $(NAME_SERVER) $(CFLAGS) $(INCLUDE) $(LIB) $(OBJS_SERVER)

server_san: libft $(OBJS_SERVER)
		@$(CC) -fsanitize=address -o $(NAME_SERVER) $(CFLAGS) $(INCLUDE) $(LIB) $(OBJS_SERVER)

$(NAME_CLIENT):	libft $(OBJS_CLIENT)
		@$(CC) -o $(NAME_CLIENT) $(CFLAGS) $(INCLUDE) $(LIB) $(OBJS_CLIENT)

client_san:	libft $(OBJS_CLIENT)
		@$(CC) -fsanitize=address -o $(NAME_CLIENT) $(CFLAGS) $(INCLUDE) $(LIB) $(OBJS_CLIENT)

.c.o:
			@echo "Creating object: $@"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	make clean -C libs/libft
	$(RM)   $(OBJS)

fclean: clean
		make fclean -C libs/libft
		$(RM) $(NAME)
		$(RM) $(NAME_SERVER)
		$(RM) $(NAME_CLIENT)

re: fclean all

bonus: all

.PHONY:         all clean fclean bonus re libft $(NAME_SERVER) $(NAME_CLIENT)