#include "CodeCoverageSoFar.h"
#include <iostream>
#include <string>
#include <cstdlib>

static void
Usage(const char *exeName)
{
	fprintf(stderr, "Usage: %s file1 ...\n", exeName);
	exit(1);
}

static void
PrintCSVResults(std::list<std::pair<std::string, double> > &resultsList)
{
	std::list<std::pair<std::string, double> >::iterator resultsListIter;
	unsigned int i;

	printf("\"Filename\", \"Num\", \"Cummulative Percentage\",\n");
	for (	resultsListIter  = resultsList.begin(), i = 1;
		resultsListIter != resultsList.end();
		resultsListIter++, i++)
	{
		printf("%s,%u,%f,\n", resultsListIter->first.c_str(), i, resultsListIter->second);
	}
}

int
main(int argc, char *argv[])
{
	CodeCoverageSoFar coverage;
	std::list<std::string> filenameList;
	unsigned int i;
       	std::list<std::pair<std::string, double> > resultsList;

	if (argc < 2) {
		Usage(argv[0]);
	}
	for (i = 1; i < argc; i++) {
		filenameList.push_back(std::string(argv[i]));
	}
	coverage.Build(filenameList, resultsList);
	PrintCSVResults(resultsList);
}
