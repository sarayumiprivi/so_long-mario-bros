/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprivite <marvin@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:48:16 by sprivite          #+#    #+#             */
/*   Updated: 2024/11/21 15:49:51 by sprivite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <unistd.h>
#include <stdarg.h>

// Write a single character
static void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

// Write a string
static void	ft_putstr(const char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		ft_putchar(*s, count);
		s++;
	}
}

// Write an integer
static void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return;
	}
	if (n < 0)
	{
		ft_putchar('-', count);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, count);
	ft_putchar((n % 10) + '0', count);
}

// Write an unsigned integer in hexadecimal
static void	ft_puthex(unsigned int n, int *count)
{
	const char *base = "0123456789abcdef";

	if (n >= 16)
		ft_puthex(n / 16, count);
	ft_putchar(base[n % 16], count);
}

// The ft_printf function
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count = 0;

	va_start(args, format); // Initialize variadic arguments
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(args, const char *), &count);
			else if (*format == 'd')
				ft_putnbr(va_arg(args, int), &count);
			else if (*format == 'c')
				ft_putchar(va_arg(args, int), &count);
			else if (*format == 'x')
				ft_puthex(va_arg(args, unsigned int), &count);
		}
		else
		{
			ft_putchar(*format, &count);
		}
		format++;
	}
	va_end(args); // Clean up variadic arguments
	return (count);
}
