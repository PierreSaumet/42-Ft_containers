/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <utility>

/*
** Check if T is an integral type : bool. char, char16_t, char32_t, wchar_t, siggned_char,
**	short_int, int, long int, long long int, unsgined char, unsigned short int, unsigned int, unsigned long itn ...
*/

namespace ft {

	template<class T>
	struct				is_integral {

		static const bool			value = false;
	};

	template<>
	struct is_integral<bool> {
	
		static const bool			value = true;
	};
	
	template<>
	struct is_integral<char> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<wchar_t> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<signed char> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<short int> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<int> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<long int> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<long long int> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<unsigned char> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<unsigned short int> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<unsigned int> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<unsigned long int> {
	
		static const bool			value = true;
	};

	template<>
	struct is_integral<unsigned long long int> {
	
		static const bool			value = true;
	};
};

#endif