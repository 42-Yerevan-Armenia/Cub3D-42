/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:43:07 by vaghazar          #+#    #+#             */
/*   Updated: 2023/01/31 18:15:12 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_init(t_all *all)
{
    all->img.n_wall = NULL;
	all->img.s_wall = NULL;
	all->img.e_wall = NULL;
	all->img.w_wall = NULL;
}