/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_function.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_FUNCTION_HPP
# define BINARY_FUNCTION_HPP

namespace ft {

	template<class Arg1, class Arg2, class Result>
	struct binary_function {

		typedef Arg1 	first_argument_type;		// first arg of operator()
		typedef Arg2 	second_argument_type;		// second arg of operator()
		typedef Result 	result_type;				// return by operator()
	};
}
#endif