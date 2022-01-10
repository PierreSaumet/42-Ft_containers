# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             #
#   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       #
#                                                                            #
# ************************************************************************** #


# SIMPLE =======================================================================
VECTOR			= vector

# SRCS =========================================================================
SRCS_VECTOR	= ./

SOURCES			=	main.cpp 
					
# INCLUDES =====================================================================
INCLUDE 		+= 	../Headers/binary_function.hpp		\
					../Headers/enable_if.hpp			\
					../Headers/equal.hpp				\
					../Headers/is_integral.hpp			\
					../Headers/iterator.hpp				\
					../Headers/less.hpp					\
					../Headers/lexicographical.hpp		\
					../Headers/nullptr.hpp				\
					../Headers/pair.hpp					\
					../Headers/random_access_iterator.hpp	\
					./vector.hpp

# FLAGS ========================================================================
FLAGS 			= -Wall -Wextra -Werror -g -std=c++98 

# OBJECTS ======================================================================
OBJECTS_FOLDER 	= ./objects/


OBJECT			= $(SOURCES:.cpp=.o)
OBJECTS		 	= $(addprefix $(OBJECTS_FOLDER), $(OBJECT));

VAL = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all
all: $(VECTOR)

# TESTER VECTOR=================================================================
$(OBJECTS_FOLDER)%.o :	$(SRCS_VECTOR)%.cpp	$(INCLUDE) 
	@mkdir -p	$(OBJECTS_FOLDER)
	@echo "Compiling: $<"
	@clang++ $(FLAGS) -c $< -o $@

$(VECTOR): $(OBJECTS)
	@clang++ $(FLAGS) -o  $(VECTOR) $(OBJECTS)

.PHONY: clean
clean:
	@echo "Cleaning: vector objects"
	@rm -rf ./objects

.PHONY: fclean
fclean:	clean
	@echo "Cleaning: vector"
	@rm -rf ./vector

.PHONY: re
re: fclean all
