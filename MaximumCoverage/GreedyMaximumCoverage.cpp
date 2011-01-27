#include "GreedyMaximumCoverage.h"

unsigned int
GreedyMaximumCoverage::FindUncovered(std::set<Addr> *set)
{
	std::set<Addr>::iterator iter;
	unsigned int count;

	count = 0;
	for (	iter  = set->begin();
		iter != set->end();
		iter++)
	{
		if (m_RemainingBlocks.find(*iter) != m_RemainingBlocks.end()) {
			count++;
		}
	}
	return count;
}

bool
GreedyMaximumCoverage::PopNextBest(std::pair<std::string, double> &res) // result is not cummulative
{
        std::map<std::string, std::set<Addr> *>::iterator iter, maxIter;
	unsigned int uncoveredMax;

	uncoveredMax = 0;
	maxIter = m_RemainingSetsByFilename.end();
	for (	iter  = m_RemainingSetsByFilename.begin();
		iter != m_RemainingSetsByFilename.end();
		iter++)
	{
		unsigned int u ;

		u = FindUncovered(iter->second);
		if (u > uncoveredMax) {
			uncoveredMax = u;
			maxIter = iter;
		}
	}
	if (maxIter != m_RemainingSetsByFilename.end()) {
		std::set<Addr>::iterator remIter;

		res.first = maxIter->first;
//printf("foo %i %i\n", uncoveredMax, m_AllBlocks.size());
		res.second = (double)uncoveredMax / m_AllBlocks.size();
		for (	remIter  = maxIter->second->begin();
			remIter != maxIter->second->end();
			remIter++)
		{
			m_RemainingBlocks.erase(*remIter);
		}
		delete maxIter->second;
		m_RemainingSetsByFilename.erase(maxIter);
		return true;	
	}
	return false;
}

void
GreedyMaximumCoverage::FindMaximumCoverage(std::list<std::string> &filenameList, double cover,
	std::list<std::pair<std::string, double> > &results)
{
	std::list<std::string>::iterator filenameListIter;
	double currentCover = 0.0;
	
	for (	filenameListIter  = filenameList.begin();
		filenameListIter != filenameList.end();
		filenameListIter++)
	{
		std::set<Addr> *set;

		set = BuildSetFromBinaryFilename(*filenameListIter);
		if (set == NULL)
			throw "woopsy";
		m_RemainingSetsByFilename[*filenameListIter] = set;
	}

	m_RemainingBlocks = m_AllBlocks;
	do {
		std::pair<std::string, double> res;

		if (!PopNextBest(res)) {
			break;
		} else {
			currentCover += res.second;
			results.push_back(std::pair<std::string, double>(res.first, currentCover));
		}
	} while ((cover < 0 || currentCover < cover) && m_RemainingSetsByFilename.size() != 0);
	
	// this only happens in error
        std::map<std::string, std::set<Addr> *>::iterator cleanIter;
	for (	cleanIter  = m_RemainingSetsByFilename.begin();
		cleanIter != m_RemainingSetsByFilename.end();
		cleanIter++)
	{
		delete cleanIter->second;
	}
}
