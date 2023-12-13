/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:42:45 by araymond          #+#    #+#             */
/*   Updated: 2023/12/13 09:57:59 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the character is a space character.
int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
