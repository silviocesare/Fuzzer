#include <iostream>
#include <fstream>
#include <getopt.h>
#include <cstdlib>

static void
Usage()
{
	fprintf(stderr, "Usage: foo [-a numToChange] [-b percToChange] [infile]\n");
	exit(1);
}

static unsigned int
get_rdtsc()
{
	__asm__("rdtsc");
}

int
main(int argc, char *argv[])
{
	char *data;
	int ch;
	std::ifstream in;
	unsigned int size;
	unsigned int numToChange = 2;
	unsigned int seed = get_rdtsc();
	float percToChange = -1.0;

	while ((ch = getopt(argc, argv, "a:s:b:")) != EOF) {
		switch (ch) {
		case 'a':
			numToChange = atoi(optarg);
			break;
		case 'b':
			percToChange = atof(optarg);
			break;
		case 's':
			seed = atoi(optarg);
			break;
		default:
			Usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc != 1) {
		Usage();
	}
	srand(seed);
	in.open(argv[0], std::ifstream::in | std::ifstream::binary);
	in.seekg(0, std::ios_base::end);
	size = in.tellg();
	if (percToChange > 0.0) {
		numToChange = percToChange * (float)size;
	}
	in.seekg(0);
	data = new char[size];
	in.read(data, size);
	for (unsigned int i = 0; i < numToChange; i++) {
		unsigned int pos;

		pos = rand() % size;
		data[pos] = rand() % 255;
	}
	in.close();
	std::cout.write(data, size);
	delete [] data;
	exit(0);
}
