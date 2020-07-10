#	Program output
NAME = 42sh

#	GCC flags -Wall -Wextra $(CFLAGS) -g 
#-fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
#CFLAGS = -Wall -Wextra -Werror -g
ALL_CFLAGS = $(CFLAGS)

#	Library files
LIBFLAGS = -L./libft -lft

#	Termcaps library flag
ifeq ($(OS),Windows_NT)
	LIBFLAGS += -lncurses
else
	LIBFLAGS += -ltermcap
endif

#	Ojects/Sources directories
INC_42SH = includes/
SRC_42SH = $(shell find src | grep "\.c$$" | sed "s/\.c$$//g")
INCLUDES += $(addprefix -iquote , $(INC_42SH))
SRCS += $(addsuffix .c, $(SRC_42SH))

#	Extern includes
INC_LIBFT = libft/includes
INCLUDES += $(addprefix -iquote , $(INC_LIBFT))

#	Final OBJS
OBJS = $(SRCS:.c=.o)

#	Layout
VERBOSE = true

all: header $(NAME) footer

header:
	@echo "\033[33m[\033[4m$(NAME)\033[0m\033[33m] Compile\033[0m"

footer:
	@echo "\033[33m[\033[4m$(NAME)\033[0m\033[33m] Finished\033[0m"

$(NAME): lft $(OBJS)
ifeq ($(VERBOSE),true)
	@echo "\033[34m. Compile Final .\033[0m $(NAME)"
else
	@printf"\033[34m.\033[0m\n"
endif
	@$(CC) $(ALL_CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) -g $(LIBFLAGS)

%.o: %.c 
ifeq ($(VERBOSE),true)
	@echo "\033[34m. Compile .\033[0m $<"
else
	@printf"\033[34m.\033[0m"
endif
	@$(CC) $(ALL_CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "\033[33m[\033[4m$(NAME)\033[0m\033[33m] >>\033[0m \033[31mCLEAN all object files (*.o)\033[0m"
	@$(RM) $(OBJS)

fclean: clean lftclean
	@echo -e "\033[33m[\033[4m$(NAME)\033[0m\033[33m] >>\033[0m \033[31mFCLEAN project binary ($(NAME))\033[0m"
	@$(RM) $(NAME)

re: fclean all

lft:
	@echo "\033[33m[\033[4m$(NAME)\033[0m\033[33m] >> Extern dependencies\033[0m"
	@make -C libft
	@echo "\033[33m[\033[4m$(NAME)\033[0m\033[33m] << Extern dependencies\033[0m"

lftclean:
	make -C libft clean

lftfclean:
	make -C libft fclean

lftre:
	make -C libft re

git:
	@git add .
	@echo "Enter Your Commit :"
	@read var1 ; git commit -m "$$var1"
	@git push
