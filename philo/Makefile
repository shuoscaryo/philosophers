NAME := philo

CC := gcc
STANDARD_FLAGS :=  -Wall -Wextra -Werror #-fsanitize=thread

SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj

SRC := main.c\
	init_data.c\
	init_forks.c\
	init_philos.c\
	init_shared.c\
	check_end.c\
	philo_routine.c\
	utils.c

SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRC))
OBJ := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_FOLDER := $(sort $(dir $(OBJ)))
INCLUDE_PATH := -I$(INCLUDE_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(STANDARD_FLAGS)  $(INCLUDE_PATH) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(STANDARD_FLAGS) $(INCLUDE_PATH) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Deleted obj files"

fclean: clean
	@rm -f $(NAME)
	@echo "Deleted $(NAME) executable"
	
re: fclean all

.PHONY: debug clean fclean all re
