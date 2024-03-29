/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_diu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:26:00 by angkim            #+#    #+#             */
/*   Updated: 2019/10/02 09:41:25 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// get argument
// get LEN, WIDTH, and PRECISION values
// determine if prefix needed (check for F_PLUS || F_SPACE)
	// negative values (minus sign)
// determine padding: how many zeros/spaces (check for F_ZERO)
// determine order of prefix, padding, value (check for F_MINUS)
	// 0's should always be connected to the decimal value
	// prefix (+ or space) are the same
	// space padding should never come between zero padding / prefix and decimal values
// keep track of count (f->count)
// reset struct

void	put_int(char **format, t_format *f, va_list args)
{
	get_mod_arg_di(f, args);
	COUNT += (f->d_arg < 0) ? 1 : 0;
	LEN = ft_digitcount(f->d_arg);
	WIDTH -= (f->d_arg < 0) ? 1 : 0;
	if (FLAGS & F_PLUS || FLAGS & F_SPACE)
	{
		if (f->d_arg >= 0)
			WIDTH--;
	}
// printf("\n\tneg: %d\tlen: %d\twidth: %d\tprec: %d\n", (f->d_arg < 0) ? 1 : 0, LEN, WIDTH, PREC);
	if (!(FLAGS & F_ZERO) || (FLAGS & F_ZERO && f->p))
	{
		P_ZERO = PREC - LEN;
		P_SPACE = (WIDTH -= (PREC > LEN) ? PREC : LEN);
	}
	else if (FLAGS & F_ZERO)
	{
		P_ZERO = (WIDTH > PREC) ? (WIDTH - LEN) : (PREC - LEN);
		P_SPACE = 0;
	}
// printf("\n\tspace: %d\tzero: %d\n", P_SPACE, P_ZERO);
	if (!(FLAGS & F_MINUS))
		put_pad_int(f);
	else if (FLAGS & F_MINUS)
		put_pad_int_minus(f);
	COUNT += ft_digitcount(f->d_arg);
	(*format)++;
	reset_struct(f);
}

void	put_int_value(t_format *f)
{
// printf("HERE: PREC = %d\n", PREC);
	if (f->d_arg == 0 && f->p && (PREC == 0 || PREC == 1))
	{
		if (f->spec == 'd' || f->spec == 'i')
		{
			if (WIDTH > -1)
				write(1, " " , 1);
			else
				COUNT--;
		}
		else
			return ;
	}
	else
	{
		if ((f->d_arg) + 1 == -9223372036854775807)
			return ;
		(f->spec == 'u') ? ft_putnbr(f->u_arg) : ft_putnbr(f->d_arg);
	}
}

void	put_unsigned(char **format, t_format *f, va_list args)
{
	get_mod_arg_u(f, args);
	LEN = ft_digitcount(f->u_arg);
	if (!(FLAGS & F_ZERO) || (FLAGS & F_ZERO && f->p))
	{
		P_ZERO = PREC - LEN;
		P_SPACE = (WIDTH -= (PREC > LEN) ? PREC : LEN);
	}
	else if (FLAGS & F_ZERO)
	{
		P_ZERO = (WIDTH > PREC) ? (WIDTH - LEN) : (PREC - LEN);
		P_SPACE = 0;
	}
// printf("\n\tspace: %d\tzero: %d\n", P_SPACE, P_ZERO);
	if (!(FLAGS & F_MINUS))
		put_pad_int(f);
	else if (FLAGS & F_MINUS)
		put_pad_int_minus(f);
	COUNT += ft_digitcount(f->u_arg);
	(*format)++;
	reset_struct(f);
}
