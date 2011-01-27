#ifndef _CodeCoverageSoFar_h
#define _CodeCoverageSoFar_h

#include <set>
#include <list>
#include <string>
#include <map>

typedef unsigned int Addr;

class CodeCoverageSoFar {
public:
	void Build(std::list<std::string> &filenameList, std::list<std::pair<std::string, double> > &resultsList);

protected:
	std::set<Addr> *BuildSetFromBinaryFilename(std::string &filename);
	std::set<Addr> *BuildSetFromFilename(std::string &filename);
	unsigned int FindUncovered(std::set<Addr> *set);

	std::map<std::string, std::set<Addr> *> m_SetsByFilename;
        std::set<Addr> m_AllBlocks;
        std::set<Addr> m_RemainingBlocks;
};

#endif
