/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:32:55 by eduwer            #+#    #+#             */
/*   Updated: 2020/03/03 18:38:04 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/libftprintf.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <wctype.h>
#include <fcntl.h>

#define COMP_TEST(str, ...) do { \
	write(1, "Testing the string: ", 20); \
	write(1, str, ft_strlen(str)); \
	ret1 = printf(str, __VA_ARGS__); \
	ret2 = ft_printf(str, __VA_ARGS__); \
	ft_printf("   printf: %d\nft_printf: %d\n", ret1, ret2); \
} while (0)

void func_test03(void);
void tests_from_curqui();

int		main(int argc, char **argv)
{
	int fd = open("./Makefile", O_RDONLY);
	char *ptr;
	size_t size;

	//int ret = read_whole_file(fd, (void **)&ptr, &size);
	//printf("%d %s\n", ret, ptr);
	// printf(argv[1], 42);
	// printf("\n");
	// printf(argv[1], -42);
	// printf("\n");
	// printf("Locale: %s\n", setlocale(LC_NUMERIC, NULL));
	// printf("%10d\n", -42);
	// printf("%.10d\n", -42);
	// printf("%20.10d\n", -42);
	// printf("%zd, %zd, %zd\n", sizeof(int), sizeof(short), sizeof(short int));
	
	//char *ptr1;
	//char *ptr2;
	//int ret1 = asprintf(&ptr1, "coucou");
	//int ret2 = ft_asprintf(&ptr2, "coucou");
	//printf("strings: %s %s\n", ptr1, ptr2);
	//printf("Lengths: %d %d\n", ret1, ret2);

	int ret1;
	int ret2;
	//COMP_TEST("%010x\n", 0x0e0e);
	//COMP_TEST("%010d\n", -42);
	//COMP_TEST("%010d\n", 42);
	//COMP_TEST("%010f\n", 0.123f);
	//COMP_TEST("%010s\n", "test");
	//COMP_TEST("%+10.5d\n", 42);
	//COMP_TEST("%+10.5d\n", -42);
	//COMP_TEST("%#15.10x\n", 0x0e0e);
	COMP_TEST("%*d\n", 10, 42);
	COMP_TEST("%.*d\n", 12, 42);
	COMP_TEST("%*.5d\n", 10, 42);
	COMP_TEST("%20.*d\n", 10, 42);
	COMP_TEST("%*.*d\n", 20, 10, 42);
	COMP_TEST("%*.*f\n", 20, 10, 42.42);
	COMP_TEST("% f\n", 123.456);
	//COMP_TEST("%f\n", 1.23);
	//COMP_TEST("%.2f\n", 3.141592654);
	//COMP_TEST("%f\n", 42.0);
	//COMP_TEST("%f\n", 123.456);
	//COMP_TEST("%f\n", 0.4242);
	//COMP_TEST("%f\n", 0.1 + 0.2);
//
// 	float grandNbr = 123456789012345678901234567890123456.0f;
//	unsigned long long faux = (unsigned long long) grandNbr;
//	COMP_TEST("Grand nombre: %f\n", grandNbr);
////
//	COMP_TEST("Vide\n", NULL);
////
//	COMP_TEST("%f\n", INFINITY);
//	COMP_TEST("%f\n", -INFINITY);
//	COMP_TEST("%F\n", INFINITY);
//	COMP_TEST("%20.10F\n", -INFINITY);
//	COMP_TEST("A que coucou %s\n", "bob");
//	COMP_TEST("%.5d\n", 42);
//	COMP_TEST("%.5ld\n", (long)42);
//	COMP_TEST("%.5d\n", -42);
//	COMP_TEST("%hhd\n", 'a');
//	COMP_TEST("%+d\n", 42);
//	COMP_TEST("% d\n", 42);
//	COMP_TEST("% +d\n", 42);
//	COMP_TEST("% +d\n", 42);
//	COMP_TEST("|%10.5d|\n", -12);
//	COMP_TEST("|%10d|\n", -12);
//	COMP_TEST("|%010d|\n", -12);
//	COMP_TEST("|%-10.5d|\n", -12);
//	COMP_TEST("|%-010.5d|\n", -12);
//	COMP_TEST("|%u|\n", (unsigned int)3147483642);
//	//COMP_TEST("|%.hhu|\n", (unsigned char)'é');
//	COMP_TEST("|%llu|\n", (unsigned long long int)18446744073709551615);
//	COMP_TEST("|%10.5u|\n", (unsigned int)3147483642);
//	COMP_TEST("|%100.50u|\n", (unsigned int)3147483642);
//	COMP_TEST("|%o|\n", 0123);
//	COMP_TEST("|%llx|\n", (unsigned long long int)0xabc123);
//	COMP_TEST("|%llx|\n", (unsigned long long int)0x321bca);
//	COMP_TEST("|%#o|\n", 042);
//	COMP_TEST("|%#15.10X|\n", 0x42ab);
//	COMP_TEST("|%+.0d|\n", 0);
//	COMP_TEST("|%+10.0d|\n", 0);
//	COMP_TEST("|% 10.0d|\n", 0);
//	COMP_TEST("|%- 10.0d|\n", 0);
//	COMP_TEST("|%015.10d|\n", 42);
//	COMP_TEST("|%-20p|\n", &ret1);
//	COMP_TEST("|%-20lX|\n", 0xcc42fedcbabcdef);
//	COMP_TEST("|%20c|\n", 'a');
//	COMP_TEST("|%-20c|\n", '\172');
//	COMP_TEST("|%-20c|\n", '\311'); // é mais ca marche pas
//	COMP_TEST("|%30.5s|\n", "a que cc bob é á ö Ó");
//	COMP_TEST("|%30s|\n", "accents: é á ö Ó Â ý ñ Ñ Ỳ");
//	COMP_TEST("%s, %d\n", "test de 2 args", 42);
	//int ret;
	//printf("4567 |%-10]5d| plip\n", 12);
	//printf("4567 |%10]5d| plip\n", 12);
	//printf("a%%bc%defhij\n", 25);
	//ret = printf ("%s\n", "ζ");
	//write (1, "Щ\n", 3);
	//printf("%x %#x\n", 0x123, 0x123);
	//printf("%ll010d\n", 42);
	//if (argc >= 2) {
	//	ret = ft_printf("%s\n", argv[1]);
	//	printf("%d\n", ret);
	//}
	//ret = ft_printf("%s %f %d WOUAOUW\n", "a que coucou", 3.14159f, 42);
	//printf("%d\n", ret);
	//ret = ft_printf("\033[0;31mCC\033[0m CA VA?\n");
	//printf("%d\n", ret);
	//printf("%f\n", (float)123);
	//printf("%f\n", (double)123);
	//printf("%lu, %lu", sizeof(double), sizeof(float));
	//tests_from_curqui();
	//while(1);
	return (0);
}

void func_test03() {
	return;
}

//tests générant une erreur de curqui
void tests_from_curqui() {
	int ret1;
	int ret2;
	COMP_TEST("%D\n",  0xff11ff11ff88);
	COMP_TEST("toto%.0d et %+.i et  %   .0D !!!\n",  0, 0, 0);
	COMP_TEST("\ntoto et %00009U%-2lu mimi et titi%--14u\n",  0, (unsigned long)14, 200);
	COMP_TEST("%#o\n",  0);
	COMP_TEST("coco et %-#-#--24O titi%#012o\n",  12, -874);
	COMP_TEST("t%04.2o%#2oet %#-8.3o titi\n",  0, 0, 0);
	COMP_TEST("\n%024hho et%#1.2o %0012.O\n",  (unsigned char)12, 0, 123654789);
	COMP_TEST("test%#.4o et %02o %0#14.0o!!\n",  012, 036, 12587499);
	COMP_TEST("toto %###.0o%#.O et %#.1o !\n",  0, 0, 0);
	COMP_TEST("%#X\n",  0);
	COMP_TEST("%.7X\n",  0xaa);
	COMP_TEST("%011X\n",  0xdd66);
	COMP_TEST("test%---10.6x et %01hhX !!\n",  0xaabb, (unsigned char)0);
	COMP_TEST("t %#7.5X%0006.2x et %lX!\n",  0xab, 0x876, 0xff11ff11ff1);
	COMP_TEST("cc%#.4X et %#0012x %#04hX !!\n",  0xaef, 0xe, (unsigned short)0);
	COMP_TEST("%#.22zX et %020.14jx\n",  0xff1144ff1144, 0xffaabbccee);
	COMP_TEST("toto %##.0xet %#.X%###.1x\n",  0, 0, 0);
	COMP_TEST("%0#10.0x %0#x\n",  12345, 0);
	COMP_TEST("%0#10.0x\n",  0);
	COMP_TEST("%c\n",  '\0'); //Le code retour doit valoir 1, pas 0
	COMP_TEST("hello ca%----4c %1c va %10c%-c ??\n",  '\0', '\n', (char)564, 0);
	COMP_TEST("%C\n",  0x6f);
	COMP_TEST("%lc\n",  0x4e6);
	COMP_TEST("%lc\n",  0x1e40);
	COMP_TEST("%lc\n",  0x40501);
	COMP_TEST("%C\n",  0x11ffff);
	COMP_TEST("%C\n",  0);
	COMP_TEST("%C\n",  (wint_t)-2);
	COMP_TEST("%C\n",  0xd800);
	COMP_TEST("%C\n",  0xdb02);
	COMP_TEST("%C\n",  0xdfff);
	COMP_TEST("%C\n",  0xbffe);
	COMP_TEST("%lc\n",  254);
	COMP_TEST("%C\n",  83);
	COMP_TEST("%C\n",  256);
	COMP_TEST("%C\n",  0xe000);
	COMP_TEST("%5lc\n",  350);
	COMP_TEST("%-8C\n",  1350);
	COMP_TEST("%-1C\n",  2250);
	COMP_TEST("%8C et coco %C titi %lc\n",  3250, 0x11ffff, 'a');
	COMP_TEST("%---8C et coco %1C titi\n",  3250, 0xffff);
	COMP_TEST("%6C et coco %C titi %C tyty\n",  3250, 0xd800, 'u');
	COMP_TEST("yo%2C%-12lc et %C titi %C tyty\n",  'u', 254, 256, 'a');
	wchar_t s1[4] = {0x53, 0x3abc, 0x81000, '\0'};
	COMP_TEST("%S\n",  s1);
	wchar_t s2[4] = {0x53, 0xd800, 0x81000, '\0'};
	COMP_TEST("%S\n",  s2);
	wchar_t s3[4] = {'a', 254, 'b', '\0'};
	COMP_TEST("%S\n",  s3);
	wchar_t s4[4] = {254, 256, 'b', '\0'};
	COMP_TEST("%S\n",  s4);
	setlocale(LC_ALL, "");
	wchar_t s5[4] = {'\0', 256, 'b', '\0'};
	COMP_TEST("%S\n",  s5);
	wchar_t s6[4] = {'\0', 256, 'b', '\0'};
	COMP_TEST("%S\n",  s6);
	wchar_t s7[4] = {0x53, 0xabc, 0x81000, '\0'};
	COMP_TEST("%.9ls\n",  s7);
	COMP_TEST("%.5ls\n",  s7);
	COMP_TEST("%.3ls\n",  s7);
	COMP_TEST("%.ls\n",  s7);
	COMP_TEST("%.0ls\n",  s7);
	wchar_t s13[4] = {'S', 254, 'u', '\0'};
	COMP_TEST("%.2ls\n",  s13);
	wchar_t s14[4] = {'S', 256, 'u', '\0'};
	COMP_TEST("%.1ls\n",  s14);
	wchar_t s15[4] = {0x53, 0x3abc, 0x81000, '\0'};
	COMP_TEST("%.4ls\n",  s15);
	COMP_TEST("%10ls\n",  s15);
	COMP_TEST("%5S\n",  s15);
	COMP_TEST("%-12S\n",  s15);
	wchar_t s19[4] = {'a', 250, 'b', '\0'};
	COMP_TEST("%-4S\n",  s19);
	wchar_t s20[4] = {'a', 256, 'b', '\0'};
	COMP_TEST("%9ls\n",  s20);
	COMP_TEST("%---10.5ls\n",  s7);
	COMP_TEST("%9.6ls %S\n",  s15, L"a");
	COMP_TEST("cc %10.0ls et %.ls et %-2S%-12S\n",  s15, s15, s15, s15);
	COMP_TEST("%p\n",  NULL);

	typedef struct  s_data
	{
		int		r1;
		int		r2;
		char	*s1;
		char	*s2;
	}				t_data;
	t_data dataTest02;

	COMP_TEST("%p\n",  &dataTest02);
	COMP_TEST("%p\n",  &func_test03);
	COMP_TEST("%20p\n",  &dataTest02);
	COMP_TEST("%-25p\n",  &dataTest02);
	COMP_TEST("%2p\n",  &dataTest02);
	int reta07;
	COMP_TEST("%----24p et hello %2p %12p\n",  &reta07, &main, NULL);
	COMP_TEST("titi % +---12.5% et%%%0004% et %+1%", NULL);
	COMP_TEST("%--.4u et %#O%#012O%1lc\n",  -12, 0, 0, 95);
	COMP_TEST("%-+-12.7Dt%0 4i %04.2% et %lc titi\n",  125, 124, 256);
	COMP_TEST("test%-8p %---32p %#5.3x%#024X\n",  &reta07, &reta07, 0x25, 0);


}
