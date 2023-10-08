NAME := philosophers

CC := gcc
STANDARD_FLAGS := -fsanitize=leak -pthread -Wall -Wextra -Werror 

SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj

SRC := main.c\
	create_mutex.c\
	save_inputs.c\
	free_mutex.c

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

.PHONY: clean fclean all re
