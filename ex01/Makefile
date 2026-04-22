NAME := RPN
CXX := c++
RM := rm -rf
CXXFLAGS := -Wall -Wextra -Werror -std=c++17

INCLUDE_DIR := include
SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := main.cpp Rpn.cpp
INCLUDES_FILES := Rpn.hpp

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
HEADERS := $(addprefix $(INCLUDE_DIR)/, $(INCLUDES_FILES))

INCLUDES := -I$(INCLUDE_DIR)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
