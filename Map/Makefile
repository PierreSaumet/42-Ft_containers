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
MAP			= map

# SRCS =========================================================================
SRCS_STACK	= ./

SOURCES			=	main.cpp 

# INCLUDES =====================================================================
INCLUDE 		+= 	../Headers/bidir_redblacktree_iterator.hpp	\
					../Headers/binary_function.hpp		\
					../Headers/enable_if.hpp			\
					../Headers/equal.hpp				\
					../Headers/is_integral.hpp			\
					../Headers/iterator.hpp				\
					../Headers/less.hpp					\
					../Headers/lexicographical.hpp		\
					../Headers/nullptr.hpp				\
					../Headers/pair.hpp					\
					../Headers/random_access_iterator.hpp	\
					../Headers/reverse_random_access_iterator.hpp	\
					./red_black_tree.hpp	\
					./map.hpp

# FLAGS ========================================================================
FLAGS 			= -Wall -Wextra -Werror -g -std=c++98

# OBJECTS ======================================================================
OBJECTS_FOLDER 	= ./objects/


OBJECT			= $(SOURCES:.cpp=.o)
OBJECTS		 	= $(addprefix $(OBJECTS_FOLDER), $(OBJECT));

VAL = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all
all:  $(MAP)

# TESTER MAP=================================================================
#		NO TIMER
$(OBJECTS_FOLDER)%.o :	$(SRCS_STACK)%.cpp	$(INCLUDE) 
	@mkdir -p	$(OBJECTS_FOLDER)
	@echo "Compiling: $<"
	@clang++ $(FLAGS) -c $< -o $@

$(MAP): $(OBJECTS)
	@clang++ $(FLAGS) -o  $(MAP) $(OBJECTS)

.PHONY: clean
clean:
	@echo "Cleaning: map objects"
	@rm -rf ./objects

.PHONY: fclean
fclean:	clean
	@echo "Cleaning: map"
	@rm -rf ./map
	@rm -rf ./map_chrono


.PHONY: re
re: fclean all
