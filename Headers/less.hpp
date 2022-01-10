/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
# define LESS_HPP

# include "binary_function.hpp"

# include <iostream>

namespace ft {

	template<class T>
	struct less : binary_function< T, T, bool> {

		bool operator() (const T &x, const T &y) const {

			return (x < y);
		};

	};
}

#endif