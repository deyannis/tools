/*-
 *	pagetool.c
 *	Dimitris Deyannis
 *	d.deyannis@gmail.com
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

unsigned int	addr_to_uint(char *);
void		usage(void);
int		check_args(int);


int
main(int argc, char **argv)
{
	int page_size = getpagesize();
	int page_mask = ~(page_size - 1);
	char *addr;
	int c;

	if (!check_args(argc))
		return 0;

	/* process arguments */
	while (-1 != (c = getopt(argc, argv,
		"a:"	/* address to be converted */
		"h"	/* help */
		)))
		{
		switch (c)
			{
			case 'a':
				addr = strdup(optarg);
				break;
			case 'h':
				usage();
				return 0;
				break;
			default:
				printf("Illegal argument %c\n", c);
				printf("Use -h for help!\n");
				return 0;
			}
		}

	printf("Address:\t0x%X\n", addr_to_uint(addr));
	printf("Uint Value:\t%u\n", addr_to_uint(addr));
        printf("Page Mask:\t0x%X\n", addr_to_uint(addr) & ~page_mask);
        printf("Page:\t\t0x%X\n", addr_to_uint(addr) & page_mask);

	return 0;
}

unsigned int
addr_to_uint(char *s)
{
	unsigned int result = 0;
	int c ;

	if (('0' == *s) && ('x' == *(s + 1)))
		s += 2;

	while (*s)
		{
		result = result << 4;

		if (c = (*s - '0'), ((c >= 0) && (c <= 9)))
			result |= c;
		else if (c = (*s - 'A'), ((c >= 0) && (c <= 5)))
			result |= (c + 10);
		else if (c = (*s - 'a'), ((c >= 0) && (c <= 5)))
			result |= (c + 10);
		else break;

		++s;
		}

	return result;
}


void 
usage(void)
{
	printf("Usage:\tpagetool [-a] [ADDRESS]\n");
	printf("\t\t [-h]\n\n");
	printf("Options\n");
	printf("\t-a,\t<address>\taddress to be calculated.\n");
	printf("\t\t\t\te.g.: 0xFF8C364A\n");
	printf("\t-h,\t\t\tprint this help message\n");
	return;
}


int 
check_args(int c)
{
	if (c == 1)
		{
                printf("Illegal argument %c\n", c);
                printf("Use -h for help!\n");
                return 0;
                }

	return 1;
}
