/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include <iostream>

/*
**	if B is true, the public member typeedef 'type' equal 'T'
**	otherwise esta los plsos lol
*/
namespace ft {

	template<bool B, class T = void>
		struct enable_if {};
	
	template<class T>
		struct enable_if<true, T> {

			typedef T type;
		};
}

#endif