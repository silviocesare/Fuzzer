#ifndef _GreedyMaximumCoverage_h
#define _GreedyMaximumCoverage_h

#include "MaximumCoverage.h"
#include <set>
#include <map>

class GreedyMaximumCoverage : public MaximumCoverage {
public:
	void FindMaximumCoverage(std::list<std::string> &filenameList, double cover,
		std::list<std::pair<std::string, double> > &results);

protected:
	bool PopNextBest(std::pair<std::string, double> &res);
	unsigned int FindUncovered(std::set<Addr> *set);

	std::map<std::string, std::set<Addr> *> m_RemainingSetsByFilename;
	std::set<Addr> m_RemainingBlocks;
};

#endif
