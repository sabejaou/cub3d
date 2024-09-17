/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:42:45 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/17 17:03:24 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_CUB3D_H
# define ERRORS_CUB3D_H

// ERRCD

typedef enum e_errcd
{
	NO_ERROR = 0,
	ERR_ARGS_NBR = -1,
	ERR_ACCESS_MAP = -2,
	ERR_INVALID_MAP = -3,
	ERR_FILE_CONSTRUCTION = -4,
	ERR_ACCESS_TEXTURE = -5,
	ERR_FORMAT_TEXTURE = -6,
	ERR_COLOR_FORMAT = -7,
	ERR_ALLOC = -8,
} t_errcd;

#endif