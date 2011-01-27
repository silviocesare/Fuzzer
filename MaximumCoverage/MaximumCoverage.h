#ifndef _MaximumCoverage_h
#define _MaximumCoverage_h

#include <list>
#include <string>
#include <set>

typedef unsigned int Addr;

class MaximumCoverage {
public:
	virtual ~MaximumCoverage() {}

	virtual void FindMaximumCoverage(std::list<std::string> &filenameList, double cover,
		std::list<std::pair<std::string, double> > &results) = 0;

protected:
	std::set<Addr> *BuildSetFromFilename(std::string &filename);
	std::set<Addr> *BuildSetFromBinaryFilename(std::string &filename);
	std::set<Addr> m_AllBlocks;
};

#endif
