/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouzalm <tbouzalm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:23:21 by tbouzalm          #+#    #+#             */
/*   Updated: 2022/08/17 17:56:16 by tbouzalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

int ft_putchar(char c)
{
    int len;

    len = 0;
    len += write(1, &c, 1);
    return (len);
}

int ft_putstr(const char *str)
{
    int len;
    int i;

    len = 0;
    i = 0;
    while (str[i] != '\0')
    {
        len += write(1, &str[i], 1);
        i++;
    }
    return (len);
}

int ft_putnbr(int   nbr)
{
    long    n;
    int     len;
    int     i;

    n = nbr;
    len = 0;
    i = 0;
    if (n < 0)
    {
        len += ft_putchar('-');
        n = n * (-1);
    }
    else if (n > 9)
    {
        len += ft_putnbr(n / 10);
        len += ft_putnbr(n % 10);
    }
    else
        len += ft_putchar(n + '0');
    return (len);
}

int ft_print_hex(unsigned int n)
{
    char    str[]= "0123456789abcdef";
    int     len = 0;
    
    if (n > 16)
        len += ft_print_hex(n / 16);
    len += write(1, &str[n % 16], 1);
    return (len);
}

int ft_check_format(va_list ap,char c)
{
    int len = 0;
    
    if (c == 's')
    {
        len += ft_putstr(va_arg(ap, const char *));
    }
    else if (c == 'd')
    {
        len += ft_putnbr(va_arg(ap, int));
    }
    else if (c == 'x')
    {
        len += ft_print_hex(va_arg(ap, unsigned int));
    }
    return (len);
}

int ft_printf(const char *s, ...)
{
    va_list ap;
    int     i;
    int     len;

    i = 0;
    va_start(ap,s);
    len = 0;
    while (s[i] != '\0')
    {
        if (s[i] != '%')
        {
            len += ft_putchar(s[i]);
        }
        else if (s[i] == '%' && s[i + 1] != '\0')
        {
            len += ft_check_format(ap ,s[i + 1]);
            i++; 
        }
        i++;
    }
    va_end(ap);
    return (len);   
}

int main()
{
    ft_printf("Magic %s is %d\n", "number", 42);
    ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}