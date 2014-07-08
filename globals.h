/**
 * Global functions and utilities.
 */

#ifndef _GLOBALS_H
#define _GLOBALS_H

#define die(s, ...) \
	do {\
		fprintf(stderr, "[%s: %s %d] "s"\n", __FILE__, \
				__func__, __LINE__, ##__VA_ARGS__); \
		exit(EXIT_FAILURE); \
	} while (0)

struct drand48_data;

/* qsort function for integer comparisons */
int int_cmp(const void *a, const void *b);

void init_rng(struct drand48_data *buffer);

/* Laplace mechanism */
double laplace_mechanism(double x, double eps, double sens,
		struct drand48_data *buffer);

#endif
