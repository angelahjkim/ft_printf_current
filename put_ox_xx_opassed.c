/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ox_xx_opassed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:26:00 by angkim            #+#    #+#             */
/*   Updated: 2019/09/30 12:51:37 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
if HASH flag

continue with padding as usual

THEN
before printing number (where depends on the presence of the MINUS flag)

check if there was '0' padding added
	if NOT, add a '0'
	otherwise, do nothing

done.
*/

#include "ft_printf.h"

void	put_hex(char **format, t_format *f, va_list args)
{
	uint64_t tmp;

	get_mod_arg_ox_xx(f, args);
	if (f->ox_arg == 0 && f->w_val == -1)
		put_ox_zero(f);
	else
	{
		tmp = f->ox_arg;
		while (tmp / 16)
		{
			f->arg_len++;
			tmp /= 16;
		}
		f->arg_len++;
		f->count += f->arg_len;
		put_hex_flags(f);
	}
	(*format)++;
	reset_struct(f);
}

void	put_hex_flags(t_format *f)
{
	if (f->flags & F_HASH)
		f->w_val -= 2;
	if (f->flags & F_MINUS)
	{
		put_prefix(f);
		(f->ox_arg != 0) ? ft_puthex_lower(f->ox_arg) : ft_putchar(' ');
		put_padding(f);
		f->flags -= F_MINUS;
	}
	else if (f->flags & F_ZERO && f->flags & F_HASH)
	{
		put_prefix(f);
		put_padding(f);
		if (f->spec == 'x')
			(f->ox_arg != 0) ? ft_puthex_lower(f->ox_arg) : ft_putchar(' ');
		else if (f->spec== 'X')
			(f->ox_arg != 0) ? ft_puthex_upper(f->ox_arg) : ft_putchar(' ');
	}
	else
	{
		put_padding(f);
		put_prefix(f);
		if (f->spec == 'x')
			(f->ox_arg != 0) ? ft_puthex_lower(f->ox_arg) : ft_putchar(' ');
		else if (f->spec== 'X')
			(f->ox_arg != 0) ? ft_puthex_upper(f->ox_arg) : ft_putchar(' ');
	}
}

void	put_octal(char **format, t_format *f, va_list args)
{
	uint64_t tmp;

	// get_mod_arg_ox_xx(f, args);
	f->ox_arg = va_arg(args, uint64_t);
	// if (f->ox_arg == 0 && f->w_val == -1)
	// 	put_ox_zero(f);
	// else
	// {
		tmp = f->ox_arg;
		while (tmp / 8)
		{
			LEN++;
			tmp /= 8;
		}
		LEN++;
		COUNT += LEN;


if (f->ox_arg == 0 && f->p == 1 && f->p_val <= 0)
	P_SPACE--;

		put_octal_flags(f);
	// }
	(*format)++;
	reset_struct(f);
}

void	put_octal_flags(t_format *f)
{
	if (!(FLAGS & F_ZERO) || (FLAGS & F_ZERO && f->p))
	{
		P_ZERO = PREC - LEN;
		P_SPACE = (WIDTH -= (PREC > LEN) ? PREC : LEN);
	}
	else if (FLAGS & F_ZERO)
	{
		P_ZERO = (WIDTH > PREC) ? (WIDTH - LEN) : (PREC - LEN);
		P_SPACE = 0;
		if (FLAGS & F_HASH && f->p >=0 && f->ox_arg)
			P_ZERO--;
	}

if (P_ZERO > 0 && !(FLAGS & F_ZERO))
	f->hash_flag = 1;

if (FLAGS & F_HASH && WIDTH >= PREC && f->ox_arg != 0)
	P_SPACE--;
if (FLAGS & F_HASH && f->ox_arg == 0 && PREC == 0)
	P_SPACE--;

	if (!(FLAGS & F_MINUS))
		put_pad_int(f);
	else if (FLAGS & F_MINUS)
		put_pad_int_minus(f);
}

void	put_prefix_ox_xx(t_format *f)
{
	if (FLAGS & F_ZERO && FLAGS & F_HASH && f->p)
	{
		PREC--;
		P_ZERO--;
	}
	while (PREC-- > LEN)
	// while (P_ZERO)
	{
		write(1, "0", 1);
		COUNT++;
		// PREC--;
		P_ZERO--;
	}
// printf("\n\tspace: %d\tzero: %d\tprec: %d\n", P_SPACE, P_ZERO, PREC);

	if (FLAGS & F_HASH)
	{
		// if (P_ZERO)
		if (f->hash_flag == 0)
			ft_putchar('0');
		if (f->spec == 'x')
			ft_putchar('x');
		else if (f->spec == 'X')
			ft_putchar('X');
		(f->spec == 'o') ? (COUNT++) : (COUNT += 2);
		// FLAGS -= F_HASH;
		// P_ZERO--;
	}
}

void	put_ox_zero(t_format *f)
{
	if (FLAGS & F_HASH) 
	{
		if (f->spec == 'x' || f->spec == 'X')
		{
			if (!f->p)
				write(1, "0", 1);
			else
				return ;
		}
		else if (f->spec == 'o')
		{
			if (f->p && (PREC == 0 || PREC == 1))
				write(1, "0", 1);
			else if (PREC == -1 && WIDTH == -1)
				write(1, "0", 1);
		}
	}
	else if (f->w_val == -1 && !(f->p))
		write(1, "0", 1);
	else if (f->p && f->p_val != -1)
		return ;
	COUNT++;
	f->hash_flag = 1;
}

void	put_ox_value(t_format *f)
{
	if (f->ox_arg == 0 && f->p && (PREC == 0 || PREC == 1))
	{
			if (WIDTH > -1)
				write(1, " " , 1);
			else
				COUNT--;
	}
	else
	{
		if (f->spec == 'o')
			ft_putoctal(f->ox_arg);
		else if (f->spec == 'x' || f->spec == 'X')
		{
			if (f->spec == 'x')
				ft_puthex_lower(f->ox_arg);
			else
				ft_puthex_upper(f->ox_arg);
		}
	}
}
