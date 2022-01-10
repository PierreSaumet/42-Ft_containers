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

# RULES ======================================================================
.PHONY: all
all: vector stack map

.PHONY: vector
vector:
		@cd Vector && make

.PHONY: stack
stack:
		@cd Stack && make

.PHONY: map
map:
		@cd Map && make

.PHONY: clean
clean:
	@echo "Cleaning: vector objects"
	@rm -rf ./Vector/objects
	@echo "Cleaning: stack objects"
	@rm -rf ./Stack/objects
	@echo "Cleaning: map objects"
	@rm -rf ./Map/objects

.PHONY: fclean
fclean:	clean
	@echo "Cleaning: vector"
	@rm -rf ./Vector/vector
	@rm -rf ./Vector/vector_chrono
	@echo "Cleaning: stack"
	@rm -rf ./Stack/stack
	@rm -rf ./Stack/stack_chrono
	@echo "Cleaning: map"
	@rm -rf ./Map/map
	@rm -rf ./Map/map_chrono


.PHONY: re
re: fclean all
