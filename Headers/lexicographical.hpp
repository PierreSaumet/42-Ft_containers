/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_HPP
# define LEXICOGRAPHICAL_HPP

/*
**	Check if the first range of first1 / last1 is less than the second range
**	if yes, then return true(1). Overwise, returns false(0).
*/

namespace ft {

	template<class InputIt1, class InputIt2>
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return (true);
			else if (*first1 > *first2)
				return (false);
			else
			{
				first1++;
				first2++;
			}
		}
		return (first1 == last1) && (first2 != last2);
	}	
	
}


#endif