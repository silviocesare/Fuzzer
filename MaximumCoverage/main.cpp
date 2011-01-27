#include <iostream>
#include <string>
#include <cstdlib>

#include "GreedyMaximumCoverage.h"

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

	printf("\"Filename\", \"Cummulative Percentage\",\n");
	for (	resultsListIter  = resultsList.begin();
		resultsListIter != resultsList.end();
		resultsListIter++)
	{
		printf("%s,%f,\n", resultsListIter->first.c_str(), resultsListIter->second);
	}
}

int
main(int argc, char *argv[])
{
	std::list<std::string> filenameList;
	GreedyMaximumCoverage coverage;
	std::list<std::pair<std::string, double> > resultsList;
	unsigned int i;

	if (argc < 2) {
		Usage(argv[0]);
	}
	for (i = 1; i < argc; i++) {
		filenameList.push_back(std::string(argv[i]));
	}
	coverage.FindMaximumCoverage(filenameList, -1, resultsList);
	PrintCSVResults(resultsList);
}
