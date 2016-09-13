/**
 * Differentially-private high-confidence association rule extractor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dp2d.h"
#include "fp.h"

/* Command line arguments */
static struct {
	/* filename containing the transactions */
	char *tfname;
	/* global value for epsilon */
	double eps;
	/* fraction of epsilon for first step */
	double er1;
	/* confidence threshold */
	double c0;
	/* max number of items in rule */
	size_t lmax;
	/* num items (to be removed later) */
	size_t ni;
	/* branching factor */
	size_t cspl;
	/* random seed */
	long int seed;
} args;

static void usage(const char *prg)
{
	fprintf(stderr, "Usage: %s TFILE C0 RMAX NI\n", prg);
	exit(EXIT_FAILURE);
}

static void parse_arguments(int argc, char **argv)
{
	int i;

	printf("Called with: argc=%d\n", argc);
	for (i = 0; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");

	if (argc != 5)
		usage(argv[0]);
	args.tfname = strdup(argv[1]);
	if (sscanf(argv[2], "%lf", &args.c0) != 1 || args.c0 < 0 || args.c0 >= 1)
		usage(argv[0]);
	if (sscanf(argv[3], "%lu", &args.lmax) != 1 || args.lmax < 2 || args.lmax > 7)
		usage(argv[0]);
	if (sscanf(argv[4], "%lu", &args.ni) != 1)
		usage(argv[0]);
}

int main(int argc, char **argv)
{
	struct fptree fp;

	parse_arguments(argc, argv);

	fpt_read_from_file(args.tfname, &fp);
	printf("fp-tree: items: %lu, transactions: %lu, nodes: %d, depth: %d\n",
			fp.n, fp.t, fpt_nodes(&fp), fpt_height(&fp));

#if 0
	dp2d(&fp, args.eps, args.er1, args.c0, args.lmax, args.ni, args.seed,
			args.cspl);
#endif

	fpt_cleanup(&fp);
	free(args.tfname);

	return 0;
}