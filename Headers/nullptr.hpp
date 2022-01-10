/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_ptr.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NULLPTR_HPP
# define NULLPTR_HPP

# include <iostream>
// THANK YOU Scott Meyers
static class nullptr_t
{
	public:
		template< class T>
		operator T*() const {

			return  (0);
		}

		template< class C, class T>
		operator T C::*() const {

			return (0);
		}
	
	private:
		void operator&() const;

} my_nullptr = {};

#endif