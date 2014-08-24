#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN3(a,b,c) ((a < b) ? ((a < c) ? a : c) : ((b < c) ? b:c) )
#define VERSION "v1.0"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\x1b[34m"

typedef unsigned short u16_t;

#define U16_SIZE sizeof(u16_t)


static void displayHelp();
static u16_t getLevenDistance(const char* s0, const char* s1);

int main(int argc, char** argv)
{
	unsigned short argc_copy = argc;
	unsigned short i = 0;
	const char* s0;
	const char* s1;

	if (argc_copy > 1) {
		switch (argv[1][1]) {
			default:
			case 'h':
				displayHelp();
				return 0;
			case 'd':
				if (argc < 4) {
					printf("\n" ANSI_COLOR_RED 
						"Please provide two strings for comparison."
						ANSI_COLOR_RESET
						"\n");
					displayHelp();
				} else {
					s0 = &argv[2][0];
					s1 = &argv[3][0];
					u16_t distance = getLevenDistance(s0,s1);
					printf("\n\nThe Levenshtein distance of %s and %s is %d.\n\n",
						s0, s1, distance);
					exit(EXIT_SUCCESS);
					return 0;
				}
				break;

		}
	} else {
		displayHelp();
	}

	return 0;
}

static void displayHelp()
{
	fprintf(stderr,
		"\n-----------------------------------------------\n"
		ANSI_COLOR_YELLOW
		"Simple Levenshtein Distance Tool %s"
		ANSI_COLOR_RESET
		"\n-----------------------------------------------\n"
		"Usage: leven [flag] [string1] [string2]\n"
		"  -h <help>        Display help text.\n"
		"  -d <distance>    Return Levenshtein distance."
		"\n-----------------------------------------------\n"
		"Example: leven -d aba acb\n\n",
		VERSION);
	exit(EXIT_FAILURE);
	return;

}

static u16_t getLevenDistance(const char* s0, const char* s1)
{
	u16_t s0_len = (u16_t) strlen(s0) + 1;
	u16_t s1_len = (u16_t) strlen(s1) + 1;

	u16_t* c_cost = malloc(U16_SIZE*s0_len);
	u16_t* new_c_cost = malloc(U16_SIZE*s0_len);

	for (size_t i = 0; i < s0_len; i++) c_cost[i] = i;

	for (size_t j = 1; j < s1_len; j++) {
		new_c_cost[0] = (u16_t) j;
		for (size_t i = 1; i < s0_len; i++) {
			u16_t m = (s0[i-1] == s1[j-1]) ? 0 : 1;

			u16_t c_r = c_cost[i-1] + m;
			u16_t c_i = c_cost[i] + 1;
			u16_t c_d = new_c_cost[i-1] + 1;

			new_c_cost[i] = MIN3(c_r, c_i, c_d);
		}
		u16_t* swap = c_cost;
		c_cost = new_c_cost;
		new_c_cost = swap;
	}

	return c_cost[s0_len-1];
}