#include "main.h"

/**
 * _printf - prints anything
 * @format: the format string
 *
 * Return: number of bytes printed
 */
int _printf(const char *format, ...)
{
	int sum = 0;
	va_list ap;
	char *p, *start;
	params_t params = PARAMS_INIT;

	va_start(ap, format);

	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (p = (char *)format; *p; p++)
	{
		init_params(&params, ap);
		if (*p != '%')
		{
			sum += _putchar(*p);
			continue;
		}
		start = p;
		p++;
		while (get_flag(p, &params)) /* while char at p is flag char */
		{
			p++; /* next char */
		}
		p = get_width(p, &params, ap);
		p = get_precision(p, &params, ap);
		if (get_modifier(p, &params))
			p++;
		if (!get_specifier(p))
			sum += print_from_to(start, p,
				params.l_modifier || params.h_modifier ? p - 1 : 0);
		else
			sum += get_print_func(p, ap, &params);
	}
	_putchar(BUF_FLUSH);
	va_end(ap);
	return (sum);
}
// #include "main.h"
// /**
//  *_printf - function that produces output according to a format
//  *@format: info to print
//  *Return: count
//  */
// int _printf(const char *format, ...)
// {
// 	va_list args;
// 	int i, len;
// 	int (*get_ptr)(va_list, int);

//     va_start(args, format);
// 	if (!(format))
// 		return (-1);
// 	i = 0;
// 	len = 0;
// 	while (format && format[i])
//     {
//         	if (format[i] == '%')
// 		{
// 			i++;
// 			if (format[i] == '%')
// 			{
// 				len += _putchar(format[i]);
// 				i++;
// 				continue;
// 			}
// 			if (format[i] == '\0')
// 				return (-1);
// 			get_ptr = get_print_func(format[i]);
// 			if (get_ptr != NULL)
// 				len = get_ptr(args, len);
// 			else
// 			{
// 				len += _putchar(format[i - 1]);
// 				len += _putchar(format[i]);
// 			}
// 			i++;
// 		}
// 		else
// 		{
// 			len += _putchar(format[i]);
// 			i++;
// 		}
// 	}
//     va_end(args);
// 	return (len);
// }