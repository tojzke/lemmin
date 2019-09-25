/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiehn <bkiehn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:31:56 by dzboncak          #+#    #+#             */
/*   Updated: 2019/03/12 17:58:42 by bkiehn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/includes/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "fcntl.h"
# define U_LL unsigned long long

typedef enum	e_flag_f
{
	p2, p1r, p1b, p0, neg, dis, lc
}				t_flag_f;

typedef enum		e_flag
{
	NO_FLAG, PLUS, MINUS, SPACE, SHARP, NOLL, EXC
}					t_flag;

typedef	enum		e_datatype
{
	CHAR = 1, STR, DEC, PTR, U_DEC, OCT, HEX, HEX_B, FLOAT
}					t_datatype;

typedef enum		e_length
{
	NO_LEN, hh, h, l, ll, L
}					t_length;

typedef union		u_data
{
	long long int	i;
	unsigned char	c;
	char			*str;
	double			d;
	size_t			pointer;

}					t_data;

typedef struct		s_str
{
	char			*buf;
	size_t			len;
}					t_str;

typedef struct		s_p_buf
{
	t_flag			flag[7];
	int				width;
	int				precision;
	t_length		d_length;
	t_datatype		d_type;
	t_data			data;
	size_t			len;
	char			*f_str;
	char			*end_find;
	int				fd;
}					t_p_buf;

char				*find_type(t_p_buf *str, char *start, va_list *ap);
int					parse_start(char **start, va_list *ap, int fd);
void				parse_flags(t_p_buf *tmp, char *start);
void				parse_width(t_p_buf *tmp, char *start);
void				parse_precision(t_p_buf *tmp, char *start);
int					parse_length(t_p_buf *tmp, char *start);
int					addtnl_types(char c, t_p_buf *p_str);
int					ft_printf(const char *f, ...);
char				*get_char(char c);
int					type_char(char c, t_p_buf *p_str);
void				numeric(t_p_buf *p_str);
void				numeric_u(t_p_buf *p_str);
char				*get_format_str(t_p_buf *p_str, va_list *ap);
char				*ft_itoa_long(long long int n);
char				*ft_itoa_unlong(unsigned long long int n);
char				*itoa_hex(unsigned long long int i, int size);
char				*char_add(char *str, char c, int n);
char				*add_char(char *str, char c, int n);
char				*add_char2zero(char *str, char c, int n, t_p_buf *p_str);
char				*itoa_oct(unsigned long long int i);
char				*check_presicion(t_p_buf *p_str);
char				*check_width(t_p_buf *p_str, char *prec_str);
char				*use_width(t_p_buf *p_str, char *prev_s);
char				*use_flags(t_p_buf *p_str, char *prev_str);
char				*use_flags_and_width(t_p_buf *p_str, char *prec_s);
char				*min_prec(t_p_buf *p_str, char *str, char c, int count);
char				*plus_prec(t_p_buf *p_str, char *str, char c, int count);
void				wid_to_sign(t_p_buf *p_str, int diff, char **tmp,
					char *prev_str);
int					find_max(int a, int b, int c);
int					hex_oct_types(char c, t_p_buf *p_str);
char				*neg_wid(t_p_buf *p_str, char *prev_s, char c);
char				*hec_oct_flags(t_p_buf *p_str, char *prev_str);
void				numeric_f(t_p_buf *p_str, va_list *ap);
char				*ft_itoa_double(long double i, int prec);
char				*d_to_s(long double i, t_flag_f *f, int prec);
char				*real_f(t_flag_f *f, char *str, int lstr);
char				*flags_f(t_flag_f *f, long double i, int prec);
char				*drob_f(char *str2, int prec, t_flag_f *f, long double i);
void				flags_f_p0(t_flag_f *f, long double i, int prec);
long double			ft_pow(long long x, int y);
char				*ft_strjoin_clean(char *s1, char *s2);
char				*chek_special_number(double i);
int					calc_diff_w(t_p_buf *p_str, char *prev_str, int *diff_w,
					int *diff_p);
char				*exceptions_hex(t_p_buf *p_str);
void				set_diff_p(t_p_buf *p_str, int *diff_p, int *wid,
					int *len);
int					found_fd(va_list *ap, char **str);

#endif
