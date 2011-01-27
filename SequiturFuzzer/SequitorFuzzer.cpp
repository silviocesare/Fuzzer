#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cassert>

static bool
okToMutateTerminal()
{
	if ((rand() % 1024) == 0)
		return true;
	return false;
}

static bool
okToMutateInsertTrailingTerminal()
{
	if ((rand() % 1024) == 0)
		return true;
	return false;
}

static int
get_rdtsc()
{
	__asm__("rdtsc");
}

int
main(int argc, char *argv[])
{
	std::string rule;

	srand(get_rdtsc());
	while (getline(std::cin, rule)) {
		unsigned int ruleNum;
		std::stringstream strStream(rule);

		strStream >> ruleNum;
		printf("%u ", ruleNum);
        	while (!strStream.eof()) {
        	        char type;
        	        unsigned int num;

			strStream >> type;
			if (strStream.eof()) {
				break;
			}
			strStream >> num;
			if (type == 't') {
				if (okToMutateTerminal()) {
					printf("t %u ", rand() % 256);
				} else {
					printf("t %u ", num);
				}
			} else {
				assert(type == 'n');
				printf("n %u ", num);
			}
		}
		if (okToMutateInsertTrailingTerminal()) {
			printf("t %u ", rand() % 256);
		}
		printf("\n");
	}
	return 0;
}
